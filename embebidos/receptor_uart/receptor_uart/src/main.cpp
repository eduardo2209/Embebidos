#include <Arduino.h>
HardwareSerial mySerial(0);

int valor=-1;
int LEDS[] = {33, 25, 13, 14, 12, 26, 27};
const int NUMEROS[11][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}, // 9
  {0, 0, 0, 0, 0, 0, 0}  // Vacío
};

void escribirNumero(char B) {
    valor = B - '0'; // Convertir char a int
    for (int j = 0; j < 7; j++) {
        digitalWrite(LEDS[j], NUMEROS[valor][j]);
    }
}

void setup() {
    Serial.begin(115200);      // Para depuración
    mySerial.begin(9600, SERIAL_8N1, 3, 1); // UART1 en pines 16 (TX) y 17 (RX)
}

void loop() { 
/* if (mySerial.available()) {
    String receivedText = mySerial.readStringUntil('\n');
    Serial.println(receivedText);
}*/

    if (mySerial.available()) {
        String mensaje = mySerial.readStringUntil('\n'); // Lee hasta nueva línea
        Serial.print("Recibido: ");
        Serial.println(mensaje); // Muestra el mensaje en Serial
        escribirNumero(mensaje);
    }
}