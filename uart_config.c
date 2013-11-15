/*
 * uart.c
 *
 * Copyright 2013 Stefan Mavrodiev <support@olimex.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <termios.h>

#include "uart_config.h"

int OpenSerial(port *myPort)
{
    memset(&myPort->serialConfig, 0, sizeof(struct termios));

    if(_DEBUG)
        printf("Opening serial port: %s...", myPort->serialName);

    *myPort->fd = open(myPort->serialName, O_RDWR | O_NOCTTY | O_SYNC);
    if(myPort->fd < 0)
    {
        if(_DEBUG)
            printf("Fail\n");
        return -1;
    }
    else
    {
        if(_DEBUG)
            printf("Done\n");

        if(_DEBUG)
            printf("Getting current configuration...");
        if(tcgetattr(*myPort->fd, &myPort->serialConfig) != 0)
        {
            if(_DEBUG)
                printf("Fail\n");
            return -1;
        }
        else
        {
            if(_DEBUG)
                printf("Done\n");
        }
    }
    //zmiana ustawień na te wg książki

    /* C_CFLAG */

    /* ustawienie 8 bitów danej */
    myPort->serialConfig.c_cflag &= ~CSIZE;
    myPort->serialConfig.c_cflag |= CS8;
    /* ------------------------ */
    /* wyłączona kontrola parzystonści i 1 bity stopu */
    myPort->serialConfig.c_cflag &= ~PARENB;
    myPort->serialConfig.c_cflag &= ~PARODD;
    myPort->serialConfig.c_cflag &= ~CSTOPB;
    /* --------------------------------------------- */
    myPort->serialConfig.c_cflag &= ~CRTSCTS; // wyłączenie sprzętowej kontroli przepływu
    myPort->serialConfig.c_cflag |= (CLOCAL | CREAD); //włączenie odbiornika

    /* ------ */

    /* L_FLAG
    * tryb kanoniczny bez echa i kontroli przepływu danych*/
    myPort->serialConfig.c_lflag = 0;
    /* ------ */

    /* C_IFLAG */

    myPort->serialConfig.c_iflag &= ~(IXON | IXOFF | IXANY); //wyłączenie sprzętowej kontroli przepływu danych
    /*ignorowanie znaku <CR>, znak nowej lini będzie odblokowywał wywołanie read()*/
    myPort->serialConfig.c_iflag &= ~IGNBRK;         // ignore break signal
    myPort->serialConfig.c_iflag &= ~IGNCR;
    myPort->serialConfig.c_iflag &= ~ICRNL;
    /* -------------------------------------------------------------------------- */
    /* ------- */

    myPort->serialConfig.c_oflag &= 0; //no remapping, no delays
    myPort->serialConfig.c_oflag |= ONLCR;

    myPort->serialConfig.c_cc[VMIN]  = 0;            // read doesn't block
    myPort->serialConfig.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if(_DEBUG)
        printf("Setting in/out speed...\n");
    cfsetispeed(&myPort->serialConfig, myPort->baudrate);
    cfsetospeed(&myPort->serialConfig, myPort->baudrate);

    if(_DEBUG)
       printf("Done\n");

    if(_DEBUG)
        printf("Applying new configuration...\n");
        if(tcsetattr(*myPort->fd, TCSANOW, &myPort->serialConfig) != 0)
        {
            if(_DEBUG)
                printf("Fail\n");
            return -1;
        }
        else
        {
            if(myPort->serialConfig.c_iflag & IGNCR) {
                printf("Received CRs are ignored.\n");
            }
            else if(myPort->serialConfig.c_iflag & ICRNL)
            {
                printf("Received CRs are translated to NLs.\n");
            }
            else
            {
                printf("Received CRs are not changed.\n");
            }
            if(_DEBUG)
                printf("Done\n");
            /*if(_DEBUG)
                printf("Flushing serial port...");
            tcflush(*fd, TCIFLUSH);*/
            return 0;
        }



}
int CloseSerial(port *myPort)
{
    if(_DEBUG)
        printf("Closing serial port...");

    if(close(*myPort->fd) < 0)
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
