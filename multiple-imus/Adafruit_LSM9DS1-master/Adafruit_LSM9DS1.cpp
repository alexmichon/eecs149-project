/***************************************************************************
  This is a library for the LSM9DS1 Accelerometer and magnentometer/compass

  Designed specifically to work with the Adafruit LSM9DS1 Breakouts

  These sensors use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <Adafruit_LSM9DS1.h>

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

void Adafruit_LSM9DS1::initI2C( TwoWire* wireBus, int32_t sensorID ) {
    _i2c = true;
    _wire = wireBus;
    _lsm9dso_sensorid_accel = sensorID + 1;
    _lsm9dso_sensorid_gyro = sensorID + 2;
    _accelSensor = Sensor(this, &Adafruit_LSM9DS1::readAccel, &Adafruit_LSM9DS1::getAccelEvent, &Adafruit_LSM9DS1::getAccelSensor);
    _gyroSensor  = Sensor(this, &Adafruit_LSM9DS1::readGyro,  &Adafruit_LSM9DS1::getGyroEvent,  &Adafruit_LSM9DS1::getGyroSensor);
}


// default
Adafruit_LSM9DS1::Adafruit_LSM9DS1( int32_t sensorID ) {
    initI2C(&Wire, sensorID);
}

Adafruit_LSM9DS1::Adafruit_LSM9DS1( TwoWire* wireBus, int32_t sensorID ) {
    initI2C(wireBus, sensorID);
}

Adafruit_LSM9DS1::Adafruit_LSM9DS1(int8_t xgcs, int32_t sensorID ) {
  _i2c = false;
  // hardware SPI!
  _csxg = xgcs;
  _mosi = _miso = _clk = -1;
  _lsm9dso_sensorid_accel = sensorID + 1;
  _lsm9dso_sensorid_gyro = sensorID + 2;
  _accelSensor = Sensor(this, &Adafruit_LSM9DS1::readAccel, &Adafruit_LSM9DS1::getAccelEvent, &Adafruit_LSM9DS1::getAccelSensor);
  _gyroSensor  = Sensor(this, &Adafruit_LSM9DS1::readGyro,  &Adafruit_LSM9DS1::getGyroEvent,  &Adafruit_LSM9DS1::getGyroSensor);
}

Adafruit_LSM9DS1::Adafruit_LSM9DS1(int8_t sclk, int8_t smiso, int8_t smosi, int8_t xgcs, int32_t sensorID ) {
  _i2c = false;
  // software SPI!
  _csxg = xgcs;
  _mosi = smosi;
  _miso = smiso;
  _clk = sclk;
  _lsm9dso_sensorid_accel = sensorID + 1;
  _lsm9dso_sensorid_gyro = sensorID + 2;
  _accelSensor = Sensor(this, &Adafruit_LSM9DS1::readAccel, &Adafruit_LSM9DS1::getAccelEvent, &Adafruit_LSM9DS1::getAccelSensor);
  _gyroSensor  = Sensor(this, &Adafruit_LSM9DS1::readGyro,  &Adafruit_LSM9DS1::getGyroEvent,  &Adafruit_LSM9DS1::getGyroSensor);
}

bool Adafruit_LSM9DS1::begin()
{
  if (_i2c) {
    _wire->begin();
  } else if (_clk == -1) {
    // Hardware SPI
    pinMode(_csxg, OUTPUT);
    digitalWrite(_csxg, HIGH);
    SPI.begin();
  } else {
    //Serial.println("softSPI");
    // Sofware SPI
    pinMode(_clk, OUTPUT);
    pinMode(_mosi, OUTPUT);
    pinMode(_miso, INPUT);
    pinMode(_csxg, OUTPUT);
    digitalWrite(_csxg, HIGH);
    digitalWrite(_clk, HIGH);
  }


  // soft reset & reboot accel/gyro
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG8, 0x05);

  delay(10);


  /*
  for (uint8_t i=0; i<0x30; i++) {
    Serial.print("XG $"); Serial.print(i, HEX); Serial.print(" = 0x"); 
    Serial.println(read8(XGTYPE, i), HEX);
  }
  for (uint8_t i=0; i<0x30; i++) {
    Serial.print("M $"); Serial.print(i, HEX); Serial.print(" = 0x"); 
    Serial.println(read8(MAGTYPE, i), HEX);
  }
  */

  uint8_t id = read8(XGTYPE, LSM9DS1_REGISTER_WHO_AM_I_XG);
  //Serial.print ("XG whoami: 0x"); Serial.println(id, HEX);
  Serial.println(id);
  if (id != LSM9DS1_XG_ID) {
    //return false;
  }

  // enable gyro continuous
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG1_G, 0xC0); // on XYZ

  // Enable the accelerometer continous
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG5_XL, 0x38); // enable X Y and Z axis
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG6_XL, 0xC0); // 1 KHz out data rate, BW set by ODR, 408Hz anti-aliasing



  // Set default ranges for the various sensors  
  setupAccel(LSM9DS1_ACCELRANGE_2G);
  setupGyro(LSM9DS1_GYROSCALE_245DPS);

  return true;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/
