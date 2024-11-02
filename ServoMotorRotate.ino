#include <ESP32Servo.h>

Servo myServo;
int servoPin = 18;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(18);
  myServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:

}
