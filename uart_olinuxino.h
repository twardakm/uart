
#ifndef _UART_H
#define _UART_H

#include <termios.h>

#define _DEBUG 1

int OpenSerial(int *fd, char *SerialName, speed_t baudrate);
int CloseSerial(int *fd);
int WriteSerial(int *fd, char *buff, int len);
int ReadSerial(int *fd, char *buff, int len);
#endif
