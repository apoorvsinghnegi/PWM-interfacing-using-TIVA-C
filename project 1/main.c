/* Generates 50HZ and variable duty cycle on PF2 pin*/
/* PWM1 module and PWM generator 3 of PWM1 module is used*/
#include "TM4C123GH6PM.h"
#include "delay.h"

int main(void)
{

  int duty_cycle = 4999;
    
/* Clock setting for PWM and GPIO PORT */
SYSCTL->RCGCPWM |= 2;         /* To enable Clock in PWM1 Module*/
SYSCTL->RCGCGPIO |= 0x20;    /* Enable system clock to PORTF as all LEDs are connected to PORTF*/
SYSCTL->RCC |= (1<<20);     /* Enable System Clock Divisor function for PWM modules */
SYSCTL->RCC |= 0x000E0000; /* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/

 /* Setting of PF2 pin for M1PWM6 channel output pin */
GPIOF->AFSEL |= (1<<2);  /* PF2 sets a alternate function as blue LED is connected to PF2 */
GPIOF->PCTL &= ~0x00000F00; /*set PF2 as output pin */
GPIOF->PCTL |= 0x00000500; /* make PF2 PWM output pin */
GPIOF->DEN |= (1<<2);      /* set PF2 as a digital pin as we want to glow LED  */
    
PWM1->_3_CTL &= ~(1<<0);   /* Disable Generator 3 counter */
PWM1->_3_CTL &= ~(1<<1);   /* select down count mode of counter 3*/
PWM1->_3_GENA = 0x0000008C;  /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
PWM1->_3_LOAD = 5000;     /* set load value for 50Hz 16MHz/65 = 250kHz and (250KHz/5000) */
PWM1->_3_CMPA = 4999;     /* set duty cyle to to minumum value*/
PWM1->_3_CTL = 1;           /* Enable Generator 3 counter */
PWM1->ENABLE = 0x40;      /* Enable PWM1 channel 6 output */
    
    while(1)
    {
        duty_cycle = duty_cycle - 10;
        if (duty_cycle <= 0) 
	   duty_cycle = 5000;
        PWM1->_3_CMPA = duty_cycle;
        delay(100000);
    }
}


