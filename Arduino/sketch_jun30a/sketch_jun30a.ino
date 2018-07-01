#include <SoftwareSerial.h>
SoftwareSerial softSerial(10,11); // RX, TX

int led1 = 3;
int led2 = 4;
int led3 = 5;

unsigned char blue_data;   //stores the value from a bluetooth mediumSoftwareSerial mySerial(10, 11); // RX, TX
void setup()
{
  Serial.begin(9600);           // Set up serial communications with 9600 baud rate
  softSerial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  // Intialize all motor PIN mode as Output
  digitalWrite(led1,LOW);    // Low as by default value
  digitalWrite(led2,LOW); 
  digitalWrite(led3,LOW); 
}
void loop()
{
   if (softSerial.available())        // Checks for Serial communication availability
  {
    blue_data = softSerial.read();        // Get incoming byte from bluetooth module 
          if(blue_data=='F')          // If Byte data is 'F' write Pins High Low to move Forward
           {
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,HIGH);
            Serial.println("Leds are ON");
           }
          if(blue_data=='S')          // If Byte data is 'S' write Pins High Low to move Backward
           {
            digitalWrite(led1,HIGH);
            delay(1000);
            digitalWrite(led1,LOW);
            delay(1000);
            Serial.println("Leds are OFF");
           }

          
  }
}
