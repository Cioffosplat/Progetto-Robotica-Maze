int IR_pin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_pin, INPUT);
}

void loop() {
  int g = analogRead(IR_pin);
  Serial.println(g);
  delay(300);

}
