/*
 * LTC_SPI.c
 *
 *  Created on: Dec 29, 2016
 *      Author: elenahuang
 */

#include "LTC_SPI.h"
#include "stm32l4xx_hal.h"
#include "stm32l432xx.h"


uint16_t size = 8;



void ouput_low(){
	LTC_CS_Pin = 0;
	//pull ltc6804_cs high
}

void output_high(){
	LTC_CS_Pin = 1;
	//pull ltc6804_cs high
}

int spi_send(uint8_t command){


	uint8_t* TxBuffer;
	uint8_t* dataTbuffer = TxBuffer;
	TxBuffer = (uint8_t *) malloc((8)*sizeof(uint8_t));	//total_ic is one thus 8*total_ic = 8

	memcpy(command, TxBuffer , sizeof(command));


	HAL_StatusTypeDef errorcode;
	errorcode = HAL_SPI_Transmit(&hspi1,dataTbuffer,size,5000);	//timeout is 5 seconds(referenced from example spi code)


	if(errorcode == HAL_OK)			return 0;		//the transaction is successful

	else if(errorcode == HAL_ERROR)	return 1;		//the transaction is unsuccessful

	else if(errorcode == HAL_BUSY) 	return 2;		//the spi is busy, wait and do it again
}

int spi_receive(uint8_t command){


	uint8_t* RxBuffer;
	uint8_t* dataRbuffer = RxBuffer;
	RxBuffer = (uint8_t *) malloc((8)*sizeof(uint8_t));	//total_ic is one thus 8*total_ic = 8

	memcpy(command, RxBuffer , sizeof(command));


	HAL_StatusTypeDef errorcode;
	errorcode = HAL_SPI_Receive(&hspi1,dataRbuffer,size,5000);	//timeout is 5 seconds(referenced from example spi code)


	if(errorcode == HAL_OK)			return 0;			//the transaction is successful

	else if(errorcode == HAL_ERROR)	return 1;			//the transaction is unsuccessful

	else if(errorcode == HAL_BUSY) 	return 2;		//the spi is busy, wait and do it again

}


