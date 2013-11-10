#include <stdio.h>
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

    printf("1 - dioda 1\n2 - dioda 2\n0 - wyjscie\n");

    int d;
    while(1)
    {
        scanf("%d", &d);
        if (d == 1)
        {
            /*if (sunxi_gpio_get_output(PIN4))
                sunxi_gpio_set_output(PIN4, 0);
            else
                sunxi_gpio_set_output(PIN4, 1);*/
            sunxi_gpio_set_output(PIN4, 1);
            sunxi_gpio_set_output(PIN39, 1);
        }
        else if (d == 2)
        {
            /*if (sunxi_gpio_get_output(PIN39))
                sunxi_gpio_set_output(PIN39, 0);
            else
                sunxi_gpio_set_output(PIN39, 1);*/
            sunxi_gpio_set_output(PIN4, 0);
            sunxi_gpio_set_output(PIN39, 0);
        }
        else if (d == 0)
            break;
        printf ("Konfiguracja portu %d: %d, %d, %d, %d",
            PIN4, sunxi_gpio_get_output(PIN4, 0), sunxi_gpio_get_output(PIN4, 1),
            sunxi_gpio_get_output(PIN4, 2), sunxi_gpio_get_output(PIN4, 3));
        printf ("Konfiguracja portu %d: %d, %d, %d, %d",
            PIN4, sunxi_gpio_get_output(PIN39, 0), sunxi_gpio_get_output(PIN39, 1),
            sunxi_gpio_get_output(PIN39, 2), sunxi_gpio_get_output(PIN39, 3));
    }

    sunxi_gpio_cleanup();
    return 0;
}
