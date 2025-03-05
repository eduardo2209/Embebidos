//CABECERAS
#include <Arduino.h>

//DEFINICIONES
#define LED 23
#define BOTON 22
int apachurrado=0;

void setup() { //CONFIGURACIONES
  //configurar el LED de la tarjeta como salida
  pinMode(LED, OUTPUT); 
  //configurar el PIN donde está el PB
  pinMode(BOTON, INPUT_PULLDOWN);
  //configurar la velocidad de transmisión en la terminal
  Serial.begin(115200); 
  //imprimir mensaje en la terminal
  Serial.println("Finalizan Configuraciones"); 
}

void loop() { //BUCLE PRINCIPAL
/*   apachurrado=digitalRead(BOTON);
  if(apachurrado){
    //escribir valor digital alto en un pin
    digitalWrite(LED, HIGH);
    //mandar mensaje por la terminal serial
    Serial.print("Hola");
    //esperar 250 ms
    delay(500);
    //escribir valor digital bajo en un pin
    digitalWrite(LED, LOW);
    //mandar mensaje por la terminal serial
    Serial.println(" Mundo");
    //esperar 250 ms
    delay(500);
  }
  else{
    //escribir valor digital bajo en un pin
    digitalWrite(LED, LOW);
  } */
  digitalWrite(LED, HIGH);
  //mandar mensaje por la terminal serial
  Serial.print("Hola");
  //esperar 250 ms
  delay(50);
  //escribir valor digital bajo en un pin
  digitalWrite(LED, LOW);
  //mandar mensaje por la terminal serial
  Serial.println(" Mundo");
  //esperar 250 ms
  delay(50);
}
