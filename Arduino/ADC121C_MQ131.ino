// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C_MQ131
// This code is designed to work with the ADC121C_I2CGAS_MQ131 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Gas?sku=ADC121C_I2CGAS_MQ131#tabs-0-product_tabset-2

#include <Wire.h>

// ADC121C_MQ131 I2C address is 0x50(80)
#define Addr 0x50

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12-bits
  int raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  float ppm = (1.99 * raw_adc) / 4095.0 + 0.01;

  // Output data to serial monitor
  Serial.print("Ozone Concentration : ");
  Serial.print(ppm);
  Serial.println(" ppm");
  delay(500);
}
