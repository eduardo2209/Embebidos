//CABECERAS
#include <Arduino.h>

//DECLARACIONES
#define LED 23

//CONFIGURACIONES
void setup() {
  pinMode(LED, OUTPUT); //configurar el LED de abordo como salida
  Serial.begin(115200); //habilitar la comunicación serial
  Serial.println("Termina configuración"); //mandar mensaje por serial
}

//BUCLE PRINCIPAL
void loop() {
    digitalWrite(LED, 1); //encender el LED de abordo
    Serial.print("Hola ");
    delay(500); //esperar 500ms
    digitalWrite(LED, 0); //apagar el LED de abordo
    Serial.println("Mundo");
    delay(500); //esperar 500ms
} 
