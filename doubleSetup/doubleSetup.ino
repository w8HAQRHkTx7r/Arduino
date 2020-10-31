int setupCount = 0;
int loopCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("*****\nStart Program now ");
  Serial.println(++setupCount);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("In the loop ");
  Serial.println(++loopCount);
  delay(5000);
}
