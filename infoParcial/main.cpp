void setup(){
    pinMode(pinData, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinClock, OUTPUT);
    Serial.begin(9600);
}

void publik(){
    Serial.println("***********");
    Serial.println("Bienvenido");
    Serial.println("1. Probar Leds");
    Serial.println("2. Ingresar imagen (8 lineas de 1 y 0)");
    Serial.println("3. Probar secuencias");
}

void loop(){
    publik();
    while (Serial.available() == 0) {}
    data = Serial.read();
    if(data == '1'){
        verificacion();
    } else if (data == '2'){
        ingresarImagen();
    } else if (data == '3'){
        secuencias();
    }
}

void verificacion(){
    encenderLeds();
    delay(2000);
    apagarLeds();
    delay(1000);
}

void secuenciaX() {
    int valoresFilasLeds[BYTE_SIZE];
    int valorLedIzq = 128;
    int valorLedDer = 1;
    int valor = 0;
    for (int i = 0; i < 4; i++) {
        valor = valorLedIzq + valorLedDer;
        valoresFilasLeds[i] = valor; // Guardo la fila que va hacia arriba
        valoresFilasLeds[(BYTE_SIZE - 1) - i] = valor; // Guardo la misma fila que va hacia abajo
        valorLedIzq = valorLedIzq/2;
        valorLedDer = valorLedDer*2;
    }

    for (int i = 0; i < 8; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valoresFilasLeds[i]);
    }

    // Ya asignados los desplazamientos mando la señal digital
    digitalWrite(pinLatch, HIGH);
    digitalWrite(pinLatch, LOW);
    Serial.println("Mostrando patron 2...");
}

void secuenciaFlecha() {
    byte valorInicial = B11110000;

    for (int i = 0; i < 4; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valorInicial);
        if(i != 3){ // Para que se repita el patron del medio (no desplazo)
            valorInicial = (valorInicial >> 1);
        }
    }
    for (int i = 0; i < 4; i++) {
        shiftOut(pinData, pinClock, LSBFIRST, valorInicial);
        valorInicial = (valorInicial << 1);
    }
    // Ya asignados los desplazamientos mando la señal digital
    digitalWrite(pinLatch, HIGH);
    digitalWrite(pinLatch, LOW);
    Serial.println("Mostrando patron 4...");
}
