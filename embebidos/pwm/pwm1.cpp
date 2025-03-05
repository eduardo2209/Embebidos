//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
#define LED 23
int brillo = 0;
int incremento = 10;

//FUNCIONES

//CONFIGURACIONES
void setup() {



  
}
 /* se suma el el valor de brillo que en principio es 0 al de incremento que es 10,
  ahora brillo vale 10 y asi sucesivamente, (brillo = 0,10,20,30,40...n), al desvordarse
   incia de nuevo en cero y asi hasta volver a desvordearse. no hay nada en el void setup
   ya que estamos escribiendo una señal analoga
 */

//PRINCIPAL
void loop() {
  analogWrite(LED,brillo);
  brillo= brillo+incremento;
  delay(50);
}
