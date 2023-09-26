int pinData  = 2;
int pinLatch = 3;
int pinClock = 4;
char data;
#define TIEMPO 200
#define BYTE_SIZE 8

void setup(){
    pinMode(pinData, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinClock, OUTPUT);
    Serial.begin(9600);
}


void loop(){
    publik();
    while (Serial.available() == 0) {}
    data = Serial.read();
    if(data == '1'){
        verificacion();
    } else if (data == '2'){
        imagen();
    } else if (data == '3'){
        secuencias();
    }
}

void publik(){
    Serial.println("***********");
    Serial.println("Bienvenido");
    Serial.println("1. Probar Leds");
    Serial.println("2. Ingresar imagen (8 lineas de 1 y 0)");
    Serial.println("3. Probar secuencias");
}

void verificacion(){
  	int secu, time, i = 0;
    Serial.println("Ingrese el numero de secuencias: ");
    while(Serial.available() == 0) {}
    secu = Serial.parseInt();
    Serial.println("Ingrese el tiempo de retardo en ms: ");
    while(Serial.available() == 0) {}
    time = Serial.parseInt();
    Serial.println("Mostrando secuencia...");
    while(i < secu){
        encenderLeds();
        delay(time);
        apagarLeds();
        delay(time);
        i ++;
    }  
}

void imagen() {
    int *valoresFilasLeds = new int[BYTE_SIZE]; // Aplicación de memoria dinamica en un arreglo
    int secu, tiempo, i = 0;
    Serial.println("Ingrese 8 filas: (ej: 11100111)");

    for (int fila = 0; fila < BYTE_SIZE; fila++) { // Recorro cada una de las filas de leds
        char linea[BYTE_SIZE + 1]; // Defino el arreglo con un espacio mas para el valor '\0'
        while (Serial.available() == 0) {} // Mantengo en espera de un nuevo datos ingresado
        Serial.readBytesUntil('\n', linea, BYTE_SIZE); // Leo caracter por caracter hasta encontrar un salto de linea
        linea[BYTE_SIZE] = '\0'; // Agrego un carácter nulo al final del arreglo para formar una cadena válida
        valoresFilasLeds[fila] = binarioAEntero(linea); // Asigno al array de enteros el binario ingresado convertido a entero
        Serial.print("Leido:");
        Serial.println(linea);
        // Limpieza del arreglo
        memset(linea, 0, sizeof(linea));
    }
    Serial.println("Ingrese la cantidad de secuencias: ");
    while(Serial.available() == 0) {}
    secu = Serial.parseInt();
  	Serial.println("Ingrese el tiempo de retardo en ms: ");
    while(Serial.available() == 0) {}
  	tiempo = Serial.parseInt();

    while(i < secu){
      // Recorro el arreglo para saber cuanto desplazarlo (de acuerdo a lo ingresado)
      // Se recorre en reversa para que se iluminen de la misma forma en la que se ingresó
      for (int fila = BYTE_SIZE; fila > 0; fila--) {
          shiftOut(pinData, pinClock, LSBFIRST, valoresFilasLeds[fila-1]);
      }

      // Ya asignados los desplazamientos mando la señal digital
      digitalWrite(pinLatch, HIGH);
      digitalWrite(pinLatch, LOW);

      
      Serial.println("Mostrando patron...");

      delay(tiempo);

      apagarLeds();
      
      delay(tiempo);
      i++;
  }
  //se libera la memoria dinamica
  delete[] valoresFilasLeds;
}

void secuencias(){
    Serial.println("Ingrese el tiempo de retardo en ms: ");
    while (Serial.available() == 0) {}
    int retardo = Serial.parseInt();

    secuenciaRombo();
    delay(retardo);
    apagarLeds();
    delay(retardo);

    secuenciaX();
    delay(retardo);
    apagarLeds();
    delay(retardo);

    secuenciaCuadrados();
    delay(retardo);
    apagarLeds();
    delay(retardo);

    secuenciaFlecha();
    delay(retardo);
    apagarLeds();
    delay(retardo);
}

