/**
 * @file main.c
 * @author Nick Goralka (NickGoralka@gmail.com)
 * @brief Low Power Development
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


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
#include "sysinit/sysinit.h"
#include <nrf52.h>
#include "os/mynewt.h"
#include "syscfg/syscfg.h"
#include "sysflash/sysflash.h"
#include "flash_map/flash_map.h"
#include "hal/hal_bsp.h"
#include "hal/hal_system.h"
#include "hal/hal_flash.h"
#include "hal/hal_spi.h"
#include "hal/hal_watchdog.h"
#include "hal/hal_i2c.h"
#include "mcu/nrf52_hal.h"
#include "mcu/nrf52_periph.h"
#include "FuelGauge_BQ27441_g1.h"
#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif


#include <uwb/uwb.h>

#if MYNEWT_VAL(UWBCFG_ENABLED)
#include "uwbcfg/uwbcfg.h"
#endif
#if MYNEWT_VAL(DW1000_DEVICE_0)
#include <dw1000/dw1000_gpio.h>
#include <dw1000/dw1000_hal.h>
#endif


#include <crc/crc8.h>
#include "nrf.h"
// #include "nrf_drv_gpiote.h"
// #include "app_error.h"
#include "boards.h"
// #include "nrf52_hal.h"
#include <hal/hal_i2c.h>
#include <hal/hal_gpio.h>
#include <dw1000/dw1000_hal.h>
#include "mcu/nrf52_hal.h"
#include "mcu/nrf52_periph.h"


#define I2C_NUM 1

#define TIMEOUT 100


/**
 * @brief Initialize the I2C bus for the specific application
 * 
 */
void initialize_i2c()
{

   /** I2C controller hardware settings */
    struct nrf52_hal_i2c_cfg config = {
        .scl_pin = 8,
        .sda_pin = 15,
        .i2c_frequency = 100
    };

    assert (hal_i2c_init(I2C_NUM, &config) == 0);

    assert(hal_i2c_enable(I2C_NUM) == 0);

}

/**
 * @brief Write to device over the I2C bus
 * 
 * @param addr [-] i2c address of the device being written to
 * @param len [-] number of bytes being transmitted
 * @param buf [-] pointer to memory buffer
 * @param stop_bit [-] if true send a stop bit and end the transmission
 * @return int [-] Error Code
 * @todo [-] design - implement better error handling
 */
int i2c_write(uint8_t addr, uint16_t len, uint8_t* buf, bool stop_bit)
{
    struct hal_i2c_master_data data_packet;

    data_packet.address = addr;
    data_packet.len = len;
    data_packet.buffer = buf;

    uint8_t last_op = (stop_bit) ? 1 : 0;

    return hal_i2c_master_write(I2C_NUM, &data_packet, TIMEOUT, last_op);

}

/**
 * @brief Read from device over the I2C bus
 * 
 * @param addr [-] address of the device being read from
 * @param len [-] bunber of bytes
 * @param buf [-] pointer to memory buffer
 * @param stop_bit [-] if true send a stop bit and end the transmission
 * @return int [-] Error Code
 * @todo [-] design - implement better error handling
 */
int i2c_read(uint8_t addr, uint16_t len, uint8_t* buf, bool stop_bit)
{
    struct hal_i2c_master_data data_packet;

    data_packet.address = addr;
    data_packet.len = len;
    data_packet.buffer = buf;

    uint8_t last_op = (stop_bit) ? 1 : 0;

    return hal_i2c_master_read(I2C_NUM, &data_packet, TIMEOUT, last_op);
}


int main(int argc, char **argv){
    int rc;

    sysinit();

    struct uwb_dev * udev = uwb_dev_idx_lookup(0);


    FuelGauge_BQ27441_g1_t fuel_gauge;

    fuel_gauge.i2c_write_bytes = i2c_write;
    fuel_gauge.i2c_read_bytes = i2c_read;

    FuelGauge_BQ27441_g1_t* fuel_gauge_ptr = &fuel_gauge;

    uint8_t buf[2];

    initialize_i2c();
    uwb_sleep_config(udev);
    uwb_enter_sleep(udev);

    printf("UWB Chip in Deep Sleep\n");

    // hal_bsp_power_state(HAL_BSP_POWER_DEEP_SLEEP);

    
    while (1)
    {

        get_device_type_BQ27441_g1_t(fuel_gauge_ptr);


        volatile uint16_t voltage = get_voltage_mV_BQ27441_g1(fuel_gauge_ptr);

        volatile uint16_t current = get_average_current_mA_BQ27441_g1(fuel_gauge_ptr);

        // NRF_POWER->SYSTEMOFF = 1;
        // os_tick_idle(10);

    }

}
