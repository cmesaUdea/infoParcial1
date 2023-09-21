void setup(){
    pinMode(pinData, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinClock, OUTPUT);
    Serial.begin(9600);
}





void secuenciaRombo() {
  int valoresFilasLeds[BYTE_SIZE];
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
      //Serial.println(valorInicial);
      valorInicial = (valorInicial >> 1);
      //Serial.println(valorInicial);
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


