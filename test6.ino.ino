#include <SoftwareSerial.h>
#define GET_LOW_BYTE(A) (uint8_t)((A))
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
SoftwareSerial mySerial(10, 11);
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time)
{
byte buf[10];
if (servoID > 31 || !(Time > 0)) { 
return;
}
buf[0] = 0x55;
buf[1] = 0x55;
buf[2] = 8;
buf[3] = 0x03;
buf[4] = 1;
buf[5] = GET_LOW_BYTE(Time);
buf[6] = GET_HIGH_BYTE(Time);
buf[7] = servoID;
buf[8] = GET_LOW_BYTE(Position);
buf[9] = GET_HIGH_BYTE(Position);
mySerial.write(buf, 10);
}
void setup() {
  // put your setup code here, to run once:
mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=1;i<=18;i++)
{
  moveServo(i, 500, 1000);
}
//moveServo(5, 500, 1000);
delay(1000);
for(int i=1;i<=18;i++)
{
  moveServo(i, 2500, 1000);
}
//moveServo(5, 2500, 1000);
delay(1000);
}
