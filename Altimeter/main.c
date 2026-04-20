/*
 * Altimeter.c
 *
 * Created: 18/04/2026 18:16:53
 * Author : griku
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "my_I2C.h"
#include "BMI270.h"
#include "BMI270_reg.h"
#include "BME280.h"
#include "BME280_reg.h"
#include "P_cal.h"
#include "SDcard.h"

#define F_CPU 16000000UL

void timerConfig()	// configure 16bit timer
{
	TCCR1B |= (1<<WGM12);	// CTC mode (auto reload)
	TCCR1B |= (1<<CS10 | 1<<CS11); // prescaler to f_clk/64 to get a full timer period of 0.26214s count to (25000-1)/65535 to get 0.1s = 10Hz
	OCR1A = 24999U;	//equivalent to 100ms
	TIMSK1 |= (1<<OCIE1A); // enable match interrupt to trigger when timer is equal to OCR1A 
}

ISR(TIMER1_COMPA_vect)
{
	PORTD = PORTD ^ 1<<PORTD6;
	writeData();
	
}

void writeData()
{
	unsigned char ax_MSB, ax_LSB, ay_MSB, ay_LSB, az_MSB, az_LSB, gx_MSB, gx_LSB, gy_MSB, gy_LSB, gz_MSB, gz_LSB, p_MSB, p_LSB, p;
	unsigned short data_sample[7];	//16 bit int array
	ax_LSB = I2C_MasterReceiveByte(BMI270_address, ACC_X_LSB_address);
	ax_MSB = I2C_MasterReceiveByte(BMI270_address, ACC_X_MSB_address);
	
	ay_LSB = I2C_MasterReceiveByte(BMI270_address, ACC_Y_LSB_address);
	ay_MSB = I2C_MasterReceiveByte(BMI270_address, ACC_Y_MSB_address);
		
	az_LSB = I2C_MasterReceiveByte(BMI270_address, ACC_Z_LSB_address);
	az_MSB = I2C_MasterReceiveByte(BMI270_address, ACC_Z_MSB_address);

	gx_LSB = I2C_MasterReceiveByte(BMI270_address, GYR_X_LSB_address);
	gx_MSB = I2C_MasterReceiveByte(BMI270_address, GYR_X_MSB_address);

	gy_LSB = I2C_MasterReceiveByte(BMI270_address, GYR_Y_LSB_address);
	gy_MSB = I2C_MasterReceiveByte(BMI270_address, GYR_Y_MSB_address);

	gz_LSB = I2C_MasterReceiveByte(BMI270_address, GYR_Z_LSB_address);
	gz_MSB = I2C_MasterReceiveByte(BMI270_address, GYR_Z_MSB_address);
		
	p_LSB = I2C_MasterReceiveByte(BME280_address, BME280_press_LSB_data_address);
	p_MSB = I2C_MasterReceiveByte(BME280_address, BME280_press_MSB_data_address);
		
		
	unsigned short p_cal;
	p = (p_MSB<<8) | p_LSB;
	p_cal = Calibrate_pressure(p);
		
	data_sample[0] = (ax_MSB<<8) | ax_LSB;
	data_sample[1] = (ay_MSB<<8) | ay_LSB;
	data_sample[2] = (az_MSB<<8) | az_LSB;
	data_sample[3] = (gx_MSB<<8) | gx_LSB;
	data_sample[4] = (gy_MSB<<8) | gy_LSB;
	data_sample[5] = (gz_MSB<<8) | gz_LSB;
	data_sample[6] = p_cal * 16.0U;
		
	SD_sample_write(&data_sample);
}


int main(void)
{
	DDRD |= (1<<3);	//orange
	DDRD |= (1<<4);	//yellow
	DDRD |= (1<<5);	//red
	DDRD |= (1<<6);	//green
	DDRD |= (1<<7);	//white
	
	
	I2C_MasterInit();
	BMI270_init();
	BMI270_config();
	BME280_config();
	Read_calibration_params();
	init_sd_card();
	
	sei();
	timerConfig();
	
    while (1) 
    {
		
    }

}
