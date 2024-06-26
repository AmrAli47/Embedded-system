#include "main.h"
void send_data2(uint16_t data);
void send_data1(uint16_t data);
void display_date_time(void);
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

Pin_config_t Pin_a9 = {
	.Pin_Num = Pin9,.Port_Num = Port_A,.pin_mode = Output_mode_max_speed_2_MHz,.pin_output_mode = Alternate_function_output_Push_pull
};

USART_t my_usart = {
.USART_Per = USART1,.word_length = data_length_len_8,.stop_bits_len = stop_bit_len_1,.Parity_control = disable_Parity_control,
.Tansmitter_mode = Enable_Transmitter,.Receiver_mode = Disable_Receiver,.Baud_rate_val = 9600,
.Receiving_Interrupt = Disable_Receiving_Interrupt,.Receive_data_Interrupt_Handler = NULL,.Instance = USART_1,
.Transmit_data_Interrupt_Handler = NULL
};

RTC_t my_rtc = {
.RTC_clock_source = HSE_divided_by_128_used_as_RTC_clock,.Alarm_Value = 0,.Presclaer_Value = 62500,.Alarm_Interrupt = Disable_Alarm_Interrupt,
.overflow_Interrupt = Disable_overflow_Interrupt,.seconds_Interrupt = Disable_seconds_Interrupt
};
uint16_t _year = 0;
uint8_t _month,_day,_hour,_min,_sec = 0;
int main(void)
{
	/*configure system clock*/
	RCC_osc_Config(&oscillator);
	RCC_clk_Config(&clock);
	/*configure system timer */
	configure_systick_timer(&Timer);
	/* Enable Port A Clock */
	Enable_Port_Clock(Port_A);
	/*configure pin 7 */
	GPIO_config(&Pin_a9);
	/* configure USART Module */
	USART_Init(&my_usart);
	/* configure RTC Module */
	RTC_Init(&my_rtc);
	/* set Time */
	Set_RTC(2024,6,26,11,30,10);
while(1)
{
	display_date_time();
	delay_msec(&Timer, 1000);
}
}
void send_data2(uint16_t data)
{
/*convert integer values to characters */
static int i = 0;
i++;
uint32_t temp = 0;
temp =  data / 10;
temp += 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
temp =  data % 10;
temp += 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
if(i <=4)
{
USART_Transmit_Data_Blocking(&my_usart,"-",1);
}
else
{
i = 0;
}
}
void send_data1(uint16_t data)
{
/*convert integer values to characters */
uint32_t temp = 0;
temp =  data / 1000;
temp += 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
temp = 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
data %= 100;
temp =  data / 10;
temp += 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
temp =  data % 10;
temp += 0x30;
USART_Transmit_Data_Blocking(&my_usart,(char *)&temp,1);
USART_Transmit_Data_Blocking(&my_usart,"-",1);
}

void display_date_time(void)
{
/*Read Time */
Get_RTC(&_year,&_month,&_day,&_hour,&_min,&_sec);
/* send Time over USART */
send_data1(_year);
send_data2(_month);
send_data2(_day);
send_data2(_hour);
send_data2(_min);
send_data2(_sec);
USART_Transmit_Data_Blocking(&my_usart,"\r\n",2);
}
