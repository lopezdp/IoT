#include <SoftwareSerial.h>

float field;

String apiKey = "";

SoftwareSerial


void setup() {
  // put your setup code here, to run once:
    serial1.begin(115200);
  serial1.println("AT");
  delay(2000);

  serial1.println("AT+RST");
  delay(2000);

  serial.println("AT

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.


}
