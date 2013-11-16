#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LENGHT 10

#include "uart_interaction.h"
#include "uart_config.h"

void welcomeMessage()
{
    printf("\nUART\nCOMMUNICATION\n----------------------------\n\n");
}

void getData(port *myPort)
{
    int i;

    myPort->serialName = malloc(sizeof(char) * MAX_FILE_LENGHT);
    printf("Port name (ex: /dev/ttyUSB0)\n"
        "1 - /dev/ttyS0\n"
        "2 - /dev/ttyS1\n"
        "3 - /dev/ttyS2\n"
        "4 - /dev/ttyS3\n"
        "5 - /dev/ttyUSB0\n"
        "6 - /dev/ttyUSB1\n"
        "7 - /dev/ttyUSB2\n"
        "8 - /dev/ttyUSB3\n"
        "9 - other\n");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            strcpy(myPort->serialName, "/dev/ttyS0\0");
            break;
        case 2:
            strcpy(myPort->serialName, "/dev/ttyS1\0");
            break;
        case 3:
            strcpy(myPort->serialName, "/dev/ttyS2\0");
            break;
        case 4:
            strcpy(myPort->serialName, "/dev/ttyS3\0");
            break;
        case 5:
            strcpy(myPort->serialName, "/dev/ttyUSB0\0");
            break;
        case 6:
            strcpy(myPort->serialName, "/dev/ttyUSB1\0");
            break;
        case 7:
            strcpy(myPort->serialName, "/dev/ttyUSB2\0");
            break;
        case 8:
            strcpy(myPort->serialName, "/dev/ttyUSB3\0");
            break;
        case 9:
            scanf ("%s", myPort->serialName);
            break;
        default:
            printf("Type your own name: ");
            scanf("%s", myPort->serialName);
            break;
    }
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
            myPort->baud = 4800;
            break;
        case 2:
            myPort->baudrate = B9600;
            myPort->baud = 9600;
            break;
        case 3:
            myPort->baudrate = B19200;
            myPort->baud = 19200;
            break;
        case 4:
            myPort->baudrate = B38400;
            myPort->baud = 38400;
            break;
        default:
            myPort->baudrate = B4800;
            myPort->baud = 4800;
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
        "Name: %s\n"
        "Baudrate: %d\n"
        "Stop bits: %d\n"
        "No parity\n",
        myPort->serialName, myPort->baud, myPort->stopBit);
    return;
}

char * getMessage(char * send)
{
    printf("Message to send:\n");
    scanf("%s", send);
    strcat(send, "\n");

    if (_DEBUG)
        printf("Read: %s, bytes: %d\n", send, strlen(send));
    return send;
}
