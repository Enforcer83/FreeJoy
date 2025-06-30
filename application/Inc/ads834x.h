/**
  ******************************************************************************
  * @file           : ads834x.h
  * @brief          : Header for ads834x.c file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS834x_H__
#define __ADS834x_H__

#include "common_types.h"
#include "periphery.h"

#define ADS834x_SPI_MODE						1

uint16_t ADS834x_GetData(sensor_t * sensor, uint8_t channel);
void ADS834x_StartDMA(sensor_t * sensor, uint8_t channel);
void ADS834x_StopDMA(sensor_t * sensor);

#endif 	/* __ADS834x_H__ */