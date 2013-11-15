#ifndef UART_RW_H_INCLUDED
#define UART_RW_H_INCLUDED

#include <termios.h>

int WriteSerial(port *myPort, char *buff, int len);
int ReadSerial(port *myPort, char *buff, int len);

#endif // UART-RW_H_INCLUDED
