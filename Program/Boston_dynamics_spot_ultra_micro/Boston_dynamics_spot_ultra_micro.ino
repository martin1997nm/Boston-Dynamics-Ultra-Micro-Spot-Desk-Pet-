#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include <Servo.h>

char ssid[] = "Boston Dynamics Spot"; // your network SSID (name)
char pass[] = "Spot1234";             // your network password
bool WiFiAP = true;                   // Do yo want the ESP as AP?

String TOP;
String DAT;
String TOPIC = "/sit";
String TOPIC1 = "/stand";
String TOPIC2 = "/walk";
String TOPIC3 = "/left";
String TOPIC4 = "/right";
String TOPIC5 = "/rr"; //rear right
String TOPIC6 = "/rl"; //rear left
String TOPIC7 = "/fl"; //front left
String TOPIC8 = "/fr"; //front right
String TOPIC9 = "/lay";
String TOPIC10 = "/pit";
String TOPIC11 = "/getup";

const unsigned char Passive_buzzer = 13;
Servo rear_right;
Servo rear_left;
Servo front_left;
Servo front_right;
int rear_right_current_position=90;
int rear_left_current_position=90;
int front_right_current_position=90;
int front_left_current_position=90;

class myMQTTBroker : public uMQTTBroker
{
public:
  virtual bool onConnect(IPAddress addr, uint16_t client_count)
  {
    Serial.println(addr.toString() + " connected");
    return true;
  }

  virtual bool onAuth(String username, String password)
  {
    Serial.println("Username/Password: " + username + "/" + password);
    return true;
  }

  virtual void onData(String topic, const char *data, uint32_t length)
  {
    char data_str[length + 1];
    os_memcpy(data_str, data, length);
    data_str[length] = '\0';
    Serial.println("received topic '" + topic + "' with data '" + (String)data_str + "'");
    TOP = topic;
    DAT = (String)data_str;
  }
};

myMQTTBroker myBroker;

void startWiFiAP()
{
  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, pass);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}

