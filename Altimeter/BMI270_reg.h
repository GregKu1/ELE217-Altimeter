/*
 * BMI270_reg.h
 *
 * Created: 05/11/2024 11:43:03
 *  Author: Simon Pope
 */ 

#include <avr/pgmspace.h>

#ifndef BMI270_REG_H_
#define BMI270_REG_H_

// BMI270 I2C address
#define BMI270_address UINT8_C(0x68<<1)

// BMI270 register addresses
#define ACC_CONF_address UINT8_C(0x40)
#define ACC_RANGE_address UINT8_C(0x41)
#define GYR_CONF_address UINT8_C(0x42)
#define GYR_RANGE_address UINT8_C(0x43)
#define ACC_X_LSB_address UINT8_C(0x0C)
#define ACC_X_MSB_address UINT8_C(0x0D)
#define ACC_Y_LSB_address UINT8_C(0x0E)
#define ACC_Y_MSB_address UINT8_C(0x0F)
#define ACC_Z_LSB_address UINT8_C(0x10)
#define ACC_Z_MSB_address UINT8_C(0x11)
#define GYR_X_LSB_address UINT8_C(0x12)
#define GYR_X_MSB_address UINT8_C(0x13)
#define GYR_Y_LSB_address UINT8_C(0x14)
#define GYR_Y_MSB_address UINT8_C(0x15)
#define GYR_Z_LSB_address UINT8_C(0x16)
#define GYR_Z_MSB_address UINT8_C(0x17)

// ACC ODR values
#define ACC_ODR_0p78Hz UINT8_C(0xA1)
#define ACC_ODR_1p5Hz UINT8_C(0xA2)
#define ACC_ODR_3p1Hz UINT8_C(0xA3)
#define ACC_ODR_6p25Hz UINT8_C(0xA4)
#define ACC_ODR_12p5Hz UINT8_C(0xA5)
#define ACC_ODR_25Hz UINT8_C(0xA6)
#define ACC_ODR_50Hz UINT8_C(0xA7)
#define ACC_ODR_100Hz UINT8_C(0xA8)
#define ACC_ODR_200Hz UINT8_C(0xA9)
#define ACC_ODR_400Hz UINT8_C(0xAA)
#define ACC_ODR_800Hz UINT8_C(0xAB)
#define ACC_ODR_1600Hz UINT8_C(0xAC)
#define ACC_ODR_3200Hz UINT8_C(0xAD)
#define ACC_ODR_6400Hz UINT8_C(0xAE)
#define ACC_ODR_12800Hz UINT8_C(0xAF)


// ACC RANGE values
#define ACC_RANGE_2g UINT8_C(0x00)
#define ACC_RANGE_4g UINT8_C(0x01)
#define ACC_RANGE_8g UINT8_C(0x02)
#define ACC_RANGE_16g UINT8_C(0x03)

// GYR ODR values
#define GYR_ODR_0p78Hz UINT8_C(0xA1)
#define GYR_ODR_1p5Hz UINT8_C(0xA2)
#define GYR_ODR_3p1Hz UINT8_C(0xA3)
#define GYR_ODR_6p25Hz UINT8_C(0xA4)
#define GYR_ODR_12p5Hz UINT8_C(0xA5)
#define GYR_ODR_25Hz UINT8_C(0xA6)
#define GYR_ODR_50Hz UINT8_C(0xA7)
#define GYR_ODR_100Hz UINT8_C(0xA8)
#define GYR_ODR_200Hz UINT8_C(0xA9)
#define GYR_ODR_400Hz UINT8_C(0xAA)
#define GYR_ODR_800Hz UINT8_C(0xAB)
#define GYR_ODR_1600Hz UINT8_C(0xAC)
#define GYR_ODR_3200Hz UINT8_C(0xAD)
#define GYR_ODR_6400Hz UINT8_C(0xAE)
#define GYR_ODR_12800Hz UINT8_C(0xAF)

// GYR RANGE values
#define GYR_RANGE_2000dps UINT8_C(0x00)
#define GYR_RANGE_1000dps UINT8_C(0x01)
#define GYR_RANGE_500dps UINT8_C(0x02)
#define GYR_RANGE_250dps UINT8_C(0x03)
#define GYR_RANGE_125dps UINT8_C(0x04)

#endif /* BMI270_REG_H_ */