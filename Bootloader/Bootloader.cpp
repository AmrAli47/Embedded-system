/* 
 * File:   Bootloader.cpp
 * Author: Amr Ali
 */


#include "Bootloader.h"

 const uint8_t Bootloader_version  = 0x16;

 typedef void(*ptrfunction)(void);

uint32_t sectors[32] = {
		OB_WRP_PAGES0TO3,OB_WRP_PAGES4TO7,OB_WRP_PAGES8TO11,OB_WRP_PAGES12TO15,
		OB_WRP_PAGES16TO19,OB_WRP_PAGES20TO23,OB_WRP_PAGES24TO27,OB_WRP_PAGES28TO31,
		OB_WRP_PAGES32TO35,OB_WRP_PAGES36TO39,OB_WRP_PAGES40TO43,OB_WRP_PAGES44TO47,
		OB_WRP_PAGES48TO51,OB_WRP_PAGES52TO55,OB_WRP_PAGES56TO59,OB_WRP_PAGES60TO63,
		OB_WRP_PAGES64TO67,OB_WRP_PAGES68TO71,OB_WRP_PAGES72TO75,OB_WRP_PAGES76TO79,
		OB_WRP_PAGES80TO83,OB_WRP_PAGES84TO87,OB_WRP_PAGES88TO91,OB_WRP_PAGES92TO95,
		OB_WRP_PAGES96TO99,OB_WRP_PAGES100TO103,OB_WRP_PAGES104TO107,OB_WRP_PAGES108TO111,
		OB_WRP_PAGES112TO115,OB_WRP_PAGES116TO119,OB_WRP_PAGES120TO123,OB_WRP_PAGES124TO127};

const uint8_t BL_Buffer[11] = {
		GET_COMMAND,GET_VERSION_COMMAND,GET_ID_COMMAND,READ_MEMORY_COMMAND,GO_COMMAND,
		WRITE_MEMORY_COMMAND,ERASE_COMMAND,WRITE_PROTECTION_COMMAND,WRITE_UNPROTECTION_COMMAND,
		READ_PROTECTION_COMMAND,READ_UNPROTECTION_COMMAND};

static void read_flash(uint32_t address,uint8_t len,uint8_t* data);
static void crc_8(uint8_t* data,uint8_t len,uint8_t* crc_result);

