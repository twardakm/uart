#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "uart_config.h"
#include "uart_rw.h"
#include "uart_interaction.h"

int main()
{
    welcomeMessage();

    port *myPort = (port *)malloc(sizeof(port));
    myPort->fd = (int *)malloc(sizeof(int));

    getData(myPort);

    //ustawianie UART
    if (OpenSerial(myPort) != 0) return -1;

    char *buff = malloc(sizeof(char) * 2);
    buff[1] = '0';

    char *text = malloc(sizeof(char) * 16);
    char *send = malloc(sizeof(char) * 32);

    int i = 0;

    while(1)
    {
        send = getMessage(send);
        printf("\nWysyłanie %s...", send);
        WriteSerial(myPort, send, strlen(send));
        printf("wysłano\n");
        getchar();

        while (1)
        {
            ReadSerial(myPort, buff, 1);
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

    free(buff);
    free(text);

    if (CloseSerial(myPort) != 0)
    {
        free(myPort->fd);
        free(myPort->serialName);
        free(myPort);
        return -1;
    }

    free(myPort->fd);
    free(myPort->serialName);
    free(myPort);

    return 0;
}
