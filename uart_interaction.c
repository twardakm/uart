#include <stdio.h>
#include <stdlib.h>

#include "uart_interaction.h"
#include "uart_config.h"

void welcomeMessage()
{
    printf("\nUART\nCOMMUNICATION\n----------------------------\n\n");
}

void getData(port *myPort)
{
    int i;

    myPort->serialName = malloc(sizeof(char) * 10);
    printf("Port name (ex: /dev/ttyUSB0): ");
    scanf("%s", myPort->serialName);
    printf("Choose baudrate (default: 9600)\n"
        "1 - 4800\n"
        "2 - 9600\n"
        "3 - 19200\n"
        "4 - 38400\n");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            myPort->baudrate = B4800;
            break;
        case 2:
            myPort->baudrate = B9600;
            break;
        case 3:
            myPort->baudrate = B19200;
            break;
        case 4:
            myPort->baudrate = B38400;
            break;
        default:
            myPort->baudrate = B4800;
            break;
    }
    printf("Choose stopbits (default: 2)\n1 - 1\n2 - 2\n");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            myPort->stopBit = 1;
            break;
        case 2:
            myPort->stopBit = 2;
            break;
        default:
            myPort->stopBit = 1;
            break;
    }

    printf("SUMMARY\n"
        "Name: %s"
        "Baudrate: %d\n"
        "Stop bits: %d\n"
        "No parity\n",
        myPort->serialName, myPort->baudrate, myPort->stopBit);
    return;
}
