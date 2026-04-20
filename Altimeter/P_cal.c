/*
 * P_cal.c
 *
 * Created: 22/04/2025 16:59:59
 *  Author: Simon Pope
 */ 

#include <avr/io.h>
#include "BME280_reg.h"
#include "BME280.h"

uint16_t dig_p1;
int16_t dig_p2, dig_p3, dig_p4, dig_p5, dig_p6, dig_p7, dig_p8, dig_p9;

// Reads pressure calibration parameters from BME280
// Call this function once after you initialise the BME280 and before you read any pressure data
void Read_calibration_params(void){
	
	unsigned short dig_LSB,dig_MSB;
	
	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x8e);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x8f);
	dig_p1 = (dig_MSB<<8)|dig_LSB;

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x90);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x91);
	dig_p2 = (int16_t)((dig_MSB<<8)|dig_LSB);
	
	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x92);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x93);
	dig_p3 = (int16_t)((dig_MSB<<8)|dig_LSB);	

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x94);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x95);
	dig_p4= (int16_t)((dig_MSB<<8)|dig_LSB);

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x96);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x97);
	dig_p5 = (int16_t)((dig_MSB<<8)|dig_LSB);

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x98);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x99);
	dig_p6 = (int16_t)((dig_MSB<<8)|dig_LSB);	

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x9a);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x9b);
	dig_p7 = (int16_t)((dig_MSB<<8)|dig_LSB);

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x9c);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x9d);
	dig_p8 = (int16_t)((dig_MSB<<8)|dig_LSB);

	dig_LSB = I2C_MasterReceiveByte(BME280_address,0x9e);
	dig_MSB = I2C_MasterReceiveByte(BME280_address,0x9f);
	dig_p9 = (int16_t)((dig_MSB<<8)|dig_LSB);
}

// Function to provide 16-bit calibrated pressure output based on suggested requirements in the BME280 data sheet
// Call this function to calculate the 16-bit calibrated pressure value for each sample read form the BME280
// Input "P" is the uncalibrated 16-bit pressure
// Output "pressure" is the calibrated 16-bit pressure. The pressure in Pascals is the 16-bit calibrated pressure multiplied by 16 (you will need to calculate the pressure in Pascals off-chip unless you increase the precision of the pressure value saved to the SD card)
// Temperature compensation is based on a fixed temperature defined in the variable T and not the true calibrated temperature read from the BME280
uint16_t Calibrate_pressure(uint16_t P){

	int32_t T=2000; // Value for user specified fixed temperature correction defined in hundredths of a Celsius, i.e. 1999 19.99 degrees Celsius, 2000 is 20.00 degrees Celsius, 2001 is 20.01 degrees Celsius, etc.
	int32_t t_fine,P_l;
	int32_t var1,var2,var3,var4;
	uint32_t var5;
	uint32_t pressure;
	uint32_t pressure_min = 30000,pressure_max = 110000;
	uint16_t P_cal;

	P_l = ((int32_t)(P))<<4;
	t_fine = ((T<<8)-128)/5;

	var1 = (((int32_t)t_fine) / 2) - (int32_t)64000;
	var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t)dig_p6);
	var2 = var2 + ((var1 * ((int32_t)dig_p5)) * 2);
	var2 = (var2 / 4) + (((int32_t)dig_p4) * 65536);
	var3 = (dig_p3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
	var4 = (((int32_t)dig_p2) * var1) / 2;
	var1 = (var3 + var4) / 262144;
	var1 = (((32768 + var1)) * ((int32_t)dig_p1)) / 32768;

	/* Avoid exception caused by division by zero */
	if (var1)
	{
		var5 = (uint32_t)((uint32_t)1048576) - P_l;
		pressure = ((uint32_t)(var5 - (uint32_t)(var2 / 4096))) * 3125;

		if (pressure < 0x80000000)
		{
			pressure = (pressure << 1) / ((uint32_t)var1);
		}
		else
		{
			pressure = (pressure / (uint32_t)var1) * 2;
		}

		var1 = (((int32_t)dig_p9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
		var2 = (((int32_t)(pressure / 4)) * ((int32_t)dig_p8)) / 8192;
		pressure = (uint32_t)((int32_t)pressure + ((var1 + var2 + dig_p7) / 16));

		if (pressure < pressure_min)
		{
			pressure = pressure_min;
		}
		else if (pressure > pressure_max)
		{
			pressure = pressure_max;
		}
	}
	else
	{
		pressure = pressure_min;
	}

	pressure = pressure>>4;
	P_cal = (unsigned short)pressure;
	return P_cal;

}