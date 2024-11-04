/* 
 * File:   Bootloader.h
 * Author: Amr Ali
 */

#ifndef _BOOT_LOADER_H_
#define _BOOT_LOADER_H_

/*----------------------Includes--------------------*/
#include "usart.h"
#include "gpio.h"
#include "crc.h"
#include <machine/_default_types.h>
#include "math.h"


/*----------------------Macros--------------------*/                
#define GET_COMMAND                 0x00
#define GET_VERSION_COMMAND         0x01
#define GET_ID_COMMAND              0x02
#define READ_MEMORY_COMMAND         0x11
#define GO_COMMAND                  0x21
#define WRITE_MEMORY_COMMAND        0x31
#define ERASE_COMMAND               0x43
#define WRITE_PROTECTION_COMMAND    0X63
#define WRITE_UNPROTECTION_COMMAND  0x73
#define READ_PROTECTION_COMMAND     0x82
#define READ_UNPROTECTION_COMMAND   0x92
#define CHIP_ID_FIRST_BYTE          0x04
#define CHIP_ID_SECOND_BYTE         0x10

#define NO_OF_COMMANDS              11

/*----------------------User defined datatypes--------------------*/
enum class BL_Status : uint8_t {
	 	 NACK = 0x1F,
	 	 ACK = 0x79
	};

enum class Return_Status : uint8_t {
	    HAL_NOK = 0,
	    HAL_OK = 1
	};


class BL {
    private:

    public:
	BL() = default;
	~BL() = default;
    Return_Status BL_Fetch_Host_Command(void);
    Return_Status BL_Get_Command(void);
    Return_Status BL_Get_Version_Command(void);
    Return_Status BL_Get_ID_Command(void);
    Return_Status BL_Read_Mem_Command(void);
    Return_Status BL_Go_Command(void);
    Return_Status BL_Write_Mem_Command(void);
    Return_Status BL_Erase_Command(void);
    Return_Status BL_Write_Protection_Command(void);
    Return_Status BL_Write_Unprotection_Command(void);
    Return_Status BL_Read_Protection_Command(void);
    Return_Status BL_Read_Unprotection_Command(void);
    Return_Status read_data_from_memory(uint8_t* pBuffer, uint8_t BufferLength,uint32_t address);

};


typedef struct
{
volatile uint32_t FLASH_ACR;
volatile uint32_t FLASH_KEYR;
volatile uint32_t FLASH_OPTKEYR;
volatile uint32_t FLASH_SR;
volatile uint32_t FLASH_CR;
volatile uint32_t FLASH_AR;
volatile uint32_t FLASH_OBR;
volatile uint32_t FLASH_WRPR;
}FLASH_T;

#endif /* _BOOT_LOADER_H_ */
