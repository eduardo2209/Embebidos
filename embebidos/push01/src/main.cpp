#include <Arduino.h>

//DEFINICIONES
#define LED1 23
#define BOTON1 22
#define LED2 21
#define BOTON2 19
int apachurrado1=0;
int apachurrado2=0;

void setup() { //CONFIGURACIONES
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(BOTON1, INPUT_PULLUP);
  pinMode(BOTON2, INPUT_PULLUP);
  //configurar la velocidad de transmisión en la terminal
  Serial.begin(115200); 
  Serial.println("Finalizan Configuraciones"); 
}

void loop() { //BUCLE PRINCIPAL
  apachurrado1=digitalRead(BOTON1);
  apachurrado2=digitalRead(BOTON2);
  if(!apachurrado1 && !apachurrado2){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    Serial.print("Hola if 1");
    delay(500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    Serial.println(" Mundo");
    delay(500);
  } else if (!apachurrado1 && apachurrado2){
    digitalWrite(LED1, HIGH);
    Serial.print("Hola if 2");
    delay(500);
    digitalWrite(LED1, LOW);
    Serial.println(" Mundo");
    delay(500);
  } else if (apachurrado1 && !apachurrado2){
    digitalWrite(LED2, HIGH);
    Serial.print("Hola if 3");
    delay(500);
    digitalWrite(LED2, LOW);
    Serial.println(" Mundo");
    delay(500);
  }
  else{
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  } 
}