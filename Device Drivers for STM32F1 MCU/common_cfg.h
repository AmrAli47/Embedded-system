/* 
 * File:   common_cfg.h
 * Author: Amr Ali
 * @brief common configuration 
 */
 
#ifndef _COMMON_CFG_H
#define _COMMON_CFG_H
/*************macro declarations****************/
#define SET_BIT(REG,BIT_POS)    (REG |= (0X01) << BIT_POS)
#define CLEAR_BIT(REG,BIT_POS)  (REG &= ~(0X01) << BIT_POS)
#define READ_BIT(REG,BIT_POS)	((REG >> BIT_POS) & ((uint32_t)0x01))
#define READ_REG(REG)			(REG)




/*************user defined data types****************/
typedef enum
{
E_NOK,
E_OK
}STD_Return_t;


#endif



