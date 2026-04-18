/*
 * SDcard.h
 *
 * Created: 07/11/2024 14:16:26
 *  Author: Simon Pope
 */ 


#ifndef SDCARD_H_
#define SDCARD_H_

void    init_sd_card(void);
void	SD_sample_write(unsigned short *);
void	get_fattime(void);

#endif /* SDCARD_H_ */