
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
	configure_systick_timer(&Timer);
  	while(1)
	{
  		Get_Elapsed_Ticks(&ticks);
	}
}

void sys_handler_callback(void)
{
i++;
}
