#include "main.h"
char arr[3];
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

USART_t my_usart = {
.USART_Per = USART1,.word_length = data_length_len_8,.stop_bits_len = stop_bit_len_1,.Parity_control = disable_Parity_control,
.Tansmitter_mode = Enable_Transmitter,.Receiver_mode = Enable_Receiver,.Baud_rate_val = 9600,.Error_interrupt = Error_interrupt_Enable,
.Receive_data_Interrupt_Handler = NULL,.Instance = USART_1,
.Transmit_data_Interrupt_Handler = NULL
};

int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	/*configure system timer */
	NVIC_Enabel_IRQ(USART1_Interrupt_IRQ);
	configure_systick_timer(&Timer);
	/* Enable Port A Clock */
	Enable_Port_Clock(Port_A);
	/*configure pins */
	GPIO_config(&Pin_a7);
	GPIO_config(&Pin_a9);
	GPIO_config(&Pin_a10);
	/* configure USART Module */
	USART_Init(&my_usart);
	/* Receive data via USART using interrupt */
	USART_Receive_Data_Interrupt(&my_usart,arr,2);
while(1)
{
if(!(strncmp("ON",arr,2)))
{
	Write_Pin(Port_A,Pin7,Pin_Set);
	memset(arr,'\0',3);
	USART_Transmit_Data_Interrupt(&my_usart,"\r\nLED is ON\r\n",13);
	delay_msec(&Timer,50);
	USART_Receive_Data_Interrupt(&my_usart,arr,3);
}
else if(!(strncmp("OFF",arr,3)))
{
	Write_Pin(Port_A,Pin7,Pin_Reset);
	memset(arr,'\0',3);
	USART_Transmit_Data_Interrupt(&my_usart,"\r\nLED is OFF\r\n",13);
	delay_msec(&Timer,50);
	USART_Receive_Data_Interrupt(&my_usart,arr,2);
}
else
{
}
}
}

