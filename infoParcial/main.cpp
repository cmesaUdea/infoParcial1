void setup(){
    pinMode(pinData, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinClock, OUTPUT);
    Serial.begin(9600);
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



void secuenciaCuadrados() {
  int* valoresFilasLeds = new int[BYTE_SIZE]; // Asignación de memoria dinámica para un arreglo de enteros
  int fila = 0;
  for (int i = 0; i < 2; i++) {
    byte valorInicial = B11011011;
    Serial.println(valorInicial);
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


void encederLeds(){
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
