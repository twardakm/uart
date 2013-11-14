#ifndef _UART_CONFIG_H_INCLUDED
#define _UART_CONFIG_H_INCLUDED

#include <termios.h>

#define _DEBUG 1

typedef struct port
{
    char *serialName;
    speed_t baudrate;
    int baud; //to samo co baudrate tylko w int
    int stopBit;
    int *fd; //wskaźnik na plik
    struct termios serialConfig;
}port;

int OpenSerial(int *fd, char *SerialName, speed_t baudrate);
int CloseSerial(int *fd);

#endif
