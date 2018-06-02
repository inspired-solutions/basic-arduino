/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

LiquidCrystal_PCF8574 lcd(0x3F);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "INSPIRED"
#define WLAN_PASS       "y79%25!1@aZT"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "helpse"
#define AIO_KEY         "6480108c1ff84c6ea150b8570af5a204"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/envio");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/transmision");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
pinMode(D6,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(0x3F);
  lcd.begin(16, 2); // initialize the lcd
  Serial.begin(115200);
  Serial.println("Hello World");
  delay(10);
  // Connect to WiFi access point.


  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

uint32_t x = 0;
int lastValue = 0;
void loop() {
  Serial.println("Hello World");
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(2000))) {
    if (subscription == &onoffbutton) {
      lcd.setBacklight(255);
      lcd.home(); lcd.clear();
      lcd.print((char *)onoffbutton.lastread);
      String response = (char *)onoffbutton.lastread;
      int val = response.toInt();
      if (val == 1) {
        digitalWrite(D6,0);
        Serial.println(response);
        lcd.setBacklight(255);
      lcd.home(); lcd.clear();
      lcd.print("Se prende");
      }
      if (val == 0) {
        digitalWrite(D6,1);
        Serial.println(response);
        lcd.setBacklight(255);
      lcd.home(); lcd.clear();
      lcd.print("Se Apagau");
      }
    }
  }

  // Now we can publish stuff!
  //  if (digitalRead(D5) != lastValue){
  //      Serial.print(F("\nSending photocell val "));
  //      Serial.print(lastValue);
  //      Serial.print("...");
  //     photocell.publish(lastValue);
  //     lastValue = digitalRead(D5);
  // }


  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
    if(! mqtt.ping()) {
    mqtt.disconnect();
    }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
//  lcd.setBacklight(255);
//  lcd.home(); lcd.clear();
//  lcd.print("Conectando MQTT");
  Serial.println("Conectando MQTT");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
//    lcd.home(); lcd.clear();
//    lcd.print("Intentando MQTT");
//    lcd.home(); lcd.clear();
//    lcd.print("Conectando 5seg");
    Serial.print("conectando");
    mqtt.disconnect();
    delay(3000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
//  lcd.home(); lcd.clear();
//  lcd.print("yea Conectado");
  Serial.println("Conectado");
}
