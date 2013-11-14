#ifndef _UART_CONFIG_H_INCLUDED
#define _UART_CONFIG_H_INCLUDED

#include <termios.h>

#define _DEBUG 1

int OpenSerial(int *fd, char *SerialName, speed_t baudrate);
int CloseSerial(int *fd);

#endif
