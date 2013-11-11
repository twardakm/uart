/*
 */
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart_atmega.h"

int main(void)
{
    DDRB |= 0x03;
    PORTB = 0;

    USART_Init(MYUBRR);

    sei();

    while(1)
    {
    }

    return 0;
}
