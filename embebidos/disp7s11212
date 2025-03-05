//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
//definimos los pines que se usarán para los segmentos del display
int LEDS[]={4,5,18,19,21,22,23};
int i=0; //variable global i

//CONFIGURACIONES
void setup() {
  for (i=0; i<7; i++){
    pinMode(LEDS[i], OUTPUT);
  }
}

//BUCLE PRINCIPAL
void loop() {
  for (i=0; i<7; i++){ //iterar del 0 al 6
    digitalWrite(LEDS[i], HIGH); //definir el pin correspondiente en estado alto
    delay(200); //retraso de 100ms
  }

  delay(500); //esperar medio segundo

  for (i=0; i<7; i++){ //iterar del 0 al 6
    digitalWrite(LEDS[i], LOW); //definir el pin correspondiente en estado bajo
    delay(200);
  }
  delay(500);
}
