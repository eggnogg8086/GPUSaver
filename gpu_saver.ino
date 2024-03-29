#include <GyverMAX6675.h>

#define CLK_PIN   13 
#define DATA_PIN  9 
#define CS_PIN    8 

unsigned long previousMillis = 0; 
const long interval = 1000;  


int sensorPin = A5; 
int buttonPin = 11;
int sensorValue = 0; 
int buttonState = LOW;

// перед подключением библиотеки можно
// задать задержку переключения CLK в микросекундах
// для увеличения качества связи по длинным проводам
//#define MAX6675_DELAY 10

GyverMAX6675<CLK_PIN, DATA_PIN, CS_PIN> sens;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(10, LOW);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  buttonState = digitalRead(buttonPin);

  if(buttonState == LOW) digitalWrite(10, HIGH);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (sens.readTemp()) {            // Читаем температуру
      Serial.print("Temp: ");         // Если чтение прошло успешно - выводим в Serial
      Serial.print(sens.getTemp());   // Забираем температуру через getTemp
      Serial.print(" *C volts: ");

      Serial.println(sensorValue* 15.25/1023);
    } else Serial.println("Error");   // ошибка чтения или подключения - выводим лог
  }


  if((sensorValue* 15.25/1023) > 1.25){
    digitalWrite(10, LOW);
    Serial.println(sensorValue* 15.25/1023);
  }
}
