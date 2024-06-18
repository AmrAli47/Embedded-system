#include "main.h"


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


Pin_config_t pin_a7 = {
	.Port_Num = Port_A,.Pin_Num = Pin7,.pin_mode = Output_mode_max_speed_2_MHz,.pin_output_mode = General_purpose_output_push_pull
};
Pin_config_t pin_a4 = {
	.Port_Num = Port_A,.Pin_Num = Pin4,.pin_mode = Input_mode,.pin_input_mode = Input_with_pull_up_pull_down
};

Ext_Int_Event_Config_t ext_int = {
	.Request_Number = Ext_Int_EV_4,.Edge = Rising_Edge,.Request_type = External_Interurpt
};
int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	/* configure system timer */
	configure_systick_timer(&Timer);
	/* Enable EXTI4 IRQ */
	NVIC_Enabel_IRQ(EXTI4_Interrupt_IRQ);
	/* Enable Port A & Port C Clock */
	Enable_Port_Clock(Port_A);
	/* Enable External Interrupt Clock */
	/* Configure Pins */
	Enable_EXT_INT_Clock();
	GPIO_config(&pin_a7);
	GPIO_config(&pin_a4);
	/* configure external interrupt */
	EXT_Req_config(&ext_int);
	/* Enter stop mode (Nothing will be executed after entering stop mode and will wait for interrupt to leave stop mode and
	 * execute our code again) */
	Enter_stop_mode(wait_for_interrupt,voltage_regulator_normal_mode);
	/* after exiting from stop mode -> HSI will be system clock
	 * so i reconfigure system clock again */
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	while(1)
	{
		Toggle_Pin(Port_A,Pin7);
		delay_msec(&Timer,1000);

	}
}
void EXTI4_IRQHandler(void)
{
	Clear_Pending_Bit(Ext_Int_EV_3);
}
