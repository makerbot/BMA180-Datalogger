#define BMA180_ADDRESS 0x40
#define BMA180_CHIP_ID 0x03

//bandwidth / filter mode constants
#define BMA180_BANDWIDTH_10HZ     0x00
#define BMA180_BANDWIDTH_20HZ     0x01
#define BMA180_BANDWIDTH_40HZ     0x02
#define BMA180_BANDWIDTH_75HZ     0x03
#define BMA180_BANDWIDTH_150HZ    0x04
#define BMA180_BANDWIDTH_300HZ    0x05
#define BMA180_BANDWIDTH_600HZ    0x06
#define BMA180_BANDWIDTH_1200HZ   0x07
#define BMA180_BANDWIDTH_HIGHPASS 0x08 // high-pass: 1 Hz
#define BMA180_BANDWIDTH_BANDPASS 0x09 // band-pass: 0.2 Hz ... 300 Hz  

//acceleration sensitivity range constants
#define BMA180_RANGE_1G     0x00
#define BMA180_RANGE_1DOT5G 0x01
#define BMA180_RANGE_2G     0x02
#define BMA180_RANGE_3G     0x03
#define BMA180_RANGE_4G     0x04
#define BMA180_RANGE_8G     0x05
#define BMA180_RANGE_16G    0x06

//pick your mode
#define BMA180_MODE_LOW_NOISE 0x00
#define BMA180_MODE_LOW_POWER 0x03

#define BMA180_CMD_CHIP_ID          0x00
#define BMA180_CMD_VERSION          0x01
#define BMA180_CMD_ACC_X_LSB        0x02
#define BMA180_CMD_ACC_X_MSB        0x03
#define BMA180_CMD_ACC_Y_LSB        0x04
#define BMA180_CMD_ACC_Y_MSB        0x05
#define BMA180_CMD_ACC_Z_LSB        0x06
#define BMA180_CMD_ACC_Z_MSB        0x07
#define BMA180_CMD_TEMP             0x08
#define BMA180_CMD_STATUS_REG1      0x09
#define BMA180_CMD_STATUS_REG2      0x0A
#define BMA180_CMD_STATUS_REG3      0x0B
#define BMA180_CMD_STATUS_REG4      0x0C
#define BMA180_CMD_CTRL_REG0        0x0D
#define BMA180_CMD_CTRL_REG1        0x0E
#define BMA180_CMD_CTRL_REG2        0x0F
#define BMA180_CMD_RESET            0x10
#define BMA180_CMD_BW_TCS           0x20
#define BMA180_CMD_CTRL_REG3        0x21
#define BMA180_CMD_CTRL_REG3        0x22


void BMA180_Init(byte address)
{
  int id = BMA180_ReadId(address);
  
  if(id == BMA180_CHIP_ID)
  {
    Serial.println("BMA180 Chip Detect Pass");
    
    // Connect to the ctrl_reg1 register and set the ee_w bit to enable writing.
    if (BMA180_WriteByte(address, BMA180_CMD_CTRL_REG0, 0x01) == 0)
      Serial.println("BMA180 Write Init Pass");
    else
      Serial.println("BMA180 Write Init Fail")
  }
  else
    Serial.println("BMA180 Chip Detect Fail");
}

byte BMA180_ReadByte(byte i2c_address, byte address)
{
  byte temp;
  
  Wire.beginTransmission(i2c_address);
  Wire.send(address);
  Wire.requestFrom(i2c_address, 1);
  while(Wire.available())
  {
    temp = Wire.receive();
  }
  
  return temp;
}

byte BMA180_WriteByte(byte i2c_address, byte address, byte data)
{
  Wire.beginTransmission(i2c_address);
  Wire.send(address);
  Wire.send(data);
  result = Wire.endTransmission();

  //do some error checking
  if(result > 0)
  {
    Serial.print("PROBLEM..... Result code is ");
    Serial.println(result);
  }
  else
  {
    Serial.println("Read/Write success");
  }
  
  //the BMA180 has slow EEPROM.  take it easy.
  delay(10);

  return result;
}

void BMA180_ReadId(address)
{
  //get the contents of the chip id register.
  return BMA180_ReadByte(address, BMA180_CMD_CHIP_ID);
}

void BMA180_SetBandwidth(byte address, byte bandwidth)
{
  // Connect to the bw_tcs register and set the filtering level
  BMA180_WriteByte(address, BMA180_CMD_BW_TCS, bandwidth << 4);
}

void BMA180_SetRange(byte address, byte range)
{
  // Connect to the offset_lsb1 register and set the range
  BMA180_WriteByte(address, 0x35, range << 1);
}

byte BMA180_ReadTemperature()
{
  return BMA180_ReadByte(address, BMA180_CMD_TEMP);
}

int BMA180_ReadX()
{
  int data = 0;
  
  data = BMA180_ReadByte(address, BMA180_CMD_ACC_X_MSB);
  data = temp << 6;
  data |= BMA180_ReadByte(address, BMA180_CMD_ACC_X_LSB) >> 2;
  
  return data;
}

int BMA180_ReadY()
{
  int data = 0;
  
  data = BMA180_ReadByte(address, BMA180_CMD_ACC_Y_MSB);
  data = temp << 6;
  data |= BMA180_ReadByte(address, BMA180_CMD_ACC_Y_LSB) >> 2;
  
  return data;
}

int BMA180_ReadZ()
{
  int data = 0;
  
  data = BMA180_ReadByte(address, BMA180_CMD_ACC_Z_MSB);
  data = temp << 6;
  data |= BMA180_ReadByte(address, BMA180_CMD_ACC_Z_LSB) >> 2;
  
  return data;
}