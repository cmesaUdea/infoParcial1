void setup(){
    pinMode(pinData, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinClock, OUTPUT);
    Serial.begin(9600);
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


