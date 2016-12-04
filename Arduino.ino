#include <Servo.h>
#include <Process.h>
#include <SoftwareSerial.h>
#include "DFRobotVeyronBrushed.h"

DFRobotVeyronBrushed VeyronBrushed;
SoftwareSerial vSerial(10, 11); // RX, TX
Process mediaSever;
Servo servoPan, servoTilt;

void setup() {
  Serial.begin(57600);
  Serial1.begin(250000);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();

  Process wifiCheck;  // initialize a new process
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }
  Serial.println();

  vSerial.begin(57600);
  VeyronBrushed.begin(vSerial);

  mediaSever.begin("/root/project/RPRobot/test");
  mediaSever.runAsynchronously();
  while (mediaSever.available() > 0) {
    char c = mediaSever.read();
    Serial.print(c);
  }
  Serial.println();
  
  servoPan.attach(9);
  servoTilt.attach(6);
  servoPan.write(90);
  servoTilt.write(90);
  digitalWrite(13, HIGH);
}

byte pan, tilt;

void loop() {
  int speedMin = 20;               //Store the speed of the motor in RPM (Revolutions Per Minute)

  if (Serial1.available()) {
    byte b = Serial1.read();
    Serial.println(b, DEC);
    switch(b) {
    case 0: //Stop
    case 1:
    case 5:
      setWheelState(0, 0);
      break;
    case 2:
      setWheelState(-speedMin, 0);
      break;
    case 3: //Backward
      setWheelState(-speedMin, -speedMin);
      break;
    case 4:
      setWheelState(0, -speedMin);
      break;
    case 6: //Turn left
      setWheelState(0, speedMin);
      break;
    case 7: //Forward
      setWheelState(speedMin, speedMin);
      break;
    case 8: //Turn right
      setWheelState(speedMin, 0);
      break;

    case 9: //Rotate clockwise
      setWheelState(speedMin, -speedMin);
      break;
    case 10:
      setWheelState(-2 * speedMin, -speedMin);
      break;
    case 11: //Backward
      setWheelState(-2 * speedMin, -2 * speedMin);
      break;
    case 12:
      setWheelState(-speedMin, -2 * speedMin);
      break;
    case 13: //Rotate anticlockwise
      setWheelState(-speedMin, speedMin);
      break;
    case 14: //Turn left
      setWheelState(speedMin, 2 * speedMin);
      break;
    case 15: //Forward
      setWheelState(2 * speedMin, 2 * speedMin);
      break;
    case 16: //Turn Right
      setWheelState(2 * speedMin, speedMin);
      break;

    case 32: //Camera Holder
      pan = Serial1.read();
      tilt = Serial1.read();
	  if (pan >= 166)
        pan -= 166;
      else if (pan <= 90)
        pan += 90;
      else
        return;
	  if (tilt >= 166)
        tilt -= 166;
      else if (tilt <= 90)
        tilt += 90;
      else
        return;
      Serial.print(pan, DEC);
      Serial.print(", ");
      Serial.println(tilt, DEC);
      servoPan.write(pan);
      servoTilt.write(tilt);
      break;

    case 36: //Restart
      mediaSever.close();
      digitalWrite(13, LOW);
      delay(20000);
      //mediaSever.begin("/root/projecct/RPRobot/test");
      mediaSever.runAsynchronously();
      digitalWrite(13, HIGH);
      break;
    }
  }
}

int id = 1;                   //The ID of the Veyron
int motorL = 1, motorR = 2;   //The motor number: 1 for M1 and 2 for M2

void setWheelState(int speedL, int speedR) {
  VeyronBrushed.setSpeed(id, motorL, speedL);
  delay(20);
  VeyronBrushed.setSpeed(id, motorR, speedR);
}
