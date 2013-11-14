#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "uart-config.h"
#include "uart-rw.h"

int main()
{
    printf("UART\n---------------\n");

    //ustawianie UART
    int fd;
    if (OpenSerial(&fd, "/dev/ttyUSB0", B38400) != 0) return -1;

    char buff[2];
    buff[1] = '0';

    char text[100];
    int i = 0;
    char send[4] = {'A','T',13,'\n'};

    while(1)
    {
        printf("\nWysyłanie \'AT\'... ");
        WriteSerial(&fd, send, 4);
        printf("wysłano");
        getchar();

        while (1)
        {
            ReadSerial(&fd, buff, 1);
            if (buff[0] == '\n')
            {
                text[i] = '\n';
                text[++i] = '\0';
                break;
            }
            text[i++] = buff[0];
        }
        break;
    }

    printf("Odebrano: %s", text);

    if (CloseSerial(&fd) != 0) return -1;

    return 0;
}