void Adafruit_LSM9DS1::read()
{
  /* Read all the sensors. */
  readAccel();
  readGyro();
}

void Adafruit_LSM9DS1::readAccel() {
  // Read the accelerometer
  byte buffer[6];
  readBuffer(XGTYPE, 
       0x80 | LSM9DS1_REGISTER_OUT_X_L_XL, 
       6, buffer);
  
  uint8_t xlo = buffer[0];
  int16_t xhi = buffer[1];
  uint8_t ylo = buffer[2];
  int16_t yhi = buffer[3];
  uint8_t zlo = buffer[4];
  int16_t zhi = buffer[5];
  
  // Shift values to create properly formed integer (low byte first)
  xhi <<= 8; xhi |= xlo;
  yhi <<= 8; yhi |= ylo;
  zhi <<= 8; zhi |= zlo;
  accelData.x = xhi;
  accelData.y = yhi;
  accelData.z = zhi;
}

void Adafruit_LSM9DS1::readGyro() {
  // Read gyro
  byte buffer[6];
  readBuffer(XGTYPE, 
       0x80 | LSM9DS1_REGISTER_OUT_X_L_G, 
       6, buffer);
  
  uint8_t xlo = buffer[0];
  int16_t xhi = buffer[1];
  uint8_t ylo = buffer[2];
  int16_t yhi = buffer[3];
  uint8_t zlo = buffer[4];
  int16_t zhi = buffer[5];
  
  // Shift values to create properly formed integer (low byte first)
  xhi <<= 8; xhi |= xlo;
  yhi <<= 8; yhi |= ylo;
  zhi <<= 8; zhi |= zlo;
  
  gyroData.x = xhi;
  gyroData.y = yhi;
  gyroData.z = zhi;
}

void Adafruit_LSM9DS1::setupAccel ( lsm9ds1AccelRange_t range )
{
  uint8_t reg = read8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG6_XL);
  reg &= ~(0b00011000);
  reg |= range;
  //Serial.println("set range: ");
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG6_XL, reg );
  
  switch (range)
  {
    case LSM9DS1_ACCELRANGE_2G:
      _accel_mg_lsb = LSM9DS1_ACCEL_MG_LSB_2G;
      break;
    case LSM9DS1_ACCELRANGE_4G:
      _accel_mg_lsb = LSM9DS1_ACCEL_MG_LSB_4G;
      break;
    case LSM9DS1_ACCELRANGE_8G:
      _accel_mg_lsb = LSM9DS1_ACCEL_MG_LSB_8G;
      break;    
    case LSM9DS1_ACCELRANGE_16G:
      _accel_mg_lsb =LSM9DS1_ACCEL_MG_LSB_16G;
      break;
  }
}

void Adafruit_LSM9DS1::setupGyro ( lsm9ds1GyroScale_t scale )
{
  uint8_t reg = read8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG1_G);
  reg &= ~(0b00110000);
  reg |= scale;
  write8(XGTYPE, LSM9DS1_REGISTER_CTRL_REG1_G, reg );

  switch(scale)
  {
    case LSM9DS1_GYROSCALE_245DPS:
      _gyro_dps_digit = LSM9DS1_GYRO_DPS_DIGIT_245DPS;
      break;
    case LSM9DS1_GYROSCALE_500DPS:
      _gyro_dps_digit = LSM9DS1_GYRO_DPS_DIGIT_500DPS;
      break;
    case LSM9DS1_GYROSCALE_2000DPS:
      _gyro_dps_digit = LSM9DS1_GYRO_DPS_DIGIT_2000DPS;
      break;
  }
}


/***************************************************************************
 UNIFIED SENSOR FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Gets the most recent accel sensor event
*/
/**************************************************************************/
bool Adafruit_LSM9DS1::getEvent(sensors_event_t *accelEvent,
                                sensors_event_t *gyroEvent)
{
  /* Grab new sensor reading and timestamp. */
  read();
  uint32_t timestamp = millis();

  /* Update appropriate sensor events. */
  if (accelEvent) getAccelEvent(accelEvent, timestamp);
  if (gyroEvent)  getGyroEvent(gyroEvent, timestamp);
  
  return true;
}

/**************************************************************************/
/*!
    @brief  Gets the sensor_t data
*/
/**************************************************************************/
void Adafruit_LSM9DS1::getSensor(sensor_t *accel, sensor_t *gyro)
{
  /* Update appropriate sensor metadata. */
  if (accel) getAccelSensor(accel);
  if (gyro)  getGyroSensor(gyro);
}

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/
void Adafruit_LSM9DS1::write8(boolean type, byte reg, byte value)
{
  byte address, _cs;

  if (type == XGTYPE) {
    address = LSM9DS1_ADDRESS_ACCELGYRO;
    _cs = _csxg;
  }
  if (_i2c) {
    _wire->beginTransmission(address);
    _wire->write(reg);
    _wire->write(value);
    _wire->endTransmission();
    /*
    Serial.print("0x"); Serial.print(address, HEX);
    Serial.print(" $"); Serial.print(reg, HEX); Serial.print(" = ");
    Serial.println(value, HEX);
    */
  } else {
    digitalWrite(_cs, LOW);
    if (_clk == -1)     // hardware SPI
      SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE0));
    // set address
    spixfer(reg & 0x7F); // write data
    spixfer(value);
    if (_clk == -1)     // hardware SPI
      SPI.endTransaction();
    digitalWrite(_cs, HIGH);

  }
}

