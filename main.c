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

    printf("1 - zapala\n2 - gasi\n0 - wyjscie\n");

    int d;
    while(1)
    {
        scanf("%d", &d);
        if (d == 1)
        {
            sunxi_gpio_output(PIN4 , 1);
            sunxi_gpio_output(PIN39, 1);
        }
        else if (d == 2)
        {
            sunxi_gpio_output(PIN4 , 0);
            sunxi_gpio_output(PIN39, 0);
        }
        else if (d == 0)
            break;

        printf("Stan portu 4: %d", sunxi_gpio_get_cfgpin(PIN4));
    }

    sunxi_gpio_cleanup();
    return 0;
}
