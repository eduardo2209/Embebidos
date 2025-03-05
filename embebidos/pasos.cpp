//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
int bobina[]={23,22,21,19};
#define ldrPin 34 ;
int retraso=50;
int i,j=0;

int fase[4][4]={  {1,0,0,0},    //valor 0
                  {0,1,0,0},    //valor 1
                  {0,0,1,0},    //valor 2
                  {0,0,0,1}  }; //valor 3

//FUNCIONES
void paso(int valor){
  for(j=0;j<4;j++){
    digitalWrite(bobina[j], fase[valor][j]);
  }
}

//CONFIGURACIONES
void setup() {
  for(i=0;i<4;i++){
    pinMode(bobina[i], OUTPUT);
  }  
}

/*PRINCIPAL
void loop() {
  for(i=0;i<4;i++){
    paso(i);
    delay(retraso);
  }
  
}*/
void loop() {
  // Leer valor de la fotoresistencia (0 a 4095)
  float a = analogRead(ldrPin);

  // Leer valor del potenciómetro (0 a 4095)
  float b = analogRead(potPin);

  // Mapear valor del potenciómetro al rango de PWM (0-255)
  float brightness = map(potValue, 0, 4095, 0, 255);


  /*Controlar el LED según el nivel de luz detectado
  if (ldrValue < umbral) {
    // Noche: controlar el brillo del LED
    ledcWrite(pwmChannel, brightness);
  } else {
    // Día: apagar el LED
    ledcWrite(pwmChannel, 0);
  }
}*/