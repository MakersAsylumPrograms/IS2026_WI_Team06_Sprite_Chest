#include <ESP32Servo.h>

Servo myservo;

void setup() {    
  myServo-setPeriodHertz (50); 
  myServo.attach(18, 1000, 2000);

  myServo.write(90);
  delay (1000);
}

void loop() {
  myServo.write(0);
  delay (1000);

  myServo.write(90); 
  delay (1000);

  myServo.write(180); 
  delay (1000);

  myServo.write(90); 
  delay (1000);

}