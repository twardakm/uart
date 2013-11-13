#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "uart_olinuxino.h"
#include "gpio_lib.h"

int main()
{
    printf("UART\n---------------\n");

    //ustawianie UART
    int fd;
    if (OpenSerial(&fd, "/dev/ttyS0", B38400) != 0) return -1;

    char *buff;

    char ch[2];
    int i = 0;

    while(1)
    {
        buff = malloc(sizeof (char) * 80);
        i = 0;
        ch[1] = 0;

        WriteSerial(&fd, "A\n", 2);
        printf("\n-----\nwiadomość wysłana\n-----\n");
        getchar();

        while(1)
        {
            if (ReadSerial(&fd, ch, 1) == -1) break;
            if(ch[0] == '\n')
            {
                printf("Koniec odbierania\n");
                break;
            }
            buff[i++] = ch[0];
        }
        printf("\n+++++\nwiadomość odebrana: %s\n+++++\n", buff);
        free(buff);
    }

    if (CloseSerial(&fd) != 0) return -1;

    free(buff);

    return 0;
}
