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

int OpenSerial(int *fd, char *SerialName, speed_t baudrate)
{
    struct termios SerialConfig;
    memset(&SerialConfig, 0, sizeof (SerialConfig));

    if(_DEBUG)
        printf("Opening serial port: %s...", SerialName);

    *fd = open(SerialName, O_RDWR | O_NOCTTY | O_SYNC);
    if(*fd < 0)
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

        if(tcgetattr(*fd, &SerialConfig) != 0)
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
    SerialConfig.c_cflag &= ~CSIZE;
    SerialConfig.c_cflag |= CS8;
    /* ------------------------ */
    /* wyłączona kontrola parzystonści i 1 bity stopu */
    SerialConfig.c_cflag &= ~PARENB;
    SerialConfig.c_cflag &= ~PARODD;
    SerialConfig.c_cflag &= ~CSTOPB;
    /* --------------------------------------------- */
    SerialConfig.c_cflag &= ~CRTSCTS; // wyłączenie sprzętowej kontroli przepływu
    SerialConfig.c_cflag |= (CLOCAL | CREAD); //włączenie odbiornika

    /* ------ */

    /* L_FLAG
    * tryb kanoniczny bez echa i kontroli przepływu danych*/
    SerialConfig.c_lflag = 0;
    /* ------ */

    /* C_IFLAG */

    SerialConfig.c_iflag &= ~(IXON | IXOFF | IXANY); //wyłączenie sprzętowej kontroli przepływu danych
    /*ignorowanie znaku <CR>, znak nowej lini będzie odblokowywał wywołanie read()*/
    SerialConfig.c_iflag &= ~IGNBRK;         // ignore break signal
    SerialConfig.c_iflag &= ~IGNCR;
    SerialConfig.c_iflag &= ~ICRNL;
    /* -------------------------------------------------------------------------- */
    /* ------- */

    SerialConfig.c_oflag &= 0; //no remapping, no delays
    SerialConfig.c_oflag |= ONLCR;

    SerialConfig.c_cc[VMIN]  = 0;            // read doesn't block
    SerialConfig.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if(_DEBUG)
        printf("Setting in/out speed...\n");
    cfsetispeed(&SerialConfig, baudrate);
    cfsetospeed(&SerialConfig, baudrate);

    if(_DEBUG)
       printf("Done\n");

    if(_DEBUG)
        printf("Applying new configuration...\n");
        if(tcsetattr(*fd, TCSANOW, &SerialConfig) != 0)
        {
            if(_DEBUG)
                printf("Fail\n");
            return -1;
        }
        else
        {
            if(SerialConfig.c_iflag & IGNCR) {
                printf("Received CRs are ignored.\n");
            }
            else if(SerialConfig.c_iflag & ICRNL)
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
int CloseSerial(int *fd)
{
    if(_DEBUG)
        printf("Closing serial port...");

    if(close(*fd) < 0)
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
