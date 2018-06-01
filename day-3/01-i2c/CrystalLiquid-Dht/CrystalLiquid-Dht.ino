#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_PCF8574 lcd(0x3F);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int show;

void setup() {
  int error;
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(9600);
  Serial.println("LCD...");

  while (! Serial);

  Serial.println("Dose: check for LCD");
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd.begin(16, 2); // initialize the lcd
  show = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();

  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temp:");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("hum:");
  lcd.print(hum);
  delay(1000);
}