void secuenciaRombo() {
  int* valoresFilasLeds = new int[BYTE_SIZE];
  int valorLedIzq = 16;
  int valorLedDer = 8;
  int valor = 0;
  for (int i = 0; i < 4; i++) {
    valor = valor + valorLedIzq + valorLedDer;
    valoresFilasLeds[i] = valor; // Guardo la fila que va hacia arriba
    valoresFilasLeds[(BYTE_SIZE - 1) - i] = valor; // Guardo la misma fila que va hacia abajo
    valorLedIzq = valorLedIzq*2;
    valorLedDer = valorLedDer/2;
    
  }
  
  for (int i = 0; i < 8; i++) {
    shiftOut(pinData, pinClock, LSBFIRST, valoresFilasLeds[i]);
  }
  
  // Ya asignados los desplazamientos mando la señal digital
  digitalWrite(pinLatch, HIGH);
  digitalWrite(pinLatch, LOW);

  delete[] valoresFilasLeds;

  Serial.println("Mostrando patron 1...");
}

void secuenciaX() {
    int* valoresFilasLeds = new int[BYTE_SIZE];
    int valorLedIzq = 128;
    int valorLedDer = 1;
    int valor = 0;
    for (int i = 0; i < 4; i++) {
        valor = valorLedIzq + valorLedDer;
        valoresFilasLeds[i] = valor;
        valoresFilasLeds[(BYTE_SIZE - 1) - i] = valor;
        valorLedIzq = valorLedIzq/2;
        valorLedDer = valorLedDer*2;
    }

    for (int i = 0; i < 8; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valoresFilasLeds[i]);
    }

    digitalWrite(pinLatch, HIGH);
    digitalWrite(pinLatch, LOW);

    delete[] valoresFilasLeds;

    Serial.println("Mostrando patron 2...");
}

void secuenciaCuadrados() {
  int* valoresFilasLeds = new int[BYTE_SIZE]; // Asignación de memoria dinámica para un arreglo de enteros
  int fila = 0;
  for (int i = 0; i < 2; i++) {
    byte valorInicial = B11011011;
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        valoresFilasLeds[fila] = valorInicial;
        fila++; // Lo guardo en un array para mostrarlo de arriba hacia abajo
      }
      
      valorInicial = (valorInicial >> 1);
      
    }
  }
  
  for (int fila = BYTE_SIZE; fila > 0; fila--) {
    shiftOut(pinData, pinClock, LSBFIRST, valoresFilasLeds[fila-1]);
  }
  
  // Ya asignados los desplazamientos mando la señal digital
  digitalWrite(pinLatch, HIGH);
  digitalWrite(pinLatch, LOW);

  // Liberar la memoria dinámica cuando ya no se necesite
  delete[] valoresFilasLeds;

  Serial.println("Mostrando patron 3...");
}

void secuenciaFlecha() {
    byte valorInicial = B11110000;

    for (int i = 0; i < 4; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valorInicial);
        if(i != 3){
            valorInicial = (valorInicial >> 1);
        }
    }
    for (int i = 0; i < 4; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valorInicial);
        valorInicial = (valorInicial << 1);
    }

    digitalWrite(pinLatch, HIGH);
    digitalWrite(pinLatch, LOW);
    Serial.println("Mostrando patron 4...");
}

void encenderLeds(){
    Serial.println("Probando leds...");
    shiftOut(pinData, pinClock, LSBFIRST, 255); //shiftout envia datos a dispositivos externos
    shiftOut(pinData, pinClock, LSBFIRST, 255); 
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    shiftOut(pinData, pinClock, LSBFIRST, 255);
    
    // Ya asignados los desplazamientos mando la señal digital
  digitalWrite(pinLatch, HIGH);
  digitalWrite(pinLatch, LOW);

}

void apagarLeds(){
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  shiftOut(pinData, pinClock, LSBFIRST, 0);
  
  // Ya asignados los desplazamientos mando la señal digital
  digitalWrite(pinLatch, HIGH);
  digitalWrite(pinLatch, LOW);
}

// Hago uso de punteros para recorrer el arreglo de caracteres
int binarioAEntero(char binario[]) {
    int entero = 0;
    char* ptr = binario;
    while (*ptr != '\0') {
        char digito = *ptr;

        if (digito == '1') {
            entero = (entero << 1) | 1;
        } else if (digito == '0') {
            entero = entero << 1;
        } else {
            // Manejo de error si se encuentra un carácter no válido
            Serial.println("Error: Cadena de binario no válida");
                return -1; // Valor de error
        }
        ptr++; // Apunto al siguiente elemento del arreglo
    }
    return entero;
}
