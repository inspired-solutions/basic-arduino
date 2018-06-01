#include <Servo.h>
Servo myservo;


int pos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  myservo.attach(8);
}

void loop() {
  
  if (Serial.available() > 0 ) {
    int rec = Serial.parseInt();

    myservo.write(rec);
  }
  // put your main code here, to run repeatedly:
}
