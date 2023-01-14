#include <QTRSensors.h>
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 4;
const int m22Pin = 5;
const int m1Enable = 11;
const int m2Enable = 10;
int m1Speed = 0;
int m2Speed = 0;
// increase kp’s value and see what happens
float kp = 6;
float ki = 0;
float kd = 0.5;
int p = 1;
int i = 0;
int d = 0;
int error = 0;
int lastError = 0;
const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 180;
QTRSensors qtr;
const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = { 0, 0, 0, 0, 0, 0 };
void setup() {
  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5 },
                    sensorCount);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // turn on Arduino's LED to indicate we
  //are in calibration mode
  // calibrate the sensor. For maximum grade the line follower should do
  //the movement itself, without human interaction.
  // for (uint16_t i = 0; i < 400; i++) {
  //   qtr.calibrate();
  //   // do motor movement here, with millis() as to not ruin calibration)
  // }

  int currentState = 0;
  int passes = 0;
  while(passes < 5){

    qtr.calibrate();
    qtr.read(sensorValues);

    if(currentState == 0) 
    {
        if(sensorValues[0] < 700){
          setMotorSpeed(220, -220);
        }
        else {
          currentState = 1;
        }
    }

    if(currentState == 1)
    {
      if(sensorValues[5] < 700){
          setMotorSpeed(-220, 220);
        }
        else {
          currentState = 0;
          passes ++;
        }
    }
  }
//kp = 8
//ki =0.01
//kd = 2
// viteza 200

  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
}
void loop() {

  // inefficient code, written in loop. You must create separate functions
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -50, 50);
  p = error;  
  i = i + error;
  d = error - lastError;
  lastError = error;
  int motorSpeed =  pidControl(kp, ki, kd); // = error in this case
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;
  if (error < 0) {
    m1Speed += motorSpeed;
  } else if (error > 0) {
    m2Speed -= motorSpeed;
  }
  
  m1Speed = constrain(m1Speed, 0, maxSpeed);
  m2Speed = constrain(m2Speed, 0, maxSpeed);
  setMotorSpeed(m1Speed, m2Speed);
  // DEBUGGING
  // Serial.print("Error: ");
  // Serial.println(error);
  // Serial.print("M1 speed: ");
  // Serial.println(m1Speed);
  //
  // Serial.print("M2 speed: ");

  // Serial.println(m2Speed);
  //
  // delay(250);
}
// calculate PID value based on error, kp, kd, ki, p, i and d.
int pidControl(float kp, float ki, float kd) {
  return kp * p + ki * i + kd * d;
}
  void setMotorSpeed(int motor1Speed, int motor2Speed) {
    // remove comment if any of the motors are going in reverse
    // motor1Speed = -motor1Speed;
    // motor2Speed = -motor2Speed;
    if (motor1Speed == 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    } else {
      if (motor1Speed > 0) {
        digitalWrite(m11Pin, HIGH);
        digitalWrite(m12Pin, LOW);
        analogWrite(m1Enable, motor1Speed);
      }
      if (motor1Speed < 0) {
        digitalWrite(m11Pin, LOW);
        digitalWrite(m12Pin, HIGH);
        analogWrite(m1Enable, -motor1Speed);
      }
    }
    if (motor2Speed == 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    } else {
      if (motor2Speed > 0) {
        digitalWrite(m21Pin, HIGH);
        digitalWrite(m22Pin, LOW);
        analogWrite(m2Enable, motor2Speed);
      }
      if (motor2Speed < 0) {
        digitalWrite(m21Pin, LOW);
        digitalWrite(m22Pin, HIGH);
        analogWrite(m2Enable, -motor2Speed);
      }
    }
  }