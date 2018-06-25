#include <SoftwareSerial.h>
// stores the value from a BT Serial connection
unsigned char blue_data;
int ledPin1 = 10;
const byte rxPin = 19;
const byte txPin = 18;

// RX/TX
SoftwareSerial serialDevice(rxPin,txPin);

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);     // Intialize all motor PIN mode as Output
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  serialDevice.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(serialDevice.available() > 0) { //Checks for Serial connection availability
    blue_data = serialDevice.read(); // Get incoming Byte from BT module

    serialDevice.println(blue_data);
    
    if(blue_data == 'F') { // If Byte data is 'F' write pins HIGH LOW to move forward
      digitalWrite(ledPin1,HIGH);
      delay(2500);
    
      digitalWrite(ledPin1, LOW);
      delay(100);

      
    }
    if(blue_data == 'S') { // If Byte data is 'S' write pins LOW to move backward
      digitalWrite(ledPin1,HIGH);
      delay(2500);
    
      digitalWrite(ledPin1, LOW);
      delay(2000);
    }
    if(blue_data == 'L') { // If Byte data is 'L' write pins LOW to Stop
      digitalWrite(ledPin1,HIGH);
      delay(2500);    
    }
    
    
  }

}
