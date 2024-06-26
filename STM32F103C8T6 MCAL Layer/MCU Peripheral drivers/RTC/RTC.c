/* 
 * File:   RTC.c
 * Author: Amr Ali
 * @brief Real Time clock driver  
 */
#include "RTC.h"

static uint8_t month_table[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

static void (* RTC_Alarm_Interrupt_Handler)(void);
static void (* RTC_Seconds_Interrupt_Handler)(void);
static void (* RTC_overflow_Interrupt_Handler)(void);

static uint8_t check_leap_year(uint32_t year);

static uint8_t Enable_RTC_clock(void);
static uint8_t Disable_RTC_clock(void);
static uint8_t select_RTC_clock(RTC_t* _RTC);
static uint8_t Init_RTC_Interrupt(RTC_t* _RTC);
static uint8_t DeInit_RTC_Interrupt(void);
static uint8_t Set_Alarm_Value(RTC_t* _RTC);
static uint8_t Set_RTC_Prescaler_Value(RTC_t* _RTC);
static uint8_t Set_Counter_Value(uint32_t counter_Value);



/**
 *@ brief initialize RTC Module
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
uint8_t RTC_Init(RTC_t* _RTC)
{
uint8_t ret_val = E_OK;
Enable_RTC_clock();
select_RTC_clock(_RTC);
Set_RTC_Prescaler_Value(_RTC);
Init_RTC_Interrupt(_RTC);
if(Enable_Alarm_Interrupt == _RTC->Alarm_Interrupt)
{
Set_Alarm_Value(_RTC);
}
else
{
/* Nothing */
}
return ret_val;
}

/**
 *@ brief De-initialize RTC Module
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
uint8_t RTC_DeInit(RTC_t* _RTC)
{
uint8_t ret_val = E_OK;
DeInit_RTC_Interrupt();
Disable_RTC_clock();
Disable_write_access_to_BKP();
return ret_val;
}


/**
 *@ brief  Enable RTC clock source
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Enable_RTC_clock(void)
{
uint8_t ret_val = E_OK;
Enable_write_access_to_BKP();
SET_BIT(RCC->RCC_BDCR,RTC_CLK_EN_BIT_POS);
return ret_val;
}

/**
 *@ brief  Disable RTC Clock
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Disable_RTC_clock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(RCC->RCC_BDCR,RTC_CLK_EN_BIT_POS);
return ret_val;
}

/**
 *@ brief  select RTC clock source
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t select_RTC_clock(RTC_t* _RTC)
{
uint8_t ret_val = E_OK;
Enable_write_access_to_BKP();
switch(_RTC->RTC_clock_source)
{
case LSE_used_as_RTC_clock: RCC->RCC_BDCR |= ((_RTC->RTC_clock_source) << RTC_CLK_SRC_SELEC_BIT_POS); break;
case LSI_used_as_RTC_clock: RCC->RCC_BDCR |= ((_RTC->RTC_clock_source) << RTC_CLK_SRC_SELEC_BIT_POS); break;
case HSE_divided_by_128_used_as_RTC_clock: RCC->RCC_BDCR |= ((_RTC->RTC_clock_source) << RTC_CLK_SRC_SELEC_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief initialize RTC Interrupt
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Init_RTC_Interrupt(RTC_t* _RTC)
{
uint8_t ret_val = E_OK;
uint8_t temp = 0;
switch(_RTC->Alarm_Interrupt)
{
case Disable_Alarm_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp & ALARM_INT_DIS_BIT_POS);
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
break;
case Enable_Alarm_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp | (ENABLE << RTC_ALARM_INT_EN_BIT_POS));
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC_Alarm_Interrupt_Handler = _RTC->Alarm_Interrupt_callback;
break;
default : ret_val = E_NOK;
}
switch(_RTC->seconds_Interrupt)
{
case Disable_seconds_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp & SECND_INT_DIS_BIT_POS);
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
break;
case Enable_seconds_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp | (ENABLE << RTC_SECOND_INT_EN_BIT_POS));
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC_Seconds_Interrupt_Handler = _RTC->Seconds_Interrupt_callback;
break;
default : ret_val = E_NOK;
}
switch(_RTC->overflow_Interrupt)
{
case Disable_overflow_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp & OVERFL_INT_DIS_BIT_POS);
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
break;
case Enable_overflow_Interrupt:
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
temp = RTC->RTC_CRH;
RTC->RTC_CRH = (temp | (ENABLE << RTC_OVFL_INT_EN_BIT_POS));
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC_overflow_Interrupt_Handler = _RTC->Alarm_Interrupt_callback;
break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief De-initialize RTC Interrupt
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t DeInit_RTC_Interrupt(void)
{
uint8_t ret_val = E_OK;
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
RTC->RTC_CRH = 0x0;
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
return ret_val;
}

/**
 *@ brief Set Alarm value
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Set_Alarm_Value(RTC_t* _RTC)
{
uint8_t ret_val = E_OK;
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
RTC->RTC_ALRL = (LOW_ALARM_REG_MSK & (_RTC->Alarm_Value));
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC->RTC_ALRH = (HIGH_ALARM_REG_MSK & (_RTC->Alarm_Value));
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
return ret_val;
}

/**
 *@ brief Set Prescaler value
 *@ param  Pointer to RTC Configuration @ref RTC_t
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Set_RTC_Prescaler_Value(RTC_t* _RTC)
{

uint8_t ret_val = E_OK;
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
RTC->RTC_PRLL = (LOW_PRESCA_REG_MSK & (_RTC->Presclaer_Value));
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC->RTC_PRLH = (HIGH_PRESCA_REG_MSK & (_RTC->Presclaer_Value));
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
return ret_val;
}

/**
 *@ brief Set RTC Timer
 *@ param  date and time values
 *@ return function status
 *@ E_OK   function was completed successfully
 *@ E_NOK  function was completed unsuccessfully
 * */
