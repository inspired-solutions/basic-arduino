void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(8) == 1) {
    Serial.print("Who is");
    digitalWrite(6, HIGH);
    delay(100);
  } else {
    Serial.print("Nobody");
    digitalWrite(6, LOW);
  }
}
