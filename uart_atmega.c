#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_atmega.h"

void USART_Init(unsigned int ubrr) /*Jako ubrr wchodzi MYUBRR, który jest podany w nocie*/
{
    /* Set baud rate */
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSRB = (1<<RXEN)|(1<<TXEN)|(1 << RXCIE ); //włączenie przerwania
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);


}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) )
        ;
    /* Put data into buffer, sends the data */
    UDR = data;
}

unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) )
        ;
    /* Get and return received data from buffer */
    return UDR;
}

//Przerwanie na RXC
ISR ( USART_RXC_vect )
{
    char ReceivedByte;
    ReceivedByte = USART_Receive(); // Fetch the received byte value into the variable " ByteReceived "
    diody(ReceivedByte);
}

void diody(char bajt)
{
    if (bajt == 'x')
        PORTB ^= 0x01;
    else
        PORTB ^= 0x03;
}

