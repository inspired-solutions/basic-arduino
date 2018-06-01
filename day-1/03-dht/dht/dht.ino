#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int converted = map(h, 70, 92, 0, 255);

  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.print("    ");
  Serial.print("Temperature = ");
  Serial.println(t);
  
  analogWrite(9, converted);
  if (t > 23) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
}
