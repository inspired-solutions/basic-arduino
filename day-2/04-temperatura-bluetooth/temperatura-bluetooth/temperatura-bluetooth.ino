#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  Serial.begin(9600);  
  // put your setup code here, to run once:
 // pinMode(8, OUTPUT);
//  pinMode(6, INPUT);
}

void loop() {
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();
  
  Serial.print("*T");
  Serial.print(temp);
  Serial.print("*H");
  Serial.print(hum);


  
//  analogWrite(6,conversion1);
}
