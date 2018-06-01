void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D6, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}


