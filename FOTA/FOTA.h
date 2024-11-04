/*
 * FOTA.h
 * Author: Amr Ali
 */

#ifndef INC_FOTA_H_
#define INC_FOTA_H_

/*----------------------Includes--------------------*/
#include "usart.h"
#include "gpio.h"
#include "crc.h"
#include <machine/_default_types.h>
#include "math.h"


/*----------------------Macros--------------------*/
#define WRITE_JUMP_AND           0x22


/*----------------------User defined datatypes--------------------*/
enum class FOTA_Status : uint8_t {
	 	 NACK = 0x1F,
	 	 ACK = 0x79
	};

enum class FOTA_Return_Status : uint8_t {
	    HAL_NOK = 0,
	    HAL_OK = 1
	};


class FOTA {
    public:
	FOTA() = default;
	~FOTA() = default;
	void Fetch_Command();
	void write_and_jump();
	void crc_8(uint8_t* data,uint16_t len,uint8_t* crc_result);
};


#endif /* INC_FOTA_H_ */
