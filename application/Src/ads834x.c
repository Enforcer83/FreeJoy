/**
  ******************************************************************************
  * @file           : ads834x.c
  * @brief          : ADS834x ADC driver implementation
			
		FreeJoy software for game device controllers
    Copyright (C) 2020  Yury Vostrenkov (yuvostrenkov@gmail.com)

    ADS834x ADC Driver Library
    Copyright (C) 2025 Jacob Putz, Integrated Microsystem Electronics, LLC
    (integratedmicro@proton.me)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
		
  ******************************************************************************
  */

#include "ads834x.h"

static uint8_t tmp_buf[3] = {0};

uint16_t ADS834x_GetData(sensor_t * sensor, uint8_t channel)
{

	return (sensor->data[1 + 3*channel] & 0x0F)<<8 | sensor->data[2 + 3*channel];

}

void ADS834x_StartDMA(sensor_t * sensor, uint8_t channel)
{

	sensor->rx_complete = 0;
	sensor->tx_complete = 1;
	sensor->curr_channel = channel;

	if((sensor->type == ADS8341) && (channel >= 4))
	{

		channel = channel - 4;

	}

	// CS low
	pin_config[sensor->source].port->ODR &= ~pin_config[sensor->source].pin;

	tmp_buf[0] = 0x87 | ((channel & 0x07) << 4);
	SPI_FullDuplex_TransmitReceive(&tmp_buf[0],&sensor->data[3*channel], 3, ADS834x_SPI_MODE);

}

void ADS834x_StopDMA(sensor_t * sensor)
{

	DMA_Cmd(DMA1_Channel2, DISABLE);
  
	// CS high
	pin_config[sensor->source].port->ODR |= pin_config[sensor->source].pin;
	sensor->rx_complete = 1;
	sensor->tx_complete = 1;

}
