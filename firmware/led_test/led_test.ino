#define LED1 12
#define LED2 13
#define LED3 14
#define LED4 15

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(200);

  digitalWrite(LED2, HIGH);
  delay(200);

  digitalWrite(LED3, HIGH);
  delay(200);

  digitalWrite(LED4, HIGH);
  delay(500);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  delay(500);
}
