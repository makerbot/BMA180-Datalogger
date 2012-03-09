#include <Wire.h>

#define ADDRESS 0x40

//pick your bandwidth / filter mode.
//#define BMA180_BANDWIDTH 0x00 // 10 Hz
//#define BMA180_BANDWIDTH 0x01 // 20 Hz
//#define BMA180_BANDWIDTH 0x02 // 40 Hz
//#define BMA180_BANDWIDTH 0x03 // 75 Hz
//#define BMA180_BANDWIDTH 0x04 // 150 Hz
//#define BMA180_BANDWIDTH 0x05 // 300 Hz
//#define BMA180_BANDWIDTH 0x06 // 600 Hz
#define BMA180_BANDWIDTH 0x07 // 1200 Hz
//#define BMA180_BANDWIDTH 0x08 // high-pass: 1 Hz
//#define BMA180_BANDWIDTH 0x09 // band-pass: 0.2 Hz ... 300 Hz  

//pick your acceleration sensitivity range
#define BMA180_RANGE 0x00 // +/- 1g
//#define BMA180_RANGE 0x01 // +/- 1.5g
//#define BMA180_RANGE 0x02 // +/- 2g
//#define BMA180_RANGE 0x03 // +/- 3g
//#define BMA180_RANGE 0x04 // +/- 4g
//#define BMA180_RANGE 0x05 // +/- 8g
//#define BMA180_RANGE 0x06 // +/- 16g

//pick your mode
#define BMA180_MODE 0x00 //low noise mode
//#define BMA180_MODE 0x03 //low power mode

void setup()
{
  Serial.begin(57600);
  initBMA180();
  Serial.println("MakerBot Industries Accelerometer Logger v1.0");
}

void loop()
{

  readAccel();

  delay(10);
}

