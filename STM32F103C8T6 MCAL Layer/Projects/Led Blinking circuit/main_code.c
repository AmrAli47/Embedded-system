
#include <stdint.h>
#include "main.h"

void sys_handler_callback(void);
int i = 0;
uint32_t ticks;
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

Pin_config_t pin_one =
{
.Port_Num = Port_C,.Pin_Num = Pin13,.pin_mode = Output_mode_max_speed_2_MHz,.pin_output_mode = General_purpose_output_Open_drain,
};

Pin_config_t pin_two =
{
.Port_Num = Port_A,.Pin_Num = Pin3,.pin_mode = Output_mode_max_speed_2_MHz,.pin_input_mode = General_purpose_output_Open_drain,
};

systick_t Timer =
{
.reload_value = 8999999,
.timer_clock = external_clock,
.timer_mode = periodic_mode,
.timer_exception = Enable,
.ptr_function = sys_handler_callback
};


int main(void)
{
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	NVIC_Enabel_IRQ(SysTick_Interrupt_IRQ);
	Enable_Port_Clock(Port_A);
	Enable_Port_Clock(Port_C);
	GPIO_config(&pin_one);
	GPIO_config(&pin_two);
	configure_systick_timer(&Timer);
	while(1)
	{

	}
}


void sys_handler_callback(void)
{
	Toggle_Pin(Port_C,Pin13);
	Toggle_Pin(Port_A,Pin3);
}
