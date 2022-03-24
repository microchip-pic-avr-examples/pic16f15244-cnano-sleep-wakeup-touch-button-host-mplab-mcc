/*
 * File:   application.c
 * Author: I62418
 *
 * Created on September 28, 2021, 10:50 AM
 */

#include "mcc_generated_files/mcc.h"
#include "application.h"

bool setInterruptFlag = false;
unsigned char userInput;

void Application(void)
{
    EUSART2_Write(ONE_HOUR);                                                 // Sends the time for periodic reset
    if(EUSART2_is_tx_done())                                                 // Confirm if the transmission is completed
    {
        SLEEP();
    }
    if(setInterruptFlag == true)                                             // Check if interrupt is received
    {
        printf("\n\t Wake-up Signal Received");
        __delay_ms(HOLD_TIME);
        LED_SetLow();                                                        // Visual notification of interrupt received
        __delay_ms(HOLD_TIME);
        LED_SetHigh();
        setInterruptFlag = false;
        SLEEP();
    }
}

void External_Interrupt(void)
{
    setInterruptFlag = true;                                                 // To call up the clear register value function
                                                                             // Visual indicator
}
