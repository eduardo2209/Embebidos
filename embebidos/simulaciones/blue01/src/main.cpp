//DECLARACIONES
#include <Arduino.h>
#include "BluetoothSerial.h"

//DEFINICIONES

//revisar si la tarjeta tiene Bluetooth habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta habilitado
#endif

//revisar si la tarjeta puede hacer comunicación serial por Bluetooth
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Comunicacion Serial Bluetooth no habilitada
#endif

int recibido;// variable para guardar el caracter recibido como entero
char recibidoChar;// el valor recibido como CHAR se guarda aqui
const char encender1 ='A'; //definir el caracter para encender el LED
const char apagar1 ='B'; //definir el caracter para apagar el LED
const char encender2 ='C'; //definir el caracter para encender el LED
const char apagar2 ='D'; //definir el caracter para apagar el LED
#define LED1 23 //definir el pin donde está conectado el LED
#define LED2 22

// crear objeto SerialBT que representa la conexion BT
BluetoothSerial SerialBT;

//CONFIGURACIONES
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Equipo 5"); // nombre del dispositivo BT
  Serial.println("Dispositivo iniciado, ahora puede conectarlo por BT");
  Serial.println("Para encender el LED, envie: led1");
  Serial.println("Para apagar el LED, envie: led0");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

//BUCLE PRINCIPAL
void loop() {
  //almacenar el caracter leído de la terminal
  recibidoChar =(char)SerialBT.read(); 

  if (Serial.available()) { // si la comunicación serial está habilitada
    // leer la información que llega por el puerto serial y escribirla en el puerto serial BT
    SerialBT.write(Serial.read()); 
  }
  if (SerialBT.available()) { // si la comunicación BT serial está habilitada
    SerialBT.print("Recibido:");// mandar mensaje por BT
    SerialBT.println(recibidoChar);// escribir el caracter que se recibio     
    Serial.print ("Recibido:");// mandar mensaje por serial
    Serial.println(recibidoChar);// escribir el caracter que se recibio     

    if(recibidoChar == encender1) { // si se detecta el caracter para encender el LED...
      SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      digitalWrite(LED1, HIGH);// encender el LED
      }
    else if(recibidoChar == encender2) { // si se detecta el caracter para encender el LED...
      SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      digitalWrite(LED2, HIGH);// encender el LED
      }
    else if(recibidoChar == apagar1) { // si se detecta el caracter para apagar el LED...
      SerialBT.println("LED APAGADO:");// mandar mensaje por BT
      Serial.println("LED APAGADO:");// mandar mensaje por serial
      digitalWrite(LED1, LOW);// apagar el LED
      //digitalWrite(LED2, LOW);// apagar el LED
      }
    else if(recibidoChar == apagar2) { // si se detecta el caracter para apagar el LED...
      SerialBT.println("LED APAGADO:");// mandar mensaje por BT
      Serial.println("LED APAGADO:");// mandar mensaje por serial
      //digitalWrite(LED1, LOW);// apagar el LED
      digitalWrite(LED2, LOW);// apagar el LED
      }
    else { // si no es ninguno de los caracteres definidos
      SerialBT.println("CARACTER NO VALIDO");// mandar mensaje por BT
      Serial.println("CARACTER NO VALIDO");// mandar mensaje por serial
    }
    
  }
  delay(20);
}*/


/*
#include <Arduino.h>
btw hice este codigo antes de hacerlo con display // Definición de pines
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
  pinMode(ledPin,OUTPUT);
  Serial.begin(115206);

}

void loop() {
  // Leer valor de la fotoresistencia (0 a 4095)
  ldrValue = analogRead(ldrPin);

  // Leer valor del potenciómetro (0 a 4095)
  potValue = analogRead(potPin);

  // Mapear valor del potenciómetro al rango de PWM (0-255)
  brightness = map(potValue, 0, 4095, 0, 255);


  // Controlar el LED según el nivel de luz detectado
  //if (ldrValue < umbral) {
    // Noche: controlar el brillo del LED
    ledcWrite(pwmChannel, brightness);
    Serial.println(brightness);
  //} else {
    // Día: apagar el LED
   // ledcWrite(pwmChannel, 0);
 // }

  delay(100);
}*/

#include <WiFi.h>       // Biblioteca para manejar Wi-Fi
#include <WiFiClient.h> // Biblioteca para manejar clientes Wi-Fi
#include <WiFiAP.h>     // Biblioteca para manejar puntos de acceso Wi-Fi

// Configuración del Wi-Fi
const char *ssid = "Equipo 5"; // Nombre del punto de acceso Wi-Fi
const char *password = "equipocinco"; // Contraseña del punto de acceso Wi-Fi
WiFiServer server(80); // Servidor web en el puerto 80

void setup() {

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
}

void loop() {
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
          AL = 1; // Activar alarma
          Serial.println("Alarma Activada");
          client.println("<html><body><h1>Alarma Activada</h1></body></html>");
        }
        if (currentLine.endsWith("GET /L")) {
          AL = 0; // Desactivar alarma
          Serial.println("Alarma Desactivada");
         
          client.println("<html><body><h1>Alarma Desactivada</h1></body></html>");
        }
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");
  }