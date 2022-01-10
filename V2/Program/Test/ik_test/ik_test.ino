#include <ESP32Servo.h> 

#define S1 32 
#define S2 12 
 
Servo servoMotor1;
Servo servoMotor2;

double x_pos = 1;
double y_pos = 1;
double prev_x= 0;
double prev_y= 0;
 
const double a1 = 4.7;
const double a2 = 6.4;
const double a3 = 5.4;
const double a4 = 6.9;
 
double r1 = 0.0;
double phi_1 = 0.0;
double phi_2 = 0.0;
double phi_3 = 0.0;
double theta_1 = 0.0;
double theta_2 = 0.0;

String input;
 
void setup() {
  Serial.begin(115200);
 
  servoMotor1.attach(S1);
  servoMotor2.attach(S2);

  servoMotor1.write(0);
  servoMotor2.write(calc_servo_1_angle(0));
  
  delay(1000);
}
  
void loop() { 

   if (Serial.available() > 0) {
    
    input = Serial.read();
   }
    String x_val = getValue(input, ':', 0);
    String y_val = getValue(input, ':', 1);
    x_pos = x_val.toDouble();
    y_pos = y_val.toDouble();
    if(x_pos != prev_x ){
    prev_x=x_pos;
    prev_y=y_pos;
    Serial.print("xpos:");
    Serial.println(x_pos);
    Serial.print("ypos:");
    Serial.println(y_pos);
    
    r1 = sqrt((x_pos * x_pos) + (y_pos * y_pos));
    phi_1 = acos(((a4 * a4) - (r1 * r1) - (a2 * a2))/(-2.0 * r1 * a2));
    phi_2 = atan2(y_pos,x_pos);
    theta_1 = phi_2 - phi_1;
    phi_3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4))/(-2.0 * a2 * a4));
    theta_2 = PI - phi_3;
     
    theta_1 = theta_1 * RAD_TO_DEG; // Joint 1
    theta_2 = theta_2 * RAD_TO_DEG; // Joint 2
    Serial.print("theta1:");
    Serial.println(theta_1);
    Serial.print("theta2:");
    Serial.println(theta_2);
    Serial.print("calc_servo:");
    Serial.println(calc_servo_1_angle(theta_2));
    Serial.println("----------------------");
    servoMotor1.write(theta_1);
    servoMotor2.write(calc_servo_1_angle(theta_2));
    delay(500);
  }
}     
int calc_servo_1_angle (int input_angle) {
   
  int result;
 
  result = map(input_angle, -90, 90, 0, 180);
 
  return result;
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
