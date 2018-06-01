void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A4);
  int converted = map(val, 0, 1023, 0, 255);
  int converted_inverse = map(val, 0, 1023, 255, 0);
  analogWrite(5, converted);
  analogWrite(6, converted_inverse);
  Serial.println(val);
}