uint8_t Set_RTC(uint16_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t minute,uint8_t second)
{
uint8_t ret_val = E_OK;
uint32_t counts,i = 0;
counts = 0;
if(year < 2000)
{
year = 2000;
}
else if(year > 2099)
{
year = 2099;
}
else
{
/* Nothing */
}
for(i = 2000;i < year; i++)
{
if(LEAP_YEAR == check_leap_year(i))
{
counts += 31622400;
}
else if(NOT_LEAP_YEAR == check_leap_year(i))
{
counts += 31536000;
}
else
{
/* Nothing */
}
}
--month;
if((LEAP_YEAR == check_leap_year(year)) && (month > 2))
{
counts += 86400;
}
for(i=0;i<month;i++)
{
counts += (month_table[i] * 86400);
}
counts += ((date - 1) * 86400);
counts += (hour * 3600);
counts += (minute * 60);
counts += second;
Set_Counter_Value(counts);
return ret_val;
}

/**
 *@ brief set counter value
 *@ param counter value
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
static uint8_t Set_Counter_Value(uint32_t counter_Value)
{
uint8_t ret_val = E_OK;
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
/* Enter Configuration Mode */
SET_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
RTC->RTC_CNTL = (LOW_COUNT_REG_MSK & (counter_Value));
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
RTC->RTC_CNTH = ((HIGH_COUNT_REG_MSK & (counter_Value)) >> 16);
/* Exit Configuration Mode */
CLEAR_BIT(RTC->RTC_CRL,RTC_ENTER_CONFIG_MOD_BIT_POS);
while(!(RTC->RTC_CRL,RTC_OPERATION_OFF_BIT_POS));
return ret_val;
}

/**
 *@ brief Get Timer
 *@ param pointer to date and time
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Get_RTC(uint16_t* year,uint8_t* month,uint8_t* date,uint8_t* hour,uint8_t* minute,uint8_t* second)
{
uint8_t ret_val = E_OK;
static uint32_t day_cout = 0;
uint32_t counts,temp,temp1 = 0;
counts = (((RTC->RTC_CNTH) << 16) | (RTC->RTC_CNTL ));
temp = counts / 86400;
if(day_cout != temp)
{
day_cout = temp;
temp1 = 2000;
/* calculate number of years */
while(temp >= 365)
{
if(1 == check_leap_year(temp1))
{
if(temp > 366)
{
temp -= 366;
}
else
{
break;
}
}
else
{
temp -= 365;
}
temp1++;
}
*year = temp1;
temp1 = 0;
/*count months, 28 because shortest month days is 28*/
while(temp > 28)
{
if((temp1 == 1) && (check_leap_year(*year) == 1))
{
if(temp > 29)
{
temp -= 29;
}
else
{
break;
}
}
else
{
if(temp > month_table[temp1])
{
temp -= month_table[temp1];
}
else
{
break;
}
}
temp1++;
}
*month = temp1 + 1;
*date  = temp + 1;
}
temp = counts % 86400;
*hour =  temp / 3600;
*minute = (temp % 3600) / 60;
*second = (temp % 3600) % 60;
return ret_val;
}

static uint8_t check_leap_year(uint32_t year)
{
if(((year%4 == 0) && (year % 100 != 0)) || ((year % 400 == 0)))
{
return 1;
}
else
{
return 0;
}
}
/*RTC IRQ Handler*/
void RTC_IRQHandler(void)
{
if((READ_BIT(RTC->RTC_CRH,RTC_SECOND_INT_EN_BIT_POS) && (READ_BIT(RTC->RTC_CRL,SECOND_FLAG_BIT_POS))))
{
CLEAR_BIT(RTC->RTC_CRL,SECOND_FLAG_BIT_POS);
if(RTC_Seconds_Interrupt_Handler)
{
RTC_Seconds_Interrupt_Handler();
}
else{/* Nothing */}
}
else{/* Nothing */}
if((READ_BIT(RTC->RTC_CRH,RTC_OVFL_INT_EN_BIT_POS)) && (READ_BIT(RTC->RTC_CRL,OVERFLOW_FLAG_BIT_POS)))
{
CLEAR_BIT(RTC->RTC_CRL,OVERFLOW_FLAG_BIT_POS);
if(RTC_overflow_Interrupt_Handler)
{
RTC_overflow_Interrupt_Handler();
}
else{/* Nothing */}
}
else{/* Nothing */}
}

/* RTC Alarm Interrupt Handler */
void RTCAlarm_IRQHandler(void)
{
if((READ_BIT(RTC->RTC_CRH,RTC_ALARM_INT_EN_BIT_POS) && (READ_BIT(RTC->RTC_CRL,ALARM_FLAG_BIT_POS))))
{
CLEAR_BIT(RTC->RTC_CRL,ALARM_FLAG_BIT_POS);
if(RTC_Alarm_Interrupt_Handler)
{
RTC_Alarm_Interrupt_Handler();
}
else{/* Nothing */}
}
else{/* Nothing */}
}
