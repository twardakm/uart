/*
 */

#include <avr/io.h>

int main(void)
{

    DDRB = 0xff;
    PORTB = 0xff;

    while(1)
    ;

    return 0;
}
