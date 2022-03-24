#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#define PINPOT A0

Servo serv;
unsigned char servPos;
unsigned char potVal;
unsigned char lastVal;
bool active = false;
Adafruit_MMA8451 mma = Adafruit_MMA8451();
unsigned char accel = 128;

void setup()
{
  Serial.begin(9600);
  serv.detach();
  pinMode(PINPOT, INPUT);
  servPos = 30;
  serv.write(servPos);
  mma.begin();
  mma.setRange(MMA8451_RANGE_2_G);
}

void loop()
{
  // read x axis on accelerometer and convert to a 0-255 number
  mma.read();
  // send values between 0 and 40 for accelerometer
  int val = min(max(mma.x, -4000), 4000) / 200 + 20;
  Serial.write(val);

  if (Serial.available())
  {
    servPos = (unsigned char) map(Serial.read(), 0, 255, 0, 180);
    if (servPos != 0 && !active)
    {
      serv.attach(3);
      active = true;
    }
    if (servPos == 0 && active)
    {
      serv.detach();
      active = false;
    }
    if (active)
      serv.write(servPos);
  }
  lastVal = potVal;
  potVal = map(analogRead(PINPOT), 0, 1024, 0, 255);
  potVal = (potVal-19)*2.61;
  if (lastVal != potVal)
  {
    Serial.write(potVal);
    lastVal = potVal;
  }
  delay(20);
}
