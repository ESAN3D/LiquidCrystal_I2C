/*
 * Wire - I2C Scanner
 * Arduino UNO I2C bus uses pins:
 * 19 or A5 = SCL
 * 18 or A4 = SDA
 * The WeMos D1 R1 I2C bus uses pins:
 * D3 = SCL
 * D4 = SDA
 * The WeMos D1 Mini I2C bus uses pins:
 * D1 = SCL
 * D2 = SDA
 */

#include <Wire.h>

const int sclPin = D3;
const int sdaPin = D4;

void setup()
{
  Wire.begin(D4, D3);

  Serial.begin(9600);
  Serial.println("I2C Scanner");
}

void loop()
{
  int val = analogRead(A0);
  Serial.println(val);
  
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("Done.\n");
  }

  delay(2000);
}
