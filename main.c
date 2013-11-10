#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "uart_olinuxino.h"
#include "gpio_lib.h"

int main()
{
    printf("UART\n---------------\n");

    if (sunxi_gpio_init() == SETUP_OK) printf("Zainicjalizowano poprawnie GPIO\n");
    else
    {
        printf("Błąd inicjalizacji GPIO\n");
        return -1;
    }

    if (sunxi_gpio_set_cfgpin(PIN4, 1) == 0 &&
        sunxi_gpio_set_cfgpin(PIN39, 1) == 0) printf("Port %d oraz %d został ustawiony jako wyjście\n", PIN4, PIN39);
    else
    {
        printf("Błąd ustawiania na wyjście portów\n");
        return -1;
    }

    //ustawianie UART
    int fd;
    if (OpenSerial(&fd, "/dev/ttyS0", B4800) == 0) printf("Port szeregowy został otwarty poprawnie\n");
    else
    {
        printf("Błąd przy otwieraniu portu szeregowego\n");
        return -1;
    }


    printf("a - dioda 1\nb - dioda 2\nq - wyjscie\n");

    char *message = malloc(sizeof (char) * 8);
    char buff[2];
    buff[1] = 0;
    int i = 0;
    int n;

    while(1)
    {
        for (i = 0; i < 8; i++)
        {
            n = ReadSerial(&fd, buff, 1);
            if (n > 0)
            {
                message[i] = buff[0];
                fflush(stdout);
            }
        }

       // if (r == 'a')
      /*  {
            if (sunxi_gpio_get_output(PIN4))
                sunxi_gpio_set_output(PIN4, 0);
            else
                sunxi_gpio_set_output(PIN4, 1);
        }
        //else if (r == 'b')
        {
            if (sunxi_gpio_get_output(PIN39))
                sunxi_gpio_set_output(PIN39, 0);
            else
                sunxi_gpio_set_output(PIN39, 1);
        }
//        else if (r == 'q')
        //    break;*/

        printf("\nOdebrano: %s\n", message);
    }

    sunxi_gpio_cleanup();

    if (CloseSerial(&fd) == 0) printf ("Poprawnie zamknięto port szeregowy\n");
    else
    {
        printf("Nie udało się zamknąć portu szeregowego\n");
        return -1;
    }

    free(message);

    return 0;
}
