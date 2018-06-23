int led1 = 2;
int irSensor = 10;

void triggerWeld(int ledPin) {
  digitalWrite(ledPin,HIGH);
  delay(2500);

  digitalWrite(ledPin, LOW);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(irSensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(irSensor) == HIGH) {
    triggerWeld(led1);
  }
  
  if (digitalRead(irSensor) == LOW) {
    
  }



  

}
