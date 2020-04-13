#include<Servo.h>
Servo servoMotor;
#define POS_0 90.
#define FIRST_PIN 2

void setup() {
  servoMotor.attach(FIRST_PIN);
  servoMotor.write(POS_0);
}

void loop() {
  

}
