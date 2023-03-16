/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "imgmgr/imgmgr.h"
#include "hal/hal_gpio.h"
#include "hal/hal_bsp.h"

#include "hal/hal_uart.h"
//#include "uart_hal/uart_hal.h"
#include "mcu/nrf52_hal.h"

#include "console/console.h"

#include "os/os_eventq.h"


#include <crc/crc8.h>

//#define DIAGMSG(s,u) printf(s,u)
#ifndef DIAGMSG
#define DIAGMSG(s,u)
#endif


#define DATABITS 8 
#define STOPBITS 1
#define BAUDRATE 115200
#define UART 0


static int uart_rx_cb(void *arg, uint8_t data);
static int uart_tx(void *arg);
static void uart_rx_func(char byte);

static struct uart_buffer
{
    char byte;
    char mem_buf [15];
    char *tx_data;
    int tx_off;
    int tx_len;
}uart_buffer;

int i = 0;
struct uart_buffer buf1;

/* Event callback to process a line of input from console. */
static int uart_rx_cb(void *arg, uint8_t data)
{

    char temp = (char) data;
    // *str = strcat(&str, temp);
    buf1.mem_buf[i] = temp;
    i++;
    if(i >= 15)
    {
        i = 0;
    }
    printf("%c", buf1.mem_buf[i],'\n');
    if(data == NULL)
    {
        return -1;
    }
}

void tx_func(char *tx_data, int data_len)
{
        buf1.tx_data = tx_data;
        buf1.tx_len = data_len;
        buf1.tx_off = 0;

        hal_uart_start_tx(UART);

}

static int uart_tx_cb(void *arg)
{

    // char *str = "Hello Sonicission!";
    // char *ptr = str;

    // while(*ptr) {
    //     hal_uart_blocking_tx(UART, *ptr++);
    // }
    // hal_uart_blocking_tx(UART, '\n');

    int rc;
    if(buf1.tx_off >= buf1.tx_len)
    {
        buf1.tx_data = NULL;
        return -1;
    }
    rc = buf1.tx_data[buf1.tx_off];
    buf1.tx_off++;
    return rc;

}


int main()
{
    int var;
    struct uart_buffer *buf1;

    struct nrf52_uart_cfg cfg = {
            .suc_pin_tx = 27,                          /* pins for IO */
            .suc_pin_rx = 26
    };
    
    const char my_str = "string";

    sysinit();
    assert (hal_uart_init(UART, &cfg) == 0);
    var = hal_uart_init_cbs(0, 
                        uart_tx_cb,
                        NULL,
                        uart_rx_cb,
                        buf1);


    // assert(!var);

    var = hal_uart_config(0, 
                    BAUDRATE, 
                    DATABITS, 
                    STOPBITS, 
                    HAL_UART_PARITY_NONE,
                    HAL_UART_FLOW_CTL_NONE);


    assert(!var);



    // hal_uart_start_rx(UART);

    // char *str1 = "app.ver\r";
    // int len1 = strlen(str1);

    char *str1 = "0x9\r\n";
    int len1 = strlen(str1);

    char *str2 = "100\r\n";
    int len2 = strlen(str2);

    char *str3 = "us.strm.start\r\n";
    int len3 = strlen(str3);

    char *str4 = "2\r\n";
    int len4 = strlen(str4);

    char *str5 = "0\r\n";
    int len5 = strlen(str5);

    char *str6 = "us.strm.stop\r\n";
    int len6 = strlen(str6);

    char *str7 = "err\r\n";
    int len7 = strlen(str7);

    char *str8 = "bp.fg.rsoc.last\r\n";
    int len8 = strlen(str8);

    char *str9 = "gn.usecnt\r\n";
    int len9 = strlen(str9);

    char *str11 = "us.strm.state.mask.set\r\n";
    int len11 = strlen(str11);

    char *str12 = "us.strm.delay.set\r\n";
    int len12 = strlen(str12);

    char *str14 = "us.act.set\r\n";
    int len14 = strlen(str14);


    
    os_time_delay(OS_TICKS_PER_SEC);

    tx_func(str1, len1);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str11, len11);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str2, len2);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str12, len12);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str3, len3);
    //os_time_delay(2*OS_TICKS_PER_SEC);

    hal_uart_start_rx(UART);
    os_time_delay(OS_TICKS_PER_SEC);

    tx_func(str4, len4);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str14, len14);
    os_time_delay(4*OS_TICKS_PER_SEC);

    tx_func(str5, len5);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str14, len14);
    os_time_delay(2*OS_TICKS_PER_SEC);


    tx_func(str6, len6);
    os_time_delay(2*OS_TICKS_PER_SEC);

    hal_uart_start_rx(UART);
    os_time_delay(OS_TICKS_PER_SEC);

    //printf("%s","error",'\n');


    tx_func(str8, len8);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str9, len9);
    os_time_delay(2*OS_TICKS_PER_SEC);

    tx_func(str7, len7);
    os_time_delay(4*OS_TICKS_PER_SEC);



    
    os_time_delay(OS_TICKS_PER_SEC);

    while(1)
    {

    }
}
