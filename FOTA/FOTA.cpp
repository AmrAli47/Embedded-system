/*
 * FOTA.cpp
 * Author: Amr Ali
 */


#include "FOTA.h"

typedef void (*ptr_function)(void);

/*
 * @ Brief fetches one of the Bootloader commands
 */

void FOTA::Fetch_Command()
{
	uint8_t command {};
	HAL_UART_Receive(&huart1,(uint8_t*)&command,1,HAL_MAX_DELAY);

if (command == WRITE_JUMP_AND)
{
	FOTA::write_and_jump();
}
else
{
	/*Nothing*/
}
}


/**
 * @brief Writes data to a specific memory location and jumps to that location.
 *
 * This function receives a starting address and data over UART, verifies the
 * integrity of the received data using CRC, writes the data to flash memory,
 * and then transfers control to the new application at the specified address.
 *
 * @note The function handles CRC verification, UART data reception, and flash
 *       memory programming. It also sets the main stack pointer to the new application.
 */
void FOTA::write_and_jump()
{
	uint8_t temp_Buffer[8] {};
	FOTA_Status status = FOTA_Status::ACK;
	uint8_t crc_result {};
	uint8_t length_of_list {};
	uint16_t number_of_bytes {};
    HAL_UART_Receive(&huart1,temp_Buffer,8,HAL_MAX_DELAY);
    uint32_t address =  (temp_Buffer[0] << 24) | (temp_Buffer[1] << 16) | (temp_Buffer[2] << 8) | temp_Buffer[3];
    uint32_t received_crc =  (temp_Buffer[4] << 24) | (temp_Buffer[5] << 16) | (temp_Buffer[6] << 8) | temp_Buffer[7];
    if(received_crc == HAL_CRC_Calculate(&hcrc,(uint32_t*)&address,1))
    {
    	HAL_UART_Receive(&huart1,(uint8_t *)&length_of_list,1,HAL_MAX_DELAY);
    	uint8_t number_of_bytes_arr[length_of_list] {};
    	HAL_UART_Receive(&huart1,number_of_bytes_arr,length_of_list,HAL_MAX_DELAY);


    	for(uint8_t i = 0; i < length_of_list; i++)
    	{
    		number_of_bytes= number_of_bytes*10 + number_of_bytes_arr[i];
    	}
    	uint8_t data_bytes[number_of_bytes] {};
    	HAL_UART_Receive(&huart1,data_bytes,number_of_bytes,HAL_MAX_DELAY);
    	uint16_t bytes = (number_of_bytes-1) / 2;
    	crc_8(data_bytes,(number_of_bytes-1),&crc_result);
    	if(crc_result == data_bytes[number_of_bytes-1])
    	{
    		HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    		uint32_t temp_address = address;
    		uint16_t k = 0,j=1;
    		uint16_t temp = 0;
    	    HAL_FLASH_Unlock();
    	    for(uint16_t i=0; i < bytes ; i++ )
    	    {
    			temp = (data_bytes[j] << 8) | data_bytes[k];
    			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,temp_address,temp);
    			temp_address += 2;
    			j+=2; k+=2;
    	    }
    	    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    	    HAL_FLASH_Lock();

    	    __set_MSP(*(__IO uint32_t *) address);
    	    uint32_t jump_address = *((__IO uint32_t *)address+1);
    	    ptr_function jump_app;
    	    jump_app = (ptr_function)jump_address;
    	    jump_app();
    	}
    	else
    	{
        	status = FOTA_Status::NACK;
        	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    	}

    }
    else
    {
    	status = FOTA_Status::NACK;
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    }
}



/*
 * @ Brief calculates 8 Bit CRC
 * @ param : pointer to starting address of data buffer on which to calculate the crc
 * @ param : number of data bytes to include in the CRC calculation.
 * @ param : pointer to buffer where the calculated crc will be stored
 */
void FOTA::crc_8(uint8_t* data,uint16_t len,uint8_t* crc_result)
{
	uint8_t Poly = 0x4C, initial_value = 0xFF;
	*crc_result = initial_value;
	for(int i=0;i<len;i++)
	{
		*crc_result ^= data[i];
		for(int j=0;j<8;j++)
		{
			if(*crc_result & 0x80)
			{
				*crc_result = ((*crc_result) << 1) ^ Poly;
			}
			else
			{
				*crc_result <<= 1;
			}
		}
	}
}







