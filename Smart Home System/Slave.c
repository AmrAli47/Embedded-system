
#include "mcc_generated_files/mcc.h"

uint8_t Receiving_Value = 0;

static void Handler() {
    Receiving_Value = SSPBUF;
}

void main(void)
{
    
    SYSTEM_Initialize();



    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    I2C_Open();
    I2C_SlaveSetReadIntHandler(Handler);
    while (1)
    {
        if(Receiving_Value > 30)
        {
        M11_SetHigh();
        M22_SetLow();
        }
        else
        {
        M11_SetLow();
        M22_SetLow();    
        }
    }
}
