/*
 */
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart_atmega.h"

int main(void)
{
    DDRB |= 0x03;
    PORTB |= 0x03;

    USART_Init(MYUBRR);
    unsigned char temp;
    while(1)
    {
        USART_Transmit(1);
        PORTB ^= 0x01;
        _delay_ms(1000);
        if (RXC)
        {
            temp = USART_Receive();
            if (temp == 1)
                PORTB ^= 0x02;
        }
        _delay_ms(1000);
    }

    return 0;
}
