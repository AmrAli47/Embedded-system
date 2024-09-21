
#include "main.h"
RCC_OSC_Init_t oscillator = {
.oscillator_type = High_Speed_External_Oscillator,
.Ext_OSC = High_Speed_External_Oscillator_Not_bypassed,
.PLL.PLL_State = PLL_ENABLE,
.PLL.PLL_Source = PLL_HSE_oscillator,
.PLL.HSE_Pri_dev_fc = Pre_Div_1,
.PLL.PLL_mul_factor = PLL_MUL_9,
};

RCC_CLK_Init_t clock = {
.clock_type = PLL_Selected_as_system_clock,
.AHB_Prescaler = AHB_Prescaler_DIV_BY_1,
.APB1_Prescaler = APB_Prescaler_DIV_BY_2,
.APB2_Prescaler = APB_Prescaler_DIV_BY_1
};


DMA_t dma = {
.channel = channel_6,.priority = Very_high,.direction = Read_from_memory,
.Error_interrupt = Transfer_error_interrupt_Disable,.Half_Transfer_interrupt = Half_Transfer_interrupt_Disable,
.Complete_Transfer_interrupt = complete_Transfer_interrupt_Disable,.Error_Transfer_callback = NULL,
.Half_Transfer_callback = NULL,.Complete_Transfer_callback = NULL,
.transfer_type = Memory_to_memory_mode_enabled,.direction = Read_from_memory,.Memory_Size = one_Byte,
.number_of_data_to_trasfer = 11,.Memory_increment_mode = Memory_increment_mode_enabled,
.Peripheral_increment_mode = Peripheral_increment_mode_enabled
};

uint8_t source[11] = "Hello World";
uint8_t dest[11];
int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	/* configure DMA*/
	DMA_Init(&dma);
	/* set start address where DMA will read from*/
	Set_source_aaddress(&dma,(uint32_t)source);
	/* set start address where DMA will write to*/
	Set_destination_aaddress(&dma,(uint32_t)dest);
	/* Enable DMA Channel */
	start_DMA(&dma);
while(1)
{


}
}

