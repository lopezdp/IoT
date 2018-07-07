/*
 * 
 * Interfacing LM35:
 * Left(1) Pin ---> VCC (5V)
 * Right Pin (3) Pin ---> GND
 * Center (2) Pin ---> A0
 * ESP8266 ---> 01
 * Rx ---> TX (11)
 * Tx --> RX (10)
 * VCC ---> 3.3V
 * GND ---> 0V
 * CH_PD ---> 3.3V
 * 
 * 
 */


#include <SoftwareSerial.h>
#define SENSORPIN A0 //vsriable storing D4

// RX --> TX
// TX --> RX

float field;
float value = 0.0;
float volts = 0.0;
float tempF = 0.0;

String apiKey = "UIHGBEAF9R38CZL3";

SoftwareSerial serial1(10,11); 
// RX,TX connect to RX of esp8266

void setup() {  
  pinMode(A0,INPUT);      //setting arduino A0 as input  
            
  // initialize the sensor at 7th pin as an input.
  // enable debug serial
  
  Serial.begin(115200);       //Baud rate for serial communication
  
  // enable software serial
  serial1.begin(115200);    // Baud rate for ESP8266
  
  serial1.println("AT"); 
  delay(1000);
  
  serial1.println("AT+RST");    //RESET
  delay(1000);
  
  serial1.println("AT+CWMODE=1");   //Station
  delay(1000);
  
  serial1.println("AT+CWJAP=\"d63869\",\"261624293\"");
  delay(10000);
}

void loop() {
  int val = 0;
  for(int i = 0; i < 10; i++) {
      val += analogRead(A0);   
      delay(500);
  }

  // convert to temp:
  // temp value is in 0-1023 range
  // LM35 outputs 10mV/degree C. ie, 1 Volt => 100 degrees C
  // So Temp = (avg_val/1023)*5 Volts * 100 degrees/Volt
  float temp = val*50.0f/1023.0f;

  // convert to string
  char buf[16];
  String strTemp = dtostrf(temp, 4, 1, buf);
  Serial.print("Temperature:");
  Serial.println(strTemp); // Prints Temperature
  // TCP connection
  // AT+CIPSTART = <type>,<addr>,<port>
  String cmd = "AT+CIPSTART=\"TCP\",\""; 
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  serial1.println(cmd);
  Serial.println(cmd);
  if(serial1.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
  // prepare GET string
  //GET https://api.thingspeak.com/update?api_key=TMWR47CL9G5PTZHM&field1=0&field2=0
  //GET /update?api_key=TMWR47CL9G5PTZHM&field1=31&field2=73
  String getStr = "GET /update?api_key=";
  
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strTemp);
  getStr += "\r\n\r\n";
  // send data length
  cmd = "AT+CIPSEND=";        // Sending data
  cmd += String(getStr.length());
  serial1.println(cmd);
  Serial.println(cmd);

  if(serial1.find(">")){
    serial1.print(getStr);
    Serial.print(getStr);
  }
  else{
    serial1.println("AT+CIPCLOSE");  // Closing TCP Connection
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  // thingspeak needs 5-15 sec delay between updates
  delay(15000);  
}