/*
 * @ Brief fetches one of the Bootloader commands
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Fetch_Host_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    const uint8_t error_message[25] = "You sent invalid command";
    uint8_t BL_Buffer[2] {};
    HAL_UART_Receive(&huart1,BL_Buffer,2,HAL_MAX_DELAY);
    switch(BL_Buffer[0])
    {
        case GET_COMMAND:
			BL_Get_Command();
			ret_val = Return_Status::HAL_OK;
			break;
        case GET_VERSION_COMMAND:
        	BL_Get_Version_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case GET_ID_COMMAND:
        	BL_Get_ID_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case READ_MEMORY_COMMAND:
        	BL_Read_Mem_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case GO_COMMAND:
        	BL_Go_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case WRITE_MEMORY_COMMAND:
        	BL_Write_Mem_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case ERASE_COMMAND:
        	BL_Erase_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case WRITE_PROTECTION_COMMAND:
        	BL_Write_Protection_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case WRITE_UNPROTECTION_COMMAND:
        	BL_Write_Unprotection_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case READ_PROTECTION_COMMAND:
        	BL_Read_Protection_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        case READ_UNPROTECTION_COMMAND:
        	BL_Read_Unprotection_Command();
        	ret_val = Return_Status::HAL_OK;
        	break;
        default : HAL_UART_Transmit(&huart1,error_message,25,HAL_MAX_DELAY);;
    }
    return ret_val;
}


/*
 * @ Brief retrieves commands and Bootloader version
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Get_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    const uint8_t Num_of_supported_commands = 0x0B;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t*)&Num_of_supported_commands,1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t*)&Bootloader_version,1,HAL_MAX_DELAY);
    for(int i=0;i<11;i++)
    {
  	  HAL_UART_Transmit(&huart1,(const uint8_t *)&(BL_Buffer[i]),1,HAL_MAX_DELAY);
    }
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    return ret_val;
}



/*
 * @ Brief retrieves Bootloader version
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Get_Version_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t*)&Bootloader_version,1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    return ret_val;
}



/*
 * @ Brief retrieves Device ID
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Get_ID_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t number_of_bytes = 2;
    uint8_t chip_id[2] = {0x4,0x10};
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(number_of_bytes),1,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t *)chip_id,2,HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    return ret_val;
}



/*
 * @ Brief reads data from memory
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Read_Mem_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t temp_Buffer[8];
    uint8_t number_of_bytes,crc_result;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,temp_Buffer,8,HAL_MAX_DELAY);
    uint32_t address =  (temp_Buffer[0] << 24) | (temp_Buffer[1] << 16) | (temp_Buffer[2] << 8) | temp_Buffer[3];
    uint32_t received_crc =  (temp_Buffer[4] << 24) | (temp_Buffer[5] << 16) | (temp_Buffer[6] << 8) | temp_Buffer[7];
    if(received_crc == HAL_CRC_Calculate(&hcrc,(uint32_t*)&address,1))
    {
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);

    	HAL_UART_Receive(&huart1,(uint8_t*)&number_of_bytes,1,HAL_MAX_DELAY);

    	uint8_t data[number_of_bytes];

    	read_flash(address,number_of_bytes,(uint8_t *)data);

    	crc_8(data,number_of_bytes,(uint8_t *)&crc_result);
    	uint8_t final_data[number_of_bytes+1];
    	for(int i=0;i<number_of_bytes;i++)
    	{
    		final_data[i] = data[i];
    	}
    	final_data[number_of_bytes] = crc_result;
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(final_data),number_of_bytes+1,HAL_MAX_DELAY);
    }
    else
    {
    	status = BL_Status::NACK;
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    }
    return ret_val;
}


/*
 * @ Brief jump to a specific address in memory
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Go_Command(void)
{
	Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t temp_Buffer[4];
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,temp_Buffer,4,HAL_MAX_DELAY);
    uint32_t base_address =  (temp_Buffer[0] << 24) | (temp_Buffer[1] << 16) | (temp_Buffer[2] << 8) | temp_Buffer[3];
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    __set_MSP(*(__IO uint32_t *) base_address);
    uint32_t jump_address = *((__IO uint32_t *)base_address+1);
    ptrfunction jump_app;
    jump_app = (ptrfunction)jump_address;
    jump_app();


    return ret_val;
}


/*
 * @ Brief writes data to memory
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Write_Mem_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t crc_result,number_of_bytes;
    uint8_t temp_Buffer[8];
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,temp_Buffer,8,HAL_MAX_DELAY);
    uint32_t address =  (temp_Buffer[0] << 24) | (temp_Buffer[1] << 16) | (temp_Buffer[2] << 8) | temp_Buffer[3];
    uint32_t received_crc =  (temp_Buffer[4] << 24) | (temp_Buffer[5] << 16) | (temp_Buffer[6] << 8) | temp_Buffer[7];
    if(received_crc == HAL_CRC_Calculate(&hcrc,(uint32_t*)&address,1))
        {
        	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
        	uint8_t bytes;
        	HAL_UART_Receive(&huart1,(uint8_t*)&number_of_bytes,1,HAL_MAX_DELAY);
        	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
        	uint8_t data[number_of_bytes] {};
        	HAL_UART_Receive(&huart1,data,number_of_bytes,HAL_MAX_DELAY);
        	bytes = (number_of_bytes-1) / 2;
        	HAL_UART_Transmit(&huart1,data,(number_of_bytes-1),HAL_MAX_DELAY);
        	crc_8(data,(number_of_bytes-1),(uint8_t *)&crc_result);

        	if(data[number_of_bytes-1] == crc_result)
        	{
        		HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
        		uint8_t k = 0,j=1;
        		uint16_t temp = 0;
        		HAL_FLASH_Unlock();
        		for(int i=0;i<bytes;i++)
        		{
        			temp = (data[k] << 8) | data[j];
        			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address,temp);
        			address += 2;
        			j+=2; k+=2;
        		}
        		HAL_FLASH_Lock();
        	}
        	else
        	{
            	status = BL_Status::NACK;
            	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
        	}

        }
        else
        {
        	status = BL_Status::NACK;
        	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
        }

    return ret_val;
}


/*
 * @ Brief erases a specified number of sectors
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Erase_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t temp_Buffer[8] {};
    uint8_t number_of_pages {};
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,temp_Buffer,8,HAL_MAX_DELAY);
    uint32_t address =  (temp_Buffer[0] << 24) | (temp_Buffer[1] << 16) | (temp_Buffer[2] << 8) | temp_Buffer[3];
    uint32_t received_crc =  (temp_Buffer[4] << 24) | (temp_Buffer[5] << 16) | (temp_Buffer[6] << 8) | temp_Buffer[7];
    if(received_crc == HAL_CRC_Calculate(&hcrc,(uint32_t*)&address,1))
    {
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    	HAL_UART_Receive(&huart1,(uint8_t *)&number_of_pages,1,HAL_MAX_DELAY);
        HAL_FLASH_Unlock();
        FLASH_EraseInitTypeDef Page_obj;
        uint32_t page_error {};
        Page_obj.Banks = FLASH_BANK_1;
        Page_obj.NbPages = number_of_pages;
        Page_obj.PageAddress = address;
        Page_obj.TypeErase = FLASH_TYPEERASE_PAGES;
        HAL_FLASHEx_Erase(&Page_obj,&page_error);
        HAL_FLASH_Lock();
    }
    else
    {
    	status = BL_Status::NACK;
    	HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    }


    return ret_val;
}


/*
 * @ Brief enables write protection for a specific sector
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Write_Protection_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t sector_number {};
    FLASH_OBProgramInitTypeDef obj_config;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,(uint8_t*)&sector_number,1,HAL_MAX_DELAY);
    --sector_number;
    obj_config.OptionType = OPTIONBYTE_WRP;
    obj_config.WRPState = OB_WRPSTATE_ENABLE;
    obj_config.WRPPage = sectors[sector_number];
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&obj_config);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_OB_Launch();
    return ret_val;
}


/*
 * @ Brief disables write protection for a specific sector
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Write_Unprotection_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    uint8_t sector_number {};
    FLASH_OBProgramInitTypeDef obj_config;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_UART_Receive(&huart1,(uint8_t*)&sector_number,1,HAL_MAX_DELAY);
    --sector_number;
    obj_config.OptionType = OPTIONBYTE_WRP;
    obj_config.WRPState = OB_WRPSTATE_DISABLE;
    obj_config.WRPPage = sectors[sector_number];
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&obj_config);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_OB_Launch();
    return ret_val;
}


/*
 * @ Brief enables read protection
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Read_Protection_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    FLASH_OBProgramInitTypeDef obj_config;
    obj_config.OptionType = OPTIONBYTE_RDP;
    obj_config.RDPLevel = OB_RDP_LEVEL_1;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&obj_config);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_OB_Launch();
    return ret_val;
}


/*
 * @ Brief Disables read protection
 * @ return function status
 * @ HAL_OK  The function completed successfully
 * @ HAL_NOK The function completed unsuccessfully
 */
Return_Status BL::BL_Read_Unprotection_Command(void)
{
    Return_Status ret_val = Return_Status::HAL_NOK;
    BL_Status status = BL_Status::ACK;
    FLASH_OBProgramInitTypeDef obj_config;
    obj_config.OptionType = OPTIONBYTE_RDP;
    obj_config.RDPLevel = OB_RDP_LEVEL_0;
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&obj_config);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    HAL_UART_Transmit(&huart1,(const uint8_t *)&(status),1,HAL_MAX_DELAY);
    HAL_FLASH_OB_Launch();
    return ret_val;
}


static void read_flash(uint32_t address,uint8_t len,uint8_t* data)
{
	for(int i=0;i<len;i++)
	{
		data[i] = *((uint8_t*)(address+i));
	}
}




static void crc_8(uint8_t* data,uint8_t len,uint8_t* crc_result)
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







