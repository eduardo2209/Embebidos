#include <Arduino.h>
//#include "BluetoothSerial.h"
#include <ESP32Servo.h>
// Revisar si el Bluetooth está habilitado en la configuración
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth no está habilitado
#endif

// Revisar si la comunicación serial por Bluetooth está habilitada
#if !defined(CONFIG_BT_SPP_ENABLED)
    #error Comunicación Serial Bluetooth no habilitada
#endif

BluetoothSerial SerialBT; // Creación de una instancia de BluetoothSerial

///////////////////////////////////////// variables 
String estado = "";

/////////////////////////////////////
// Velocidad máxima de los motores
int velocidadMAX = 255;

//////////////////////////////////////// MOTOR DERECHO
int velocidadDerecha = velocidadMAX;
int canal1MotorD = 0;  // Canal PWM motor derecho
int canal2MotorD = 1;  // Canal PWM motor derecho

///////////////////////////////////// puente H L298N (Motor derecho)
const int IN1 = 26;  // Dirección Motor derecho
const int IN2 = 25;  // Dirección Motor derecho
const int ENA = 14;  // Pin de habilitación para el motor derecho (PWM)

//////////////////////////////////////// MOTOR IZQUIERDO
int velocidadIzquierda = velocidadMAX;
int canal1MotorI = 2;  // Canal PWM motor izquierdo
int canal2MotorI = 3;  // Canal PWM motor izquierdo

///////////////////////////////////// puente H L298N (Motor izquierdo)
const int IN3 = 33;  // Dirección Motor izquierdo
const int IN4 = 32;  // Dirección Motor izquierdo
const int ENB = 13;  // Pin de habilitación para el motor izquierdo (PWM)

//////////////////////////////////////// PWM comunicación
const int frecuencia = 10000;  // Frecuencia PWM
const int resolucion = 8;      // Resolución PWM (8 bits)
#define PULSOMIN 750
#define PULSOMAX 2400
Servo servoX;
Servo servoY;

const int ldr2 = 35;

const int ldr4 = 27;
const int ldr5 = 34;
//const int servoPinX = 18;
//const int servoPinY = 19;
int posicionX = 45;
int posicionY = 90;
int umbral = 50;
int A=0;
int E=0;

// Declaración de prototipos de función
void serialEvent();
void adelante();
void atras();
void de();
void iz();
void detener();
void giroHorario(int canal1, int canal2, int cv);
void giroAntihorario(int canal1, int canal2, int cv);
void pararMotor(int canal1, int canal2);

void setup() {
  SerialBT.begin("Carro_Conectado");
  // Configurar los pines de dirección como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configurar PWM en los pines de habilitación (ENA, ENB)
  ledcSetup(canal1MotorD, frecuencia, resolucion);
  ledcAttachPin(ENA, canal1MotorD);
  //////////////////////
  ///ledcSetup(canal2MotorD, frecuencia, resolucion);
  ledcSetup(canal1MotorI, frecuencia, resolucion);
  ledcAttachPin(ENB, canal1MotorI);
  
    Serial.begin(115200);
    //servoX.attach(servoPinX);
    //servoY.attach(servoPinY);
    //servoX.write(posicionX);
    //servoY.write(posicionY);
    delay(1000);

}

void loop() {

  
  int valor2 = analogRead(ldr2);
 
  int valor4 = analogRead(ldr4);
  int valor5 = analogRead(ldr5);
  int derecha = valor2;
  int izquierda = valor4;
  

  int tope= valor5;

  Serial.print("Derecha: "); Serial.println(derecha);
  Serial.print("Izquierda: "); Serial.println(izquierda);
  Serial.print("tope: "); Serial.println(tope);
  
  //Serial.print("tope: "); Serial.println(tope);
if (tope > 0){
    //posicionY = posicionY;
    //posicionX = posicionX;
    adelante();
  } 

  if (izquierda > 200) {
    //posicionX = max(posicionX - 5, 0);
     de();
  } 
  
  if (derecha > 100){
    //posicionX = min(posicionX + 5, 180);
  
     iz();
  } 


  delay(50); 



    /*if (estado == "F") {
      adelante();
      
    }// atrás
    if (estado == "B") {
      atras();
    }// derecha (antes era un if con estado == "")
    if (estado == "R") {
      derecha();
    }// izquierda
    if (estado == "L") {
      izquierda();
    }// parar
    if (estado == "S") {
      detener();
    }
    estado = "";*/
  //delay(250);
  //detener();

}

//////////////////////// Recepción de datos
void serialEvent() {
  while (SerialBT.available()) {
    char inChar = (char) SerialBT.read();
    estado += inChar;
  }
}
///////////// Funciones para las direcciones
void adelante() {
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  giroHorario(canal1MotorD,canal2MotorD,velocidadDerecha);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  giroHorario(canal1MotorI,canal2MotorI,velocidadIzquierda);

}
void atras() {
   digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  giroHorario(canal1MotorD, canal2MotorD, velocidadDerecha);

  // Motor izquierdo en sentido antihorario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  giroHorario(canal1MotorI, canal2MotorI, velocidadIzquierda);
  
}
void de() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  giroHorario(canal1MotorD,canal2MotorD,velocidadDerecha);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  giroAntihorario(canal1MotorI,canal2MotorI,velocidadIzquierda);
  
}
void iz() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  giroAntihorario(canal1MotorD,canal2MotorI,velocidadDerecha);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  giroHorario(canal1MotorI,canal2MotorI,velocidadIzquierda);
  

}
void detener() {
  pararMotor(canal1MotorD, canal2MotorD);
  pararMotor(canal1MotorI, canal2MotorI);
  
}
//////////////////////// Funciones de giro
void giroHorario(int canal1, int canal2, int cv) {
  ledcWrite(canal1, cv);
  ledcWrite(canal2, 0);
}
void giroAntihorario(int canal1, int canal2, int cv) {
  
 ledcWrite(canal1, 0);   // Desactiva el canal1
  ledcWrite(canal2, cv);  // Activa el canal2 (PWM) con la velocidad

}
void pararMotor(int canal1, int canal2) {
  ledcWrite(canal1, 0);
  ledcWrite(canal2, 0);
}