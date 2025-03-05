#include <Arduino.h>
//btw hice //este codigo antes de hacerlo con display // Definición de pines
#define ldrPin 34        // Pin para la fotoresistencia (ADC1_CH6)
#define potPin 35         // Pin para el potenciómetro (ADC1_CH7)
#define ledPin 2         // Pin para el LED (PWM)
int umbral = 2000; // Umbral para diferenciar día/noche (ajustable)
int potValue = 0;        // Valor del potenciómetro
int brightness = 0;      // Nivel de brillo del LED
int ldrValue = 0;        // Valor de la fotoresistencia

// Variables PWM para ESP32
#define pwmChannel 0
#define pwmFreq 5000
#define pwmResolution 8 // 8 bits para PWM (0-255)

void setup() {
  // Configuración de canal PWM
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(ledPin, pwmChannel);

}

void loop() {
  // Leer valor de la fotoresistencia (0 a 4095)
  ldrValue = analogRead(ldrPin);

  // Leer valor del potenciómetro (0 a 4095)
  potValue = analogRead(potPin);

  // Mapear valor del potenciómetro al rango de PWM (0-255)
  brightness = map(potValue, 0, 4095, 0, 255);


  // Controlar el LED según el nivel de luz detectado
  if (ldrValue < umbral) {
    // Noche: controlar el brillo del LED
    ledcWrite(pwmChannel, brightness);
  } else {
    // Día: apagar el LED
    ledcWrite(pwmChannel, 0);
  }
}