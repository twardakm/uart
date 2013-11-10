#ifndef _GPIO_LIB_H_
#define _GPIO_LIB_H_

/*Definiuję porty z pyA13.c
* ------------------- */
#define PIN4    SUNXI_GPB(0)
#define PIN5    SUNXI_GPB(1)
#define PIN6    SUNXI_GPB(2)
#define PIN7    SUNXI_GPB(3)
#define PIN8    SUNXI_GPB(4)
#define PIN9    SUNXI_GPB(10)
#define PIN10   SUNXI_GPB(15)
#define PIN11   SUNXI_GPB(16)

#define PIN12   SUNXI_GPC(0)
#define PIN13   SUNXI_GPC(1)
#define PIN14   SUNXI_GPC(2)
#define PIN15   SUNXI_GPC(3)
#define PIN16   SUNXI_GPC(4)
#define PIN17   SUNXI_GPC(5)
#define PIN18   SUNXI_GPC(6)
#define PIN19   SUNXI_GPC(7)
#define PIN20   SUNXI_GPC(8)
#define PIN21   SUNXI_GPC(9)
#define PIN22   SUNXI_GPC(10)
#define PIN23   SUNXI_GPC(11)
#define PIN24   SUNXI_GPC(12)
#define PIN25   SUNXI_GPC(13)
#define PIN26   SUNXI_GPC(14)
#define PIN27   SUNXI_GPC(15)
#define PIN28   SUNXI_GPC(19)

#define PIN29   SUNXI_GPE(4)
#define PIN30   SUNXI_GPE(5)
#define PIN31   SUNXI_GPE(6)
#define PIN32   SUNXI_GPE(7)
#define PIN33   SUNXI_GPE(8)
#define PIN34   SUNXI_GPE(9)
#define PIN35   SUNXI_GPE(10)
#define PIN36   SUNXI_GPE(11)

#define PIN37   SUNXI_GPG(9)
#define PIN38   SUNXI_GPG(10)
#define PIN39   SUNXI_GPG(11)

#define MISO    SUNXI_GPE(3)
#define MOSI    SUNXI_GPE(2)
#define SCK     SUNXI_GPE(1)
#define CS      SUNXI_GPE(0)
/*--------------------------*/


#define SW_PORTC_IO_BASE 0x01c20800


#define SUNXI_GPIO_A	0
#define SUNXI_GPIO_B	1
#define SUNXI_GPIO_C	2
#define SUNXI_GPIO_D	3
#define SUNXI_GPIO_E	4
#define SUNXI_GPIO_F	5
#define SUNXI_GPIO_G	6
#define SUNXI_GPIO_H	7
#define SUNXI_GPIO_I	8

#define SETUP_OK            0
#define SETUP_DEVMEM_FAIL   1
#define SETUP_MALLOC_FAIL   2
#define SETUP_MMAP_FAIL     3

#define HIGH    1
#define LOW     0

#define INPUT   0
#define OUTPUT  1
#define PER     2


struct sunxi_gpio {
    unsigned int cfg[4];
    unsigned int dat;
    unsigned int drv[2];
    unsigned int pull[2];
};

/* gpio interrupt control */
struct sunxi_gpio_int {
    unsigned int cfg[3];
    unsigned int ctl;
    unsigned int sta;
    unsigned int deb;
};

struct sunxi_gpio_reg {
    struct sunxi_gpio gpio_bank[9];
    unsigned char res[0xbc];
    struct sunxi_gpio_int gpio_int;
};

#define GPIO_BANK(pin)	((pin) >> 5)
#define GPIO_NUM(pin)	((pin) & 0x1F)

#define GPIO_CFG_INDEX(pin)	(((pin) & 0x1F) >> 3)
#define GPIO_CFG_OFFSET(pin)	((((pin) & 0x1F) & 0x7) << 2)

/* GPIO bank sizes */
#define SUNXI_GPIO_A_NR		(32)
#define SUNXI_GPIO_B_NR		(32)
#define SUNXI_GPIO_C_NR		(32)
#define SUNXI_GPIO_D_NR		(32)
#define SUNXI_GPIO_E_NR		(32)
#define SUNXI_GPIO_F_NR		(32)
#define SUNXI_GPIO_G_NR		(32)
#define SUNXI_GPIO_H_NR		(32)
#define SUNXI_GPIO_I_NR		(32)

