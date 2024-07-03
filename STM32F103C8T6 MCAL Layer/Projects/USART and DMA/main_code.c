#include "main.h"
void TR_COMP(void);
char arr[12];
int i = 0;
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

systick_t Timer =
{
.reload_value = 8999999,
.timer_clock = external_clock,
.timer_mode = single_mode,
.timer_exception = Disbale,
.ptr_function = NULL
};

Pin_config_t Pin_a7 = {
	.Pin_Num = Pin7,.Port_Num = Port_A,.pin_mode = Output_mode_max_speed_2_MHz,.pin_output_mode = General_purpose_output_push_pull
};

Pin_config_t Pin_a9 = {
	.Pin_Num = Pin9,.Port_Num = Port_A,.pin_mode = Output_mode_max_speed_2_MHz,.pin_output_mode = Alternate_function_output_Push_pull
};

Pin_config_t Pin_a10 = {
	.Pin_Num = Pin10,.Port_Num = Port_A,.pin_mode = Input_mode,.pin_input_mode = Input_with_pull_up_pull_down
};

DMA_t dma1 = {
.channel = channel_5,.transfer_type = Memory_to_memory_mode_disabled,.priority = Very_high,.direction = Read_from_peripheral,
.Memory_Size = one_Byte,.Peripheral_Size = one_Byte,.mode = Normal_Mode,
.Memory_increment_mode = Memory_increment_mode_enabled,.Complete_Transfer_interrupt = complete_Transfer_interrupt_Disable,
.Complete_Transfer_callback = NULL,.Half_Transfer_interrupt = Half_Transfer_interrupt_Disable,
.Error_interrupt = Transfer_error_interrupt_Disable
};

DMA_t dma2 = {
.channel = channel_4,.transfer_type = Memory_to_memory_mode_disabled,.priority = Very_high,.direction = Read_from_memory,
.Memory_Size = one_Byte,.Peripheral_Size = one_Byte,.mode = Normal_Mode,
.Memory_increment_mode = Memory_increment_mode_enabled,.Complete_Transfer_interrupt = complete_Transfer_interrupt_Enable,
.Complete_Transfer_callback = TR_COMP,.Half_Transfer_interrupt = Half_Transfer_interrupt_Enable,
.Error_interrupt = Transfer_error_interrupt_Enable
};

USART_t usart = {
.USART_Per = USART1,.word_length = data_length_len_8,.stop_bits_len = stop_bit_len_1,.Parity_control = disable_Parity_control,
.Tansmitter_mode = Enable_Transmitter,.Receiver_mode = Enable_Receiver,.Baud_rate_val = 9600,.Error_interrupt = Error_interrupt_Enable,
.Receive_data_Interrupt_Handler = NULL,.Instance = USART_1,.Receiver_DMA = Enable_DMA_Receiver,.Transmitter_DMA = Enable_DMA_Transmitter,
.Transmit_data_Interrupt_Handler = NULL
};

int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	/* Enable Interrupt IRQ */
	NVIC_Enabel_IRQ(DMA1_Channel5_Interrupt_IRQ);
	NVIC_Enabel_IRQ(DMA1_Channel4_Interrupt_IRQ);
	/*configure system timer */
	configure_systick_timer(&Timer);
	/* Enable Port A Clock */
	Enable_Port_Clock(Port_A);
	/*configure pins */
	GPIO_config(&Pin_a7);
	GPIO_config(&Pin_a9);
	GPIO_config(&Pin_a10);
	/* configure USART Module */
	USART_Init(&usart);
	/* Receive data via USART in DMA mode*/
	USART_Receive_Data_DMA(&usart,&dma1,arr,11);

while(1)
{
	if(!(strncmp("Turn LED ON",arr,11)))
	{
		Write_Pin(Port_A,Pin7,Pin_Set);
		memset(arr,'\0',12);
		delay_msec(&Timer, 100);
		USART_Transmit_Data_DMA(&usart,&dma2,"\r\nLED is ON\r\n",13);
	}
	else if(!(strncmp("Turn LED OFF",arr,12)))
	{
		Write_Pin(Port_A,Pin7,Pin_Reset);
		memset(arr,'\0',12);
		delay_msec(&Timer, 100);
		USART_Transmit_Data_DMA(&usart,&dma2,"\r\nLED is OFF\r\n",14);
	}
}
}

void TR_COMP(void)
{
	if(i == 0)
	{
		USART_Receive_Data_DMA(&usart,&dma1,arr,12);
		i = 1;
	}
	else if(i == 1)
	{
		USART_Receive_Data_DMA(&usart,&dma1,arr,11);
		i = 0;
	}
}
