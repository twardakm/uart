#ifndef UART_RW_H_INCLUDED
#define UART_RW_H_INCLUDED

#include <termios.h>

int WriteSerial(int *fd, char *buff, int len);
int ReadSerial(int *fd, char *buff, int len);

#endif // UART-RW_H_INCLUDED
