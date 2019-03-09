#include <Wire.h>

#define MPU_I2C_ADDR 0x68


void setup() {
  Wire.begin();

  // wake up MPU by setting 0x6B to 0
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1
  Wire.write(0);     // wake up command
  Wire.endTransmission(true);

  // switch sensitivity of MPU to +/16g
  // by setting bit 3 & 4 of register 0x1C to 
  // ( see MPU-6000-Register-Map1.pdf p15)
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(0x1C);  // MPU6050_ACCEL_CONFIG
  //Wire.write(0<<3);  // +/-2g => AFS_SEL=0, in bits 3 & 4
  Wire.write(3<<3);  // +/-16g => AFS_SEL=3, in bits 3 & 4
  Wire.endTransmission(true);

  // Set 
  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(0x3B);  // ACCEL_XOUT_H
  Wire.endTransmission(false); // hold i2c bus for next read
  Wire.requestFrom(MPU_I2C_ADDR, 14, true); // next 14 registers and release i2c bus (true)
  //int16_t linear_accel_x, linear_accel_y, linear_accel_z, tmp, gyro_x, gyro_y, gyro_z;

  // At sensitivity of 16g we need to scale by 2048. (warning: from eyeballing!!)
  const float la_rescale = 2048.0;
  float linear_accel_x = (Wire.read()<<8 | Wire.read()) / la_rescale;
  float linear_accel_y = (Wire.read()<<8 | Wire.read()) / la_rescale;
  float linear_accel_z = (Wire.read()<<8 | Wire.read()) / la_rescale;
  
  float temp_c = ((Wire.read()<<8 | Wire.read()) / 340.0) + 36.53;

  // At default sensitivity of 250deg/s we need to scale by 131.
  const float av_rescale = 131.0;
  float angular_velocity_x = (Wire.read()<<8 | Wire.read()) / av_rescale;
  float angular_velocity_y = (Wire.read()<<8 | Wire.read()) / av_rescale;
  float angular_velocity_z = (Wire.read()<<8 | Wire.read()) / av_rescale;
  
  Serial.print(linear_accel_x); 
  Serial.print(" "); Serial.print(linear_accel_y); 
  Serial.print(" "); Serial.print(linear_accel_z); 
  Serial.print(" "); Serial.print(temp_c); 
  Serial.print(" "); Serial.print(angular_velocity_x); 
  Serial.print(" "); Serial.print(angular_velocity_y); 
  Serial.print(" "); Serial.print(angular_velocity_z); 
  Serial.println();
  delay(1000);
}
