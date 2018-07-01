int value = 0;            //initializing variables
float volts = 0.0;
float temp = 0.0;
float tempF = 0.0;

void setup()
{
  pinMode(A0,INPUT);      //setting arduino pin3 as input
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
}
void loop()
{
  value = analogRead(A0);            //read from A0
  volts = (value/1024.0) * 5.0; // conversion to volts
  temp = volts * 100.0; //Convert temp to Celsius
  tempF = temp * 9/5 + 32; // Convert temp to Fahrenheit
  
  Serial.print("Value= ");
  Serial.println(tempF); 
  //Serial.println(temp);
  delay(1000);
}

