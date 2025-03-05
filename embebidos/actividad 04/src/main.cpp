/*#include <WiFi.h>       // Biblioteca para manejar Wi-Fi
#include <WiFiClient.h> // Biblioteca para manejar clientes Wi-Fi
#include <WiFiAP.h>     // Biblioteca para manejar puntos de acceso Wi-Fi
#include "BluetoothSerial.h" // BIBLIOTEC APARA BLUETOOTH 
#include <Arduino.h>

//DEFINICIONES

// Configuración del Wi-Fi
const char *ssid = "Equipo 5"; // Nombre del punto de acceso Wi-Fi
const char *password = "equipocinco"; // Contraseña del punto de acceso Wi-Fi
WiFiServer server(80); // Servidor web en el puerto 80

//estas lineas son para revisar y activar la conexion bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta habilitado
#endif

//esta linea si puede hacer una conexion serial por bluetooth
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Comunicacion Serial Bluetooth no habilitada
#endif

#define LED1 26
#define BOTON1 5
#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
int LEDS[] = {22, 23, 32, 33, 12, 17, 18, 19, 25, 27, 14, 21,}; 
char recibidoChar;
const char encender = 'A';
const char apagar = 'B';
int D1 = 16;
int D2 = 2;
int apachurrado=0;
int lecturaPU=0;
int lecturaV1=0;
int lecturaV2=0;
int band=0;
int valor=0;
int AL=0;
int i=0;
int cont=0;
int k=0;
int wf = 0;
int bt = 0;
int banderas[20];
const int touchPin1 = 15; // Pin táctil
const int touchPin2 = 13; // Pin táctil
const int touchPin3 = 4; // Pin táctil
unsigned long touchTime = 0; 
unsigned long touchTimePU = 0; 
unsigned long touchTimeV1 = 0; 
unsigned long touchTimeV2 = 0; // Tiempo en que se detectó el toque
const unsigned long functionDuration = 2000; // Duración en milisegundos
bool ejecutar = false; // Bandera para controlar la ejecución de la función
int touchCount=0;
unsigned long startTime; // Tiempo de inicio de la ejecución
unsigned long displayDuration = 1000; // Duración de cada despliegue en milisegundos


//objeto bluetooth, esto para establecer conexion bluetooth
BluetoothSerial SerialBT;

// Arreglo de patrones para representar caracteres en el display
int P[5][12] = { 
  //  a  b  c  d  e  f  h  j  k  m  n  p  
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0 },  // P
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)  
  {  1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },  // U
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
};

int V1[5][12] = { 
  //  a  b  c  d  e  f  h  j  k  m  n  p
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1 },  // V
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },  // 1
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
};

int V2[5][12] = { 
  //  a  b  c  d  e  f  h  j  k  m  n  p
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1 },  // V
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0 },  // 2
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
};


/*int Vacio[5][12] = { 
  //  a  b  c  d  e  f  h  j  k  m  n  p
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
  {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // (Espacio)
};

//FUNCIONES ANALOGAS 
void escribirNumero(int valor, int B) {
    if (B==1){ //PU
      for (int j = 0; j < 12; j++) {
        digitalWrite(LEDS[j], (valor == -1 || P[valor][j] == 0) ? LOW : HIGH);
      }
    } else if (B==2){//V1
      for (int j = 0; j < 12; j++) {
        digitalWrite(LEDS[j], (valor == -1 || V1[valor][j] == 0) ? LOW : HIGH);
      }
    } else if (B==3){ //V2
      for (int j = 0; j < 12; j++) {
        digitalWrite(LEDS[j], (valor == -1 || V2[valor][j] == 0) ? LOW : HIGH);
      }
    } 
}
  ////// FUNCION ANALOGA 
void cambiodedigito(int B) {
      //Habilita solo el digito 1
      digitalWrite(D1,HIGH);
      digitalWrite(D2,LOW);
      valor=1;
      escribirNumero(valor, B);
      delay(1);
      //Habilita solo el digito 2
      digitalWrite(D1,LOW);
      digitalWrite(D2,HIGH);
      valor=3;
      escribirNumero(valor, B);  
      delay(1);         
      digitalWrite(D1,LOW);
      digitalWrite(D2,LOW);
      //delay(50);
}


void setup() { //CONFIGURACIONES ANALOGAS 
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);
  pinMode(LED1, OUTPUT); 
  pinMode(BOTON1, INPUT_PULLDOWN);
  Serial.begin(115200);
  pinMode(touchPin1, INPUT);
  pinMode(touchPin2, INPUT);
  pinMode(touchPin3, INPUT);
  for (int i = 0; i < 12; i++) {  // Configurar todos los pines como salida
    pinMode(LEDS[i], OUTPUT);
  }
  i=-1;
  k=0;
  ///////////////////////////////////////////////////
//WIFI

// Inicialización serial
  Serial.begin(115200);
  Serial.println();

  // Configuración Wi-Fi
  Serial.println("Configurando punto de acceso...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Direccion IP: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Servidor iniciado");
////////////////////////////////////////////////////////////////////////////////////////////////////
  //configuraciones bluetooth
Serial.begin(115200);
SerialBT.begin("Alarma equipo 05"); //nombre de la conexion de la alarma 
Serial.println("para encender la alarma envia 'A'");
Serial.println("para apagar la alarma envia 'B'");
pinMode(D1,OUTPUT);//salidas de los pines 
pinMode(D2,OUTPUT);
pinMode(LED1,OUTPUT);


}

void loop() { //BUCLE PRINCIPAL
//almacenar el caracter leído de la terminal
  recibidoChar =(char)SerialBT.read(); 

//bluetooth

if (Serial.available())//si la comunicacion esta habilitada, lee la informacion que llega al puerto serial
{
  SerialBT.write(Serial.read());
}
if (SerialBT.available())
{
  SerialBT.println("recibido:"); //mandar un mensaje bt
  SerialBT.println(recibidoChar); //escribe el menssaje que se mando
  Serial.println("recibido"); //mandar elmensaje por serial
  Serial.println(recibidoChar); // escribri el char que se mando
}
if (recibidoChar == encender)// si se detectecta el char correcto
{
  SerialBT.println("ALARMA ENCENDIDA ");
  Serial.println("ALARMA ENCENDIDIA ");
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(LED1,HIGH);
  bt=1;
}
if (recibidoChar == apagar)
{
  SerialBT.println("ALARMA APAGADA ");
  Serial.println("ALARMA APAGADA ");
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(LED1,LOW);
  bt=0;
}
else
{// SI NO ES UN CARACTER VALIDO MANDA MENSAJE 
  SerialBT.println("CARACTER NO VALIDO");
  Serial.println("CARACTER NO VALIDO");
}

/////////////////////////////////////////////////////////////////////////////////////////////////7
// WIFI 
 // Manejo de clientes Wi-Fi
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/H\">aqui</a> para activar la alarma.<br>");
            client.print("Click <a href=\"/L\">aqui</a> para desactivar la alarma.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Procesar comandos
        if (currentLine.endsWith("GET /H")) {
          wf = 1; // Activar alarma

          Serial.println("Alarma Activada");
          client.println("<html><body><h1>Alarma Activada</h1></body></html>");
        }
        if (currentLine.endsWith("GET /L")) {
          wf = 0; // Desactivar alarma
          Serial.println("Alarma Desactivada");
         
          client.println("<html><body><h1>Alarma Desactivada</h1></body></html>");
        }
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");





}
  apachurrado = digitalRead(BOTON1);
  AL = apachurrado ? 1 : 0;
  int touchValuePU = touchRead(touchPin1);
  int touchValueV1 = touchRead(touchPin2);
  int touchValueV2 = touchRead(touchPin3);

  if(AL==1||wf == 1||bt == 1){
      
      Serial.println("ALARMA ACTIVADA");
      digitalWrite(LED1, HIGH);

      touchCount = 0;

        if (touchValuePU > 30 && touchCount < 3) {
            banderas[touchCount++] = 1; // PU
        }
        if (touchValueV1 > 30 && touchCount < 3) {
            banderas[touchCount++] = 2; // V1
        }
        if (touchValueV2 > 30 && touchCount < 3) {
            banderas[touchCount++] = 3; // V2
        }

        // Ejecutar función si hay toques
        if (touchCount > 0) {
            unsigned long startTime = millis(); // Marcar tiempo de inicio

            // Mostrar identificadores durante 1 segundo por cada uno
            for (int j = 0; j < touchCount; j++) {
                unsigned long displayStartTime = millis(); // Tiempo de inicio de despliegue
                while (millis() - displayStartTime < displayDuration) {
                    cambiodedigito(banderas[j]);
                    // Permitir que el programa realice otras tareas
                    delay(10); // Pequeña espera para evitar bloqueos
                }
            }
            // Restablecer el estado al final del despliegue
            for (int j = 0; j < 12; j++) {
                digitalWrite(LEDS[j], LOW); 
            }
        }
  } else {
    digitalWrite(LED1, LOW);
    Serial.println("ALARMA DESACTIVADA");
  }

  

}
*/


//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
//definimos los pines que se usaran para los segmentos del display
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
                          { 0,0,0,0,0,0,1 },    // -
                          { 1,1,0,1,1,0,1 },    // 2
                          { 0,0,0,0,1,1,0 },    // 1
                          { 1,1,1,0,0,1,1 },    // 9
                          { 1,0,1,1,0,1,1 },    // 5
                          { 0,0,0,0,0,0,1 },    // -
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,0,1,1,1,1,1 },    // 6
                          { 0,0,0,0,1,1,0 },    // 1
                          { 0,0,0,0,0,0,1 },    // -
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
                          { 0,0,0,0,0,0,1 }};    // -
                          
                         
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