#define SUNXI_GPIO_NEXT(__gpio) ((__gpio##_START)+(__gpio##_NR)+0)

enum sunxi_gpio_number {
    SUNXI_GPIO_A_START = 0,
    SUNXI_GPIO_B_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_A),	//32
    SUNXI_GPIO_C_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_B),	//64
    SUNXI_GPIO_D_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_C),	//96
    SUNXI_GPIO_E_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_D),	//128
    SUNXI_GPIO_F_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_E),	//160
    SUNXI_GPIO_G_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_F),	//192
    SUNXI_GPIO_H_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_G),	//224
    SUNXI_GPIO_I_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_H)	//256
};

/* SUNXI GPIO number definitions */
#define SUNXI_GPA(_nr) (SUNXI_GPIO_A_START + (_nr))
#define SUNXI_GPB(_nr) (SUNXI_GPIO_B_START + (_nr))
#define SUNXI_GPC(_nr) (SUNXI_GPIO_C_START + (_nr))
#define SUNXI_GPD(_nr) (SUNXI_GPIO_D_START + (_nr))
#define SUNXI_GPE(_nr) (SUNXI_GPIO_E_START + (_nr))
#define SUNXI_GPF(_nr) (SUNXI_GPIO_F_START + (_nr))
#define SUNXI_GPG(_nr) (SUNXI_GPIO_G_START + (_nr))
#define SUNXI_GPH(_nr) (SUNXI_GPIO_H_START + (_nr))
#define SUNXI_GPI(_nr) (SUNXI_GPIO_I_START + (_nr))

/* GPIO pin function config */
#define SUNXI_GPIO_INPUT (0)
#define SUNXI_GPIO_OUTPUT (1)
#define SUNXI_GPIO_PER (2)

#define SUNXI_GPA0_ERXD3 (2)
#define SUNXI_GPA0_SPI1_CS0 (3)
#define SUNXI_GPA0_UART2_RTS (4)

#define SUNXI_GPA1_ERXD2 (2)
#define SUNXI_GPA1_SPI1_CLK	(3)
#define SUNXI_GPA1_UART2_CTS	(4)

#define SUNXI_GPA2_ERXD1	(2)
#define SUNXI_GPA2_SPI1_MOSI	(3)
#define SUNXI_GPA2_UART2_TX	(4)

#define SUNXI_GPA10_UART1_TX	(4)
#define SUNXI_GPA11_UART1_RX	(4)

#define SUN4I_GPB22_UART0_TX	(2)
#define SUN4I_GPB23_UART0_RX	(2)

#define SUN5I_GPG3_UART0_TX	(4)
#define SUN5I_GPG4_UART0_RX	(4)

#define SUNXI_GPC2_NCLE	(2)
#define SUNXI_GPC2_SPI0_CLK	(3)

#define SUNXI_GPC6_NRB0	(2)
#define SUNXI_GPC6_SDC2_CMD	(3)

#define SUNXI_GPC7_NRB1	(2)
#define SUNXI_GPC7_SDC2_CLK	(3)

#define SUNXI_GPC8_NDQ0	(2)
#define SUNXI_GPC8_SDC2_D0	(3)

#define SUNXI_GPC9_NDQ1	(2)
#define SUNXI_GPC9_SDC2_D1	(3)

#define SUNXI_GPC10_NDQ2	(2)
#define SUNXI_GPC10_SDC2_D2	(3)

#define SUNXI_GPC11_NDQ3	(2)
#define SUNXI_GPC11_SDC2_D3	(3)

#define SUNXI_GPF2_SDC0_CLK	(2)
#define SUNXI_GPF2_UART0_TX	(4)

#define SUNXI_GPF4_SDC0_D3	(2)
#define SUNXI_GPF4_UART0_RX	(4)

extern int sunxi_gpio_input(unsigned int pin);
extern int sunxi_gpio_init(void);
extern int sunxi_gpio_set_cfgpin(unsigned int pin, unsigned int val);
extern int sunxi_gpio_get_cfgpin(unsigned int pin);
extern int sunxi_gpio_output(unsigned int pin, unsigned int val);
extern int sunxi_gpio_get_output(unsigned int pin);
extern void sunxi_gpio_cleanup(void);

extern unsigned int SUNXI_PIO_BASE;
#endif