void startWiFiClient()
{
  WiFi.hostname("Bite Indicator");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void setup()
{
  delay(2000);
  pinMode(Passive_buzzer, OUTPUT);
  digitalWrite(Passive_buzzer, HIGH);

  Serial.begin(115200);
  rear_right.attach(0);
  rear_left.attach(2);
  front_left.attach(4);
  front_right.attach(5);

  // Start WiFi
  if (WiFiAP)
    startWiFiAP();
  else
    startWiFiClient();

  // Start the broker
  Serial.println("Starting MQTT broker");
  Serial.println(pass);
  myBroker.init();
  myBroker.subscribe("#");

  stand();

  tone(13, 329.63, 300);
  
  delay(100);
  tone(13, 311.13, 300);
  
  delay(100);
  tone(13, 329.63, 300);
  
  delay(100);
  tone(13, 311.13, 300);
  
  delay(100);
  tone(13, 329.63, 300);
  
  delay(100);
  tone(13, 246.94, 300);
  
  delay(100);
  tone(13, 293.66, 300);
  
  delay(100);
  tone(13, 261.63, 300);
  
  delay(150);
  tone(13, 220, 900);

  digitalWrite(Passive_buzzer, HIGH);
}

void loop()
{ //TODO: replace the disgusting amount of ifs here...
  if (TOP == TOPIC){
    if (DAT == "0"){
      DAT = "1";
      sit();
    }
  }

  if (TOP == TOPIC1)
  {
    if (DAT == "0")
    {
      DAT = "1";
      stand();
    }
  }

  if (TOP == TOPIC2)
  {
    if (DAT == "0")
    {
      walk();
    }
  }

  if (TOP == TOPIC3)
  {
    if (DAT == "0")
    {
      left();
    }
  }

  if (TOP == TOPIC4)
  {
    if (DAT == "0")
    {
      right();
    }
  }

  if (TOP == TOPIC5)
  {
    setServo(rear_right,rear_right_current_position,DAT.toInt(),5);
  }

  if (TOP == TOPIC6)
  {
    rear_left.write(DAT.toInt());
  }

  if (TOP == TOPIC7)
  {
    front_left.write(DAT.toInt());
  }

  if (TOP == TOPIC8)
  {
    front_right.write(DAT.toInt());
  }

  if (TOP == TOPIC9)
  {
    if (DAT == "0")
    {
      DAT = "1";
      lay();
    }
  }

  if (TOP == TOPIC10)
  {
    if (DAT == "0")
    {
      DAT = "1";
      pit();
    }
  }

  if (TOP == TOPIC11)
  {
    if (DAT == "0")
    {
      DAT = "1";
      getup();
    }
  }

  delay(300);
}

void getup()
{
  tone(Passive_buzzer, 659);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(180);
  rear_right.write(0);

  delay(200);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(90);
  rear_right.write(90);

  digitalWrite(Passive_buzzer, HIGH);
}

void stand()
{
  tone(Passive_buzzer, 659);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(90);
  rear_right.write(90);

  delay(400);

  digitalWrite(Passive_buzzer, HIGH);
}

void sit()
{
  tone(Passive_buzzer, 587);

  front_left.write(30);
  front_right.write(150);
  rear_left.write(30);
  rear_right.write(150);

  delay(400);

  digitalWrite(Passive_buzzer, HIGH);
}

void lay()
{
  tone(Passive_buzzer, 587);

  front_left.write(0);
  front_right.write(180);
  rear_left.write(180);
  rear_right.write(0);

  delay(400);

  digitalWrite(Passive_buzzer, HIGH);
}

void pit()
{
  tone(Passive_buzzer, 587);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(180);
  rear_right.write(0);

  delay(200);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(150);
  rear_right.write(0);

  delay(200);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(180);
  rear_right.write(30);

  delay(200);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(150);
  rear_right.write(0);

  delay(200);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(180);
  rear_right.write(30);

  digitalWrite(Passive_buzzer, HIGH);
}

void walk()
{
  tone(Passive_buzzer, 523); //DO note 523 Hz

  delay(200);

  digitalWrite(Passive_buzzer, HIGH);

  front_left.write(90);
  front_right.write(90);
  rear_left.write(90);
  rear_right.write(90);

  delay(200);

  front_left.write(50);

  delay(200);

  rear_right.write(110);

  delay(200);

  front_right.write(130);

  delay(200);

  rear_left.write(60);
}

void right()
{
  delay(150);
  //fl rl 130
  //fr rr 60
  //stand
  
  front_right.write(130);
  delay(150);

  rear_right.write(120);
  delay(150);

  front_left.write(60);
  delay(150);

  rear_left.write(70);
  delay(150);

  stand();
}

void left()
{
  delay(100);
  //fl 50, delay 100, rl 50, delay 100
  //fr 120, delay 100, rr 120, delay 100
  //stand

  front_left.write(50);
  delay(150);

  rear_left.write(60);
  delay(150);

  front_right.write(120);
  delay(150);

  rear_right.write(110);
  delay(150);

  stand();
}

void setServo(Servo servoId, int servoPosition, int target, int speed)
{
  if (servoPosition > target)
  {
    while(servoPosition > target)
    {
      servoPosition -= speed;
      servoId.write(servoPosition);
      delay(35);
      Serial.print(servoPosition);
    }
    //! somehow stop calling this.
    //? change topic?
    //? set speed to 0?
    //? break/continue?
  }

  if (servoPosition < target)
  {
    while(servoPosition < target){
      servoPosition += speed;
      servoId.write(servoPosition);
      delay(35);
      Serial.print(servoPosition);
    }
    //! somehow stop calling this.
    //? change topic?
    //? set speed to 0?
    //? break/continue?
  }

}

/**if(servo == "rear_right"){rear_right_current_position = servoPosition;}
if(servoId = rear_left){rear_left_current_position = servoPosition;}
if(servoId = front_right){front_right_current_position = servoPosition;}
if(servoId = front_left){front_left_current_position = servoPosition;}
**/

void standby(){
  rear_left.write(rear_left_current_position);
  rear_right.write(rear_left_current_position);

  front_left.write(front_left_current_position);
  front_right.write(front_right_current_position);
}