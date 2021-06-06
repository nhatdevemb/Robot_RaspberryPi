#include <ESP8266WiFi.h>
  #include <PubSubClient.h>
  #include <DNSServer.h>                     // Thư viện DNS Server dùng để chuyển hướng tất cả try vấn đến trang web portal
  #include <ESP8266WebServer.h>              // Thư viện dùng để chạy web portal server
  #include <WiFiManager.h>
  
#include <Servo.h>


int val = 0; 
Servo myservo1;   
Servo myservo2;       
Servo myservo3;
Servo myservo4;  
 // #include <SimpleTimer.h>
  #define mqtt_server "broker.hivemq.com"
  const uint16_t mqtt_port = 1883; //Port của CloudMQTT TCP
int in1=14,in2=12,in3=13,in4=15; // D5-D8
  WiFiClient espClient;
  PubSubClient client(espClient);
  WiFiManager wifiManager;
  static String mess="";
  char list_id[20]="";
void setup() {
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
wifiManager.autoConnect("ROBOT");  // Thiết lập Access Point tên là
  client.setServer(mqtt_server, mqtt_port); // ten brocker,,cong mqttt
  client.setCallback(callback);

}

void callback(char* topic, byte* payload, unsigned int length) 
  {
  char buff[20]="";
  //Serial.print("Co tin nhan moi tu topic:");
  //Serial.println(topic);
  for (int i = 0; i < length; i++) 
  {
   char inchar=(char)payload[i];
   buff[i]=inchar;
  if(strcmp(buff,"tien") ==0)
  {
  tien();
  }
  else if(strcmp(buff,"lui") ==0)
  {
  lui();
  }
   else if(strcmp(buff,"trai") ==0)
  {
  trai();
  } 
   else if(strcmp(buff,"phai") ==0)
  {
  phai();
  }  
     else if(strcmp(buff,"dung") ==0)
  {
  dung();
  }  
      else if(strcmp(buff,"nang") ==0)
  {
  servo2();
  servo3();
  }
       else if(strcmp(buff,"ha") ==0)
  {
  servo1();
  }
         else if(strcmp(buff,"kep") ==0)
  {
  servo4();
  }
  }
  }
  // Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
  void reconnect() 
  {
  while (!client.connected()) // Chờ tới khi kết nối
  {
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("node_dt010132","offline",0,0,"MẤT KẾT NỐI TỚI THIẾT BỊ"))  //kết nối vào broker
    {
      Serial.println("Đã kết nối:");
      client.subscribe("node_dt010132_remote"); //đăng kí nhận dữ liệu từ topic ESP8266_read_data
    }
    else 
    {
      Serial.print("Lỗi:, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
  }

void loop() {
 client.loop();
   if (!client.connected())// Kiểm tra kết nối
  {
    reconnect();
  }
}
void tien()
{
digitalWrite(in3,1);
digitalWrite(in1,1);
digitalWrite(in2,0);
digitalWrite(in4,0);
}
void lui()
{
digitalWrite(in1,0);
digitalWrite(in2,1);
digitalWrite(in3,0);
digitalWrite(in4,1);
}
void dung1()
{
  digitalWrite(in1,0);
  digitalWrite(in2,0);
}
void dung2()
{
digitalWrite(in3,0);
digitalWrite(in4,0);
}
void dung()
{
dung1();
dung2();
}
void trai()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  dung2();
}
void phai()
{
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  dung1();  
}
