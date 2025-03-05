// DECLARACIONES
#include <Arduino.h>

// DEFINICIONES
// Definimos los pines que se usarán para los segmentos del display
int LEDS[] = {15, 2, 4, 16, 17, 5, 18, 19, 21, 22, 23, 34, 35, 32}; 

// Arreglo de patrones para representar caracteres en el display
int arreglo[][14] = { 
  //  a  b  c  d  e  f  g  h  i  j  k  l  m  n
  {  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } ,
  {  0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },  // I
  {  0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },  // S
  {  0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },  // A
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },  // F
  {  0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },  // E
  {  0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 },  // R
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },  // V
  {  0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },  // I
  {  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },  // O
  {  1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },  // L
  {  0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },  // E
  {  0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },  // T
  {  0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },  // A
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }   // (Espacio)
};

// FUNCIONES
void escribirNumero(int valor) {
  for (int j = 0; j < 14; j++) {
    // Para un display de cátodo común:
    // - Encender segmento: HIGH
    // - Apagar segmento: LOW
    digitalWrite(LEDS[j], (valor == -1 || arreglo[valor][j] == 0) ? HIGH : LOW);
  }
}

void parpadearNumero(int valor, int repeticiones, int tiempo) {
  for (int k = 0; k < repeticiones; k++) {
    escribirNumero(valor);  // Encender el número
    delay(tiempo);          // Espera corta
    escribirNumero(-1);     // Apagar el número
    delay(tiempo);          // Espera corta
  }
}

// CONFIGURACIONES
void setup() {
  for (int i = 0; i < 14; i++) {  // Configurar todos los pines como salida
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 1; i++) {
    parpadearNumero(i, 5, 500); // Parpadea cada número 5 veces con un total de 500 ms
    delay(500); // Espera más larga entre cada número (500 ms)
  }
}


