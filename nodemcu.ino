
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <WiFiUdp.h>

char ssid[] = "ashu1997";    //network SSID (name) 
char pass[] = "12345678";    //network password
int status = WL_IDLE_STATUS;
WiFiClient  client;
Servo myservo;

int frontleft=4;
int frontright=0;
int backleft=12;
int backright=2;
//int laser = 10;

unsigned long myChannelNumber= 424376;
const char * myReadAPIKey = "DR16UXNSMDDGNICG";

void setup() {
pinMode(frontleft,OUTPUT);
pinMode(frontright,OUTPUT);
pinMode(backleft,OUTPUT);
pinMode(backright,OUTPUT);


myservo.attach(14);
Serial.begin(115200);
WiFi.begin(ssid, pass);
ThingSpeak.begin(client);


while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
}

void loop() {
  
  int data1= ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey); //left
  int data2= ThingSpeak.readIntField(myChannelNumber, 2, myReadAPIKey); //right
  int data3= ThingSpeak.readIntField(myChannelNumber, 3, myReadAPIKey); // front
  int data4= ThingSpeak.readIntField(myChannelNumber, 4, myReadAPIKey); // stop
  int data5= ThingSpeak.readIntField(myChannelNumber, 5, myReadAPIKey); //back
  
  myservo.write(0);
  Serial.println("Laser at 0 position");

  if(data3 ==1)
  {
    Serial.println("BOT FORWARD..");
    digitalWrite(frontleft,HIGH);
    digitalWrite(frontright,HIGH);
    delay(2000);
    Serial.println("BOT FORWARD and stopped ");
    digitalWrite(frontleft,LOW);
    digitalWrite(frontright,LOW);    
  }
    if(data5==1)
  {
    Serial.println("BOT BACKWARD");
    digitalWrite(backright,HIGH);
    digitalWrite(backleft,HIGH); 
    delay(2000);
    digitalWrite(backright,LOW);
    digitalWrite(backleft,LOW); 
  }
  if(data4==1)
  {
    Serial.println("BOT STOP ");
  }
  if((data1==20))
      {
        myservo.write(58);
        Serial.println("laser left");
      }
  else if(data2==120)
      {
        myservo.write(86);
        Serial.println("laser right");
      }  
}




      
