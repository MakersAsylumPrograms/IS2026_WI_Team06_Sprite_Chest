#include <ESP32Servo.h>

// Safe PWM pins on ESP32 (avoids boot-strapping pins and I2C pins 21/22)
const int SERVO_PINS[4] = {18, 5, 17, 16};

Servo servos[4];

void moveAll(int angle) {
  for (int i = 0; i < 4; i++) {
    servos[i].write(angle);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // Allocate timers for the PWM channels
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  for (int i = 0; i < 4; i++) {
    servos[i].setPeriodHertz(50);        // standard 50 Hz servo signal
    servos[i].attach(SERVO_PINS[i], 500, 2400); // min/max pulse width in µs
    servos[i].write(90);                 // start at center
    delay(300);                          // stagger startup to reduce inrush current
  }

  Serial.println("4 servos ready");
}

void loop() {
  // Test 1: all servos together, sweep 0 -> 180 -> 0
  Serial.println("Sweep up");
  for (int angle = 0; angle <= 180; angle += 2) {
    moveAll(angle);
    delay(15);
  }

  Serial.println("Sweep down");
  for (int angle = 180; angle >= 0; angle -= 2) {
    moveAll(angle);
    delay(15);
  }

  // Test 2: one at a time, so you can identify each servo
  Serial.println("One by one");
  for (int i = 0; i < 4; i++) {
    Serial.print("Servo ");
    Serial.println(i + 1);
    servos[i].write(150);
    delay(500);
    servos[i].write(30);
    delay(500);
    servos[i].write(90);
    delay(300);
  }

  delay(1000);
}