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
