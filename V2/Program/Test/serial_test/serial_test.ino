#include <WiFi.h>
#include <ESP32Servo.h>

//FL
#define S1 32 
#define S2 12 
//FR
#define S3 19 
#define S4 23 
//LL
#define S5 27
#define S6 25
//LR
#define S7 26 
#define S8 18 

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
Servo servoMotor5;
Servo servoMotor6;
Servo servoMotor7;
Servo servoMotor8;

unsigned long startMillis;
unsigned long currentmillis;
unsigned long measuremillis;
unsigned long savemillis;
unsigned long counter;
  
int CropValue;
int duration = 1;
int tombmeret = 110;
int i=0;
int MeasurementDelay = 10;
int status;

char*         TCPssid         ="SoptDevNetwork";
char*         TCPpassword     ="Spot12345678";

String        TCPClienID      ="Spot1";
String        MSG,TOP,DAT;
String        TOPIC0          = "sto";//STOP
String        TOPIC1          = "se1";//SERVO 1-8
String        TOPIC2          = "se2";  
String        TOPIC3          = "se3";  
String        TOPIC4          = "se4";  
String        TOPIC5          = "se5";  
String        TOPIC6          = "se6";  
String        TOPIC7          = "se7";  
String        TOPIC8          = "se8";
String        TOPIC9          = "for";//forward
String        TOPIC10         = "bac";//backward
String        TOPIC11         = "lef";//left
String        TOPIC12         = "rig";//right
String        TOPIC13         = "lay";//lay
String        TOPIC14         = "sta";//stand
String        TOPIC15         = "sit";//sit
String        TOPIC16         = "cal";//imuCalib
String        TOPIC17         = "va1";//variable 1-6
String        TOPIC18         = "va2";
String        TOPIC19         = "va3";
String        TOPIC20         = "va4";
String        TOPIC21         = "va5";
String        TOPIC22         = "va6";





  
  
IPAddress     TCPServer(192,168,43,1);
WiFiClient    TCPClient ;


void setup() {
  
  Serial.begin(115200);
  //Servo
  servoMotor1.attach(S1);
  servoMotor2.attach(S2);
  servoMotor3.attach(S3);
  servoMotor4.attach(S4);
  servoMotor5.attach(S5);
  servoMotor6.attach(S6);
  servoMotor7.attach(S7);
  servoMotor8.attach(S8); 
 
  delay(10);
  //Wifi
  WiFi.mode(WIFI_STA);            
    WiFi.begin(TCPssid,TCPpassword);         
    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");
    
    CheckConnectivity();           
    
    Serial.println("!-- Client Device Connected --!");
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.print  ("Server IP Address : ");
    Serial.println(TCPServer);
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
    
    TCPRequest();
    startMillis = millis();
    delay(500);
}

void loop() {
     MSG = TCPClient.readStringUntil('\n');
     //MSG=MSG.trim();
     Serial.println(MSG);
     TCPClient.flush();  
     TOP = MSG.substring(1,4);
     DAT = MSG.substring(4,(MSG.length()-1)); 
     Serial.println("MESSAGE :"+MSG);
     Serial.println("TOPIC :"+TOP);
     Serial.println("DATA :"+DAT);

 if(TOP == TOPIC1)
     {

       TCPClient.println("<S1"+DAT+">");
       servoMotor1.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S1:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC2)
     {
       TCPClient.println("<S2"+DAT+">");
       servoMotor2.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S2:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC3)
     {
       TCPClient.println("<S3"+DAT+">");
       servoMotor3.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S3:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC4)
     {
       TCPClient.println("<S4"+DAT+">");
       servoMotor4.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S4:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC5)
     {
       TCPClient.println("<S5"+DAT+">");
       servoMotor5.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S5:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC6)
     {
       TCPClient.println("<S6"+DAT+">");
       servoMotor6.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S6:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC7)
     {
       TCPClient.println("<S7"+DAT+">");
       servoMotor7.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S7:"+DAT);
       TOP=TOPIC0;
     }
 if(TOP == TOPIC8)
     {
       TCPClient.println("<S8"+DAT+">");
       servoMotor8.write(DAT.toInt());
       TCPClient.flush();
       Serial.println("S8:"+DAT);
       TOP=TOPIC0;
     }
  
     
}

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void CheckConnectivity(){
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 6; i++)
      {
        Serial.print(".");
      }
      
    }
  }
void TCPRequest(){
    TCPClient.stop();
    if(TCPClient.connect(TCPServer, 1883))
    {
      
      Serial.println    ("<"+TCPClienID+"-CONNECTED>"); 
      TCPClient.println ("<""CONNECTED>");    
      TCPClient.flush(); 
      TCPClient.println ("<"+TCPClienID+"-CONNECTED>");
      TCPClient.flush(); 
      
      
    }
  }
