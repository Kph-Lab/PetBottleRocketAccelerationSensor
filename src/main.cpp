#include "Arduino.h"
#include "Wire.h"
#include "SparkFun_MMA8452Q.h"
#include "SparkFun_LPS25HB_Arduino_Library.h"
#include "BluetoothSerial.h"

MMA8452Q accel;
BluetoothSerial SerialBT;
LPS25HB pressureSensor;

void setup() {
  /* pinMode(32, INPUT); */
  /* pinMode(33, INPUT); */
  /* Serial.begin(115200); */
  SerialBT.begin("ESP32Test");
  Wire.begin();

  if (accel.begin() == false) {
    SerialBT.println("Not connected. Please Check connections and read the hookup guide.");
    while(1);
  }
  pressureSensor.begin();
  if (pressureSensor.isConnected() == false) {
    SerialBT.println("LPS25HB disconnected. Reset the board to try again.");
    while(1){}
  }
}

void loop() {
  SerialBT.print(millis());
  SerialBT.print("\t");
  SerialBT.print(pressureSensor.getPressure_raw());
  SerialBT.print("\t");
  SerialBT.print(pressureSensor.getTemperature_raw());
  SerialBT.print("\t");
  if (accel.available()) {
    SerialBT.print(accel.getCalculatedX(), 3);
    SerialBT.print("\t");
    SerialBT.print(accel.getCalculatedY(), 3);
    SerialBT.print("\t");
    SerialBT.print(accel.getCalculatedZ(), 3);
    SerialBT.println();
  }
}
