#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "uart_config.h"
#include "uart_rw.h"

int ReadSerial(int *fd, char *buff, int len)
{
    int read_chars;
    if(_DEBUG)
        printf("Reading %d bytes of data...", len);
    read_chars = read(*fd, buff, len);
    if(read_chars < 0)
    {
        if(_DEBUG)
            printf("Fail\n");
        return -1;
    }
    else
    {
        if(_DEBUG)
            printf("Done\n");
        return 0;
    }
}
int WriteSerial(int *fd, char *buff, int len)
{
    int sent_bytes;

    if(_DEBUG)
        printf("Sending %d bytes of data...", len);
    sent_bytes = write(*fd, buff, len);
    if(sent_bytes < 0)
    {
        if(_DEBUG)
            printf("Fail\n");
        return -1;
    }
    else
    {
        if(_DEBUG)
            printf("Done\n");
        return 0;
    }
}
