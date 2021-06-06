#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
 #include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
void setup()
{
Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servo1.attach(0); // NodeMCU D3 pin
  servo2.attach(02); // NodeMCU D4 pin gat1
  servo3.attach(14);// NodeMCU D5 pin
  servo4.attach(04);// NodeMCU D11 pin gat2
  
 }
  
void loop()
{ 
  Blynk.run(); 
}
BLYNK_WRITE(V1)
{
   servo1.write(param.asInt());
   delay (10);
}

BLYNK_WRITE(V2)
{
   servo2.write(param.asInt());
   delay (10);
   
}

BLYNK_WRITE(V3)
{
   servo3.write(param.asInt());
   delay (10);
 
}

BLYNK_WRITE(V4)
{
   servo4.write(param.asInt());
   delay (10);


}
