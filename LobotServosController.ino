#include "LobotServoController.h"
#include"SoftwareSerial.h"

SoftwareSerial LobotServoController::mySerial(10,11); //RX,TX

LobotServoController myse;
void setup() {
  LobotServoController::mySerial.begin(9600);
}

void loop() {
  static uint32_t Timer;

  int t=1000;
  LobotServo servos[18];
  servos[0].Position = 1800;
  servos[1].Position = 1000;
  servos[2].Position = 750;
  servos[3].Position = 1200;
  servos[4].Position = 800;
  servos[5].Position = 750;
  servos[6].Position = 1800;
  servos[7].Position = 1000;
  servos[8].Position = 750;
  servos[9].Position = 1800;
  servos[10].Position = 2200;
  servos[11].Position = 2250;
  servos[12].Position = 1200;
  servos[13].Position = 2000;
  servos[14].Position = 2250;
  servos[15].Position = 1800;
  servos[16].Position = 2200;
  servos[17].Position = 2250;
  for(int i=0;i<18;i++)
    servos[i].ID=i+1;
  myse.moveServos(servos, 18, 100); 
//  myse.moveServos(servos, 2, 1000); //控制两个舵机，移动时间1000ms,ID和位置有servos指定

  delay(1100);
  myse.moveServo(14, 2150, t);
  myse.moveServo(15, 1650, t);
  myse.moveServo(16, 1700, t);
  myse.moveServo(17, 2000, t);
  myse.moveServo(18, 1800, t);
  delay(1100);
}


