#include<SoftwareSerial.h> // Software serial
SoftwareSerial client(10,11); //RX -->TX, TX -->RX
String webpage=""; //Variable to store a small webpage 
int i=0,k=0;
String readString;
int x=0;
boolean No_IP=false;
String IP="";
char temp1='0';
float temperature;
float value=0.0;
float volts=0.0;         
float tempF=0.0;
char temperatureString[6];
void wifi_init()
{
      connect_wifi("AT",1000);
      connect_wifi("AT+CWMODE=1",1000);
      connect_wifi("AT+CWQAP",1000);  // AT+CWQAP = QUITING AN ACCESS POINT
      connect_wifi("AT+RST",5000);
      check4IP(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        connect_wifi("AT+CWJAP=\"d63869\",\"261624293\"",10000);         //provide your WiFi username and password here
      }
      else
        {
          Serial.println("Wifi Connected"); 
        }
      get_ip();
      connect_wifi("AT+CIPMUX=1",100);  //For multiple client hold
      connect_wifi("AT+CIPSERVER=1,80",100);    //Server PORT
}

void check4IP(int t1)
{
  int t2=millis();
  while(t2+t1>millis())
  {
    while(client.available()>0)
    {
      if(client.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}

void get_ip()
{
  IP="";
  char ch=0;
  while(1)
  {
    client.println("AT+CIFSR");  // REsponsible command for generating an local IP address
    delay(10000);
    while(client.available()>0)
    {
      if(client.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while(client.available()>0)
        {
          ch=client.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
}

void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    client.println(cmd); 
    while(client.available())
    {
      if(client.find("OK"))
      i=8;
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8)
  Serial.println("OK");
  else
  Serial.println("Error");
}

void sendwebdata(String message)
{
    int ii=0;
     while(1)
     {
      unsigned int l=message.length();
      Serial.print("AT+CIPSEND=0,");
      client.print("AT+CIPSEND=0,");
      Serial.println(l+2);
      client.println(l+2);
      delay(100);
      Serial.println(message);
      client.println(message);
      while(client.available())
      {
        //Serial.print(Serial.read());
        if(client.find("OK"))
        {
          ii=11;
          break;
        }
      }
      if(ii==11)
      break;
      delay(100);
     }
}

void setup() 
{
   pinMode(A0,INPUT);
   Serial.begin(115200);
   client.begin(115200);
   wifi_init();
   
   Serial.println("System Ready..");
}
void loop() 
{
  int val = 0;
  for(int i = 0; i < 10; i++) {
      val += analogRead(A0);   
      delay(500);
  }

  float temperature = val*50.0f/1023.0f;
  k=0;
  while(k<1000)
  {
    k++;
   while(client.available())
   {
    if(client.find("0,CONNECT"))
    {
      Serial.println("Start Printing");
      datasend();
      Serial.println("Done Printing");
      delay(1000);
    }
  }
  delay(10);
 }
}

void datasend()
{   dtostrf(temperature, 2, 2, temperatureString);
    webpage = "<h1> Temperature Webserver </h1><body bgcolor=f0f0f0>";
    sendwebdata(webpage);
    webpage = "<h2> Temperature:";
    webpage+=temperatureString;
    webpage+="&deg C </h2>";
    sendwebdata(webpage);
    client.println("AT+CIPCLOSE=0"); 
}
