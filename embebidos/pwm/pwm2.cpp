//CABECERAS
#include <Arduino.h>

//DEFINICIONES
#define LED 23

// Parametros del canal 0
const int frec = 1000; /*     El ciclo de trabajo es de
                              1000 Hz, o sea 1ms
                        */
const int canal = 0; //Usaremos el Canal 0 del PWM
const int resolucion = 8; /*  resolucion de 8 bits
                              El ciclo de trabajo va desde
                              0 (0%) hasta 255 (100%)
                          */

//FUNCIONES

//CONFIGURACIONES
void setup() {
  /* Configurar la funcion que controla LEDs en el canal 0 
   * de PWM
   */
  ledcSetup(canal, frec, resolucion);

  /* Conectar el canal 0 de PWM al pin 23 usando la funcion 
   * que controla LEDs con PWM
  */
  ledcAttachPin(LED, canal);
}

//PRINCIPAL
void loop() {
  // Incrementar el brilo del LED de 1 en 1, hasta alcanzar 255
    for(int cicloTrabajo = 0; cicloTrabajo <= 255; cicloTrabajo++){
				//escribir en el pin que esta conectado al canal 0, el
				//valor del ciclo de trabajo especificado
        ledcWrite(canal, cicloTrabajo);
        delay(10);
    }
  /*Una vez que se alcanzo el brillo máximo, reducir el brilo del
   * LED de 1 en 1
  */
    for(int cicloTrabajo = 255; cicloTrabajo >= 0; cicloTrabajo--){
        ledcWrite(canal, cicloTrabajo);
        delay(10);
    }
}
