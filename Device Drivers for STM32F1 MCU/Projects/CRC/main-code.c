#include "main.h"
uint8_t CRC_32(uint32_t* pdata,uint8_t len,uint32_t* crc_result);

RCC_OSC_Init_t oscillator = {
.oscillator_type = High_Speed_External_Oscillator,
.Ext_OSC = High_Speed_External_Oscillator_Not_bypassed,
.PLL.PLL_State = PLL_ENABLE,
.PLL.PLL_Source = PLL_HSE_oscillator,
.PLL.HSE_Pri_dev_fc = Pre_Div_1,
.PLL.PLL_mul_factor = PLL_MUL_9,
.Ext_OSC_VAL = 8000000
};

RCC_CLK_Init_t clock = {
.clock_type = PLL_Selected_as_system_clock,
.AHB_Prescaler = AHB_Prescaler_DIV_BY_1,
.APB1_Prescaler = APB_Prescaler_DIV_BY_2,
.APB2_Prescaler = APB_Prescaler_DIV_BY_1
};

uint32_t data[4] = {0xC5,0x8E,0xB4,0xA1};
uint32_t initial_value = 0XFFFFFFFF;
uint32_t POLY = 0x4C11DB7;
uint32_t crc_result1,crc_result2 = 0;
uint8_t i,j = 0;
int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);

	/* Implement CRC using CRC Peripheral */
	CRC_Calculate(data,4,&crc_result1);

	/* Implement CRC using software code*/
	CRC_32(data,4,&crc_result2);
}
uint8_t CRC_32(uint32_t* pdata,uint8_t len,uint32_t* crc_result)
{

	for(i=0;i<len;i++)
	{
		if(i == 0)
		{
			*crc_result = pdata[i] ^ initial_value;
		}
		else
		{
			*crc_result = pdata[i] ^ (*crc_result);
		}
		for(j=0;j<=31;j++)
		{
			if(READ_BIT(*crc_result,31))
			{
				*crc_result = ((*crc_result << 1) ^ POLY) ;
			}
			else
			{
				*crc_result = (*crc_result << 1) ;
			}
		}
	}

}
