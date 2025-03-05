#include <ESP32Servo.h>
#define PULSOMIN 750
#define PULSOMAX 2400
Servo servoX;
Servo servoY;
const int ldr1 = 34;
const int ldr2 = 35;
const int ldr3 = 32;
const int ldr4 = 33;
const int ldr5 = 25;
const int servoPinX = 18;
const int servoPinY = 19;
int posicionX = 90;
int posicionY = 90;
int umbral = 50;
int A=0;
int E=0;

void setup() {
    Serial.begin(115200);
    servoX.attach(servoPinX);
    servoY.attach(servoPinY);
    servoX.write(posicionX);
    servoY.write(posicionY);
    delay(1000);
}

void loop() {
  int valor1 = analogRead(ldr1);
  int valor2 = analogRead(ldr2);
  int valor3 = analogRead(ldr3);
  int valor4 = analogRead(ldr4);
  int valor5 = analogRead(ldr5);
  int derecha = valor2;
  int izquierda = valor4;
  int abajo = valor1;
  int arriba= valor3;
  int tope= valor5;

  Serial.print("Derecha: "); Serial.println(derecha);
  Serial.print("Izquierda: "); Serial.println(izquierda);
  Serial.print("Arriba: "); Serial.println(arriba);
  Serial.print("Abajo: "); Serial.println(abajo);
  //Serial.print("tope: "); Serial.println(tope);

  if (izquierda > 1000) {
    posicionX = max(posicionX - 5, 0);
  } 
  
  if (derecha > 1000){
    posicionX = min(posicionX + 5, 180);
  } 

  if (arriba > 1000) {
    posicionY = max(posicionY + 5, 0);
  } 
  
  if (abajo > 900) {
    posicionY = min(posicionY - 5, 180);
  }

  if (tope > 900){
    posicionY = posicionY;
    posicionX = posicionX;
  }

  servoX.write(posicionX);
  servoY.write(posicionY);

  delay(50); 
}