byte Adafruit_LSM9DS1::read8(boolean type, byte reg)
{
  uint8_t value;

  readBuffer(type, reg, 1, &value);

  return value;
}

byte Adafruit_LSM9DS1::readBuffer(boolean type, byte reg, byte len, uint8_t *buffer)
{
  byte address, _cs;

  if (type == XGTYPE) {
    address = LSM9DS1_ADDRESS_ACCELGYRO;
    _cs = _csxg;
  }

  if (_i2c) {
    _wire->beginTransmission(address);
    _wire->write(reg);
    _wire->endTransmission();
    if (_wire->requestFrom(address, (byte)len) != len) {
      return 0;
    }

    /*
      Serial.print("0x"); Serial.print(address, HEX);
      Serial.print(" $"); Serial.print(reg, HEX); Serial.print(": ");
    */

    for (uint8_t i=0; i<len; i++) {
      buffer[i] = _wire->read();
      //Serial.print(buffer[i], HEX); Serial.print(", ");
    }
    //Serial.println();

  } else {
    if (_clk == -1)     // hardware SPI
      SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE0));
    else
      digitalWrite(_clk, HIGH);
    // set address

    digitalWrite(_cs, LOW);

    spixfer(reg | 0x80 ); // readdata
    for (uint8_t i=0; i<len; i++) {
      buffer[i] = spixfer(0);
    }
    if (_clk == -1)     // hardware SPI
      SPI.endTransaction();
    else
      digitalWrite(_clk, HIGH);
    digitalWrite(_cs, HIGH);
  }

  return len;
}

uint8_t Adafruit_LSM9DS1::spixfer(uint8_t data) {

  if (_clk == -1) {
      //Serial.println("Hardware SPI");
      return SPI.transfer(data);
  } else {
    //Serial.println("Software SPI");
    uint8_t reply = 0;    
    for (int i=7; i>=0; i--) {
      reply <<= 1;
      digitalWrite(_clk, LOW);
      digitalWrite(_mosi, data & (1<<i));
      digitalWrite(_clk, HIGH);
      if (digitalRead(_miso)) 
	reply |= 1;
    }
    return reply;
  }
}

void Adafruit_LSM9DS1::getAccelEvent(sensors_event_t* event, uint32_t timestamp) {
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _lsm9dso_sensorid_accel;
  event->type      = SENSOR_TYPE_ACCELEROMETER;
  event->timestamp = timestamp;
  event->acceleration.x = accelData.x * _accel_mg_lsb;
  event->acceleration.x /= 1000;
  event->acceleration.x *= SENSORS_GRAVITY_STANDARD;
  event->acceleration.y = accelData.y * _accel_mg_lsb;
  event->acceleration.y /= 1000;
  event->acceleration.y *= SENSORS_GRAVITY_STANDARD;
  event->acceleration.z = accelData.z * _accel_mg_lsb;
  event->acceleration.z /= 1000;
  event->acceleration.z *= SENSORS_GRAVITY_STANDARD;
}

void Adafruit_LSM9DS1::getGyroEvent(sensors_event_t* event, uint32_t timestamp) {
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _lsm9dso_sensorid_accel;
  event->type      = SENSOR_TYPE_GYROSCOPE;
  event->timestamp = timestamp;
  event->gyro.x = gyroData.x * _gyro_dps_digit;
  event->gyro.y = gyroData.y * _gyro_dps_digit;
  event->gyro.z = gyroData.z * _gyro_dps_digit;
}

void Adafruit_LSM9DS1::getAccelSensor(sensor_t* sensor) {
  memset(sensor, 0, sizeof(sensor_t));
  strncpy (sensor->name, "LSM9DS1_A", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _lsm9dso_sensorid_accel;
  sensor->type        = SENSOR_TYPE_ACCELEROMETER;
  sensor->min_delay   = 0;
  sensor->max_value   = 0.0;  // ToDo
  sensor->min_value   = 0.0;  // ToDo
  sensor->resolution  = 0.0;  // ToDo
}

void Adafruit_LSM9DS1::getGyroSensor(sensor_t* sensor) {
  memset(sensor, 0, sizeof(sensor_t));
  strncpy (sensor->name, "LSM9DS1_G", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _lsm9dso_sensorid_gyro;
  sensor->type        = SENSOR_TYPE_GYROSCOPE;
  sensor->min_delay   = 0;
  sensor->max_value   = 0.0;  // ToDo
  sensor->min_value   = 0.0;  // ToDo
  sensor->resolution  = 0.0;  // ToDo
}