/*
 * BME280_reg.h
 *
 * Created: 05/11/2024 11:42:47
 *  Author: Simon Pope
 */ 


#ifndef BME280_REG_H_
#define BME280_REG_H_

#define BME280_address UINT8_C(0x76<<1)

#define BME280_hum_register_address 0xf2
#define BME280_ctrl_meas_register_address 0xf4
#define BME280_config_register_address 0xf5
#define BME280_press_MSB_data_address 0xf7
#define BME280_press_LSB_data_address 0xf8

#endif /* BME280_REG_H_ */