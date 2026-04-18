/*
 * BME280.c
 *
 * Created: 05/11/2024 09:40:55
 *  Author: Simon Pope
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "BME280_reg.h"


void BME280_config(void){
	
	unsigned char BME_data;
	unsigned char ret=1;
	
	// Read the contents of an appropriate register on the BME280 and blink the white LED on and off for 1 second to indicate correct I2C communication between ATmega328P and BME280	
	// Add the missing code here
	I2C_start();
	I2C_MasterTransmitAddress(BME280_address, 0xD0);
	_delay_ms(500);
	I2C_start();
	BME_data = I2C_MasterReceiveByte(BME280_address);
	I2C_stop();
	
	if (BME_data == 0x60)
	{
		PORTD |= 1<<PORTD7;
		_delay_ms(1000);
		PORTD &= ~(1<<PORTD7);
		_delay_ms(1000);
	}
	else
	{
		PORTD &= ~(1<<PORTD7);
	}
	
	
	/* Settings for BME280 config */
	// Set a sample rate of 250Hz: Set standby time to 0.5ms to give cycle time of tm+ts = (1+2x1+0.5) + 0.5 (t_sb=000) = 4ms which corresponds to 250Hz (tm=1+2xosrs_p+0.5)
	// Set pressure output to 16-bit so that pressure LSB and MSB data registers are needed: Disable IIR and set osrs_p = 1 to give 16 bit data 16+(osrs_p=1)
	
	// Register "config" with address 0xf5 set to 0x00 - bits 7,6,5 set to 000 for t_sb = 0.5ms, bits 4,3,2 set to 000 for IIR filter off bit 0 set to 0 to disable SPI
	I2C_MasterTransmitByte(BME280_address,BME280_config_register_address,0x00);
	
	// Register "ctrl_meas" with address 0xf4 set to 0x07 - Bit 7,6,5 set to 000 for temperature disabled (osrs_t=0), bits 4,3,2 set to to 001 for pressure sensor enabled with oversampling osrs_p=1 and bits 1,0 set to 11 for normal mode
	I2C_MasterTransmitByte(BME280_address,BME280_ctrl_meas_register_address,0x07);
	
	// Register "ctrl_hum" with address 0xf2 set to 0x00 - bits 3,1,0 set to 000 for humidity disabled (osrs_h = 0)
	I2C_MasterTransmitByte(BME280_address,BME280_hum_register_address,0x00);
	
	// Turn white LED on to indicate end of BME280 config
	PORTD |= 1<<PORTD7;
}