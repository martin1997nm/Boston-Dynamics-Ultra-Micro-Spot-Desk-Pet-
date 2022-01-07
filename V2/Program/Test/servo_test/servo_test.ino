#include "MPU9250.h"
#include <ESP32Servo.h>

//MPU
MPU9250 IMU(Wire,0x68);
int status;

//Buzzer
const int PIN =4;
hw_timer_t* timer = NULL;
bool value = true;
int frequency =50; // 20 to 20000

//Servo
#define S1 26 
#define S2 18 
#define S3 19 
#define S4 23 
#define S5 27
#define S6 25
#define S7 32 
#define S8 12 

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
Servo servoMotor5;
Servo servoMotor6;
Servo servoMotor7;
Servo servoMotor8;

void IRAM_ATTR onTimer() {
  value = !value;
  digitalWrite(PIN, value); 
}

void setup() {
  Serial.begin(115200);
  
  //MPU
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  
  //Buzzer
  pinMode(PIN, OUTPUT);// sets the digital pin as output
  digitalWrite(PIN,HIGH);
  setupTimer();
  
  //Servo
  servoMotor1.attach(S1);
  servoMotor2.attach(S2);
  servoMotor3.attach(S3);
  servoMotor4.attach(S4);
  servoMotor5.attach(S5);
  servoMotor6.attach(S6);
  servoMotor7.attach(S7);
  servoMotor8.attach(S8);  
}
void setupTimer() {
    // Use 1st timer of 4  - 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up 
    timer = timerBegin(0, 80, true);//div 80
    timerAttachInterrupt(timer, &onTimer, true);
}

void setFrequency(long frequencyHz){
    timerAlarmDisable(timer);
    timerAlarmWrite(timer, 1000000l / frequencyHz, true);
    timerAlarmEnable(timer);
}

void tone(long frequencyHz, long durationMs){
    setFrequency(frequencyHz);
    delay(durationMs);
}

void loop() {
  imuGetData();
  servoControll();
  delay(300);
  tone(frequency,1000);
  delay(1000);
  digitalWrite(PIN,HIGH);
}

void imuGetData(){
IMU.readSensor();
  // display the data
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
  delay(100);
}

void servoControll(){
   for (int pos = 0; pos <= 180; pos += 10) {
    servoMotor1.write(pos);
    servoMotor2.write(pos);
    servoMotor3.write(pos);
    servoMotor4.write(pos);
    servoMotor5.write(pos);
    servoMotor6.write(pos);
    servoMotor7.write(pos);
    servoMotor8.write(pos);
    delay(15); 
  }

  for (int pos = 180; pos >= 0; pos -= 10) {
    servoMotor1.write(pos);
    servoMotor2.write(pos);
    servoMotor3.write(pos);
    servoMotor4.write(pos);
    servoMotor5.write(pos);
    servoMotor6.write(pos);
    servoMotor7.write(pos);
    servoMotor8.write(pos);
    delay(15); 
  }
}
