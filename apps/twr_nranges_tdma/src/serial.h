/**
 * @file serial.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "hal_bsp.h"

#define TX_UART
#define RX_UART


#define MY_UART 1

/**
 * @brief Initialize the uart for the transmission
 * 
 */
void uart_init()
{

    // fill in values for this struct
    struct nrf52_uart_cfg *cfg;

    // pass configurations to the hal_uart_init();

    // Initialize UART on specificic port
    assert ( hal_uart_init(MY_UART, (void *) cfg) == 0 );  // if this asserts you fucked up

}

/**
 * @brief Transmit a 
 * 
 * @param str [-] pointer to the string being printed 
 * @param len [-] number of chars
 */
void myprint(char* str, int len)
/* write to the console with blocking */
{
    char *ptr = str;

    while(*ptr) {
        hal_uart_blocking_tx(MY_UART, *ptr++);
    }
    hal_uart_blocking_tx(MY_UART, '\n');
}
