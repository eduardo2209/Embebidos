#include <Arduino.h>
#include <Keypad.h>


HardwareSerial mySerial(1); // Usar UART1

#define SWM 23
#define SWE 22
#define D 32
const int laserPin = 21; // Pin conectado al láser
//const int photodiodePin = 13;
const byte ROWS = 4; // Número de filas
const byte COLS = 3; // Número de columnas
int aswm=0;
int aswe=0;
//int D = 32;
int valor = -1;
int V = -1;
int LEDS[] = {33, 25, 13, 14, 12, 26, 27}; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
unsigned long displayDuration = 1000;
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

byte rowPins[ROWS] = {19, 18, 5, 17}; // Pines de las filas
byte colPins[COLS] = {16, 4, 15}; // Pines de las columnas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void escribirNumero(char B) {
    if (B=='0'){ valor=0;
    } else if (B=='1'){ valor=1;
    } else if (B=='2'){ valor=2;
    } else if (B=='3'){ valor=3;
    } else if (B=='4'){ valor=4;
    } else if (B=='5'){ valor=5;
    } else if (B=='6'){ valor=6;
    } else if (B=='7'){ valor=7;
    } else if (B=='8'){ valor=8;
    } else if (B=='9'){ valor=9;
    }
    V = valor;
    for (int j = 0; j < 7; j++) {
        digitalWrite (LEDS [j], NUMEROS[valor][j]);
      }
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600, SERIAL_8N1, 3, 1); // RX, TX para UART1
  pinMode(laserPin, OUTPUT);
  for (int i = 0; i <7; i ++) {
     pinMode ( LEDS [i] , OUTPUT) ;
  }
  pinMode(SWM, INPUT_PULLDOWN);
  pinMode(SWE, INPUT_PULLDOWN);
  pinMode(D, OUTPUT); 

  //pinMode(photodiodePin, INPUT);
  //Serial.println("Receptor Iniciado");
}

void loop() {
  aswm = digitalRead(SWM);
  aswe = digitalRead(SWE);

  if(aswm){
    //MAESTRO: solo recibe información a través del teclado
    //Trasmite con láser
 
    char key = keypad.getKey();
    if (key) {
      Serial.println(key);
      delay(1);
    }
    //Recibido y transmitido
    unsigned long displayStartTime = millis(); 
    while (millis() - displayStartTime < displayDuration) {
      digitalWrite(D,LOW);
      escribirNumero(key);
      delay(1); 
    }

    //Transmisión
    //Push
      mySerial.print(V);
      digitalWrite(laserPin, HIGH);
      delay(100);
      digitalWrite(laserPin, LOW);
      delay(100);

  } else if(aswe){
    //ESCLAVO: solo recibe información a través del receptor óptico (antena parabólica)
    //Replican información mediante clúster
    
    //Recepción
    /*if (digitalRead(photodiodePin) == HIGH) {
      char c = mySerial.read();
      Serial.write(c);
    }*/
    //Escribir en display

    //Replicación con push
    // Retransmisión de datos de Serial a softSerial
    /*if (Serial.available()) {
      char c = Serial.read();
      softSerial.write(c);
    }
    // Retransmisión de datos de softSerial a Serial
    if (softSerial.available()) {
      char c = softSerial.read();
      Serial.write(c);
    }*/

  } else {
    //Todo apagado
    valor=10;
    for (int j = 0; j < 7; j++) {
        digitalWrite(LEDS[j], NUMEROS[valor][j]); 
    }
  }
}

