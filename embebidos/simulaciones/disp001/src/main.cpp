/*DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
//definimos los pines que se usarán para los segmentos del display
int LEDS[]={4,5,18,19,21,22,23};
int i=0; //variable global i

//CONFIGURACIONES
void setup() {
  for (i=0; i<7; i++){
    pinMode(LEDS[i], OUTPUT);
  }
}

//BUCLE PRINCIPAL
void loop() {
  for (i=0; i<7; i++){ //iterar del 0 al 6
    digitalWrite(LEDS[i], HIGH); //definir el pin correspondiente en estado alto
    delay(500); //retraso de 100ms
     digitalWrite(LEDS[i], LOW);
     //delay(10);
  }

  delay(500); //esperar medio segundo

 /* for (i=0; i<7; i++){ //iterar del 0 al 6
    digitalWrite(LEDS[i], LOW); //definir el pin correspondiente en estado bajo
    delay(200);
  }
  delay(5);
}*/



//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
//definimos los pines que se usarán para los segmentos del display
//int LEDS[]={23,22,21,19,18,5,4};
int LEDS[] = {4,5,18,19,21,22,23};
int i,j=0; //variable global i
int valor=0; //variable global para compartir valores
                          //a b c d e f g
int arreglo[36][7] = {    { 1,1,0,1,1,0,1 },    // 2
                          { 0,0,0,0,1,1,0 },    // 1
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,0 },    // 0
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 1,1,1,1,1,1,1 },    // 8
                          { 0,0,0,0,1,1,0 },    // 1
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,0,1,1,0,1 },    // 2
                          { 0,0,0,0,1,1,0 },    // 1
                          { 1,1,1,0,0,1,1 },    // 9
                          { 1,0,1,1,0,1,1 },    // 5
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,0,1,1,1,1,1 },    // 6
                          { 0,0,0,0,1,1,0 },    // 1
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,0,1,1,0,1 },    // 2
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,0,1,1,0,1 },    // 2
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,1,1,1 },    // 8
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,1,0,0,1 },    // 3
                          { 0,1,1,0,0,1,1 },    // 4
                          { 1,1,1,1,1,1,1 },    // 8
                          { 0,0,0,0,0,0,0 },    // espacio
                          { 1,1,1,1,1,1,1 },    // 8
                          { 0,0,0,0,0,0,0 }};    // espacio
                          
                         
//FUNCIONES
void escribirNumero(int valor){
  for (j=0; j<7; j++){
    //recorrer cada pin y asignarle los valores correspondientes
    digitalWrite(LEDS[j], arreglo[valor][j]);
    //delay (50);
   //for (int a =0; a<7; a++){ //iterar del 0 al 6
    //digitalWrite(LEDS[j], HIGH); //definir el pin correspondiente en estado alto
    //delay(100); //retraso de 100ms 
   //digitalWrite(LEDS[j], LOW); //definir el pin correspondiente en estado alto
    //delay(50); //retraso de 100ms 
   }//delay(500);
  }


//CONFIGURACIONES
void setup() {
  for (i=0; i<7; i++){
    //recorrer cada pin y configurarlo como salida
    pinMode(LEDS[i], OUTPUT);
    //delay(500);
  }
}

void loop() {
  for (i=0; i<36; i++){
    //ir mostrando el valor del numero "i" en el display
    escribirNumero(i);
    delay(300);
  }
}




/* DECLARACIONES
#include <Arduino.h>

// DEFINICIONES
// Definimos los pines que se usarán para los segmentos del display
int LEDS[] = {15, 2, 4, 16, 17, 5, 18, 19, 21, 22, 23, 34, 35, 32}; 

// Arreglo de patrones para representar caracteres en el display
int arreglo[][14] = { 
  //  a  b  c  d  e  f  g  h  i  j  k  l  m  n
  {  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
  {  1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 },  // I
  {  1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },  // S
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
    digitalWrite(LEDS[j], (valor == -1 || arreglo[valor][j] == 0) ? LOW : HIGH);
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
  for (int i = 0; i < 16; i++) {
    parpadearNumero(i, 5, 500); // Parpadea cada número 5 veces con un total de 500 ms
    delay(500); // Espera más larga entre cada número (500 ms)
  }
}  */


