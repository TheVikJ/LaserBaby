#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

int laserPin = 13;
int laser2Pin = 12;
float measure1x, measure1y, measure1z;
float measure2x, measure2y, measure2z;
double diffx, diffy, diffz;

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  pinMode(laser2Pin, OUTPUT);
  digitalWrite(laserPin, LOW);
  digitalWrite(laser2Pin, LOW);
  if (!accel.begin())
  {
    Serial.println("No ADXL345 sensor detected.");
    while (1);
  }
}

void loop() {
  measure1();
  measure2();
  calculate();
  writeLaser();
}

void measure1() {
  sensors_event_t event1;
  accel.getEvent(&event1);
  delay(100);
  measure1x = event1.acceleration.x;
  measure1y = event1.acceleration.y;
  measure1z = event1.acceleration.z;
  Serial.println(String(measure1x) + " " + String(measure1y) + " " + String(measure1z));
  delay(100);
}

void measure2() {
  sensors_event_t event2;
  accel.getEvent(&event2);
  delay(100);
  measure2x = event2.acceleration.x;
  measure2y = event2.acceleration.y;
  measure2z = event2.acceleration.z;
  Serial.println(String(measure2x) + " " + String(measure2y) + " " + String(measure2z));
  delay(100);
}

void calculate() {
  diffx = measure1x - measure2x;
  diffy = measure1y - measure2y;
  diffz = measure1z - measure2z;
  Serial.println(String(diffx) + " " + String(diffy) + " " + String(diffz));
  delay(100);
}

void writeLaser() {
  if (int(diffx) > 1 || int(diffx) < -1 || int(diffy) > 1 || int(diffy)  < -1 || int(diffz) < -1 || int(diffz) > 1)
  {
    digitalWrite(laserPin, HIGH);
    digitalWrite(laser2Pin, HIGH);
    delay(4000);
  }
  digitalWrite(laserPin, LOW);
  digitalWrite(laser2Pin, LOW);
}