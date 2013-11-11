#ifndef UART_ATMEGA_H_INCLUDED
#define UART_ATMEGA_H_INCLUDED

/*str 159 datasheet AtMega*/
#define MYUBRR 12
#include <avr/interrupt.h>

/*Funkcje z datasheet*/
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
ISR ( USART_RXC_vect );
void diody(char bajt);

#endif // UART_ATMEGA_H_INCLUDED
