void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  
  if (Serial.available() > 0 ) {
    char rec = Serial.read();
    if (rec == 's') {
      digitalWrite(13, HIGH);
    }
    if (rec == 'w') {
      digitalWrite(13, LOW);
    }
  }
  // put your main code here, to run repeatedly:
}
