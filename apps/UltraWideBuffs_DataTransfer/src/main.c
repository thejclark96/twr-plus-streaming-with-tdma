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
#include "hal/hal_i2c.h"
#include "hal/hal_bsp.h"
#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif
#if MYNEWT_VAL(BLE_ENABLED)
#include "bleprph/bleprph.h"
#endif

#define I2C_NUM 1

#define TIMEOUT 100


#include <uwb/uwb.h>
#include <uwb/uwb_ftypes.h>
#include <uwb_rng/uwb_rng.h>
#include <config/config.h>
#if MYNEWT_VAL(UWBCFG_ENABLED)
#include "uwbcfg/uwbcfg.h"
#endif
#include <uwb_transport/uwb_transport.h>
#if MYNEWT_VAL(TDMA_ENABLED)
#include <tdma/tdma.h>
#endif
#if MYNEWT_VAL(UWB_CCP_ENABLED)
#include <uwb_ccp/uwb_ccp.h>
#endif
#if MYNEWT_VAL(DW1000_DEVICE_0)
#include <dw1000/dw1000_gpio.h>
#include <dw1000/dw1000_hal.h>
#endif
#if MYNEWT_VAL(CONCURRENT_NRNG)
#include <nrng/nrng.h>

#endif

#include <nrng/nrng_encode.h>
#include <crc/crc8.h>

#include "FuelGauge_BQ27441_g1.h"
#include <dw1000/dw1000_hal.h>
#include "mcu/nrf52_hal.h"
#include "mcu/nrf52_periph.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DIAGMSG(s,u) printf(s,u)
#ifndef DIAGMSG
#define DIAGMSG(s,u)
#endif


// ==============================================================================
// Fuel Gauge Driver Stuff
// ==============================================================================
#define FUEL_GAUGE_SLOT 69

FuelGauge_BQ27441_g1_t fuel_gauge;

FuelGauge_BQ27441_g1_t* fuel_gauge_ptr = &fuel_gauge;

// ===================================================

uint8_t payload_increment = 0;      // Incrementer for switching between streaming ranging data or battery data

uint8_t test[512 - sizeof(uwb_transport_frame_header_t) - 2];


/**
 * @brief String to be sent via UWB
 * 
 */
// char payload[32 - sizeof(uwb_transport_frame_header_t) - 1];
uint8_t payload[512 - sizeof(uwb_transport_frame_header_t) - 2];

/**
 * @brief String to recieve data
 * 
 */
// char reciever[32 - sizeof(uwb_transport_frame_header_t) - 1];
uint8_t reciever[512 - sizeof(uwb_transport_frame_header_t) - 2];


char * fuel_gauge_string ;

// extern char* TX_Data;   // Var for range data from nrng_encode.c




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

    fuel_gauge.i2c_write_bytes = i2c_write;
    fuel_gauge.i2c_read_bytes = i2c_read;

    assert (hal_i2c_init(I2C_NUM, &config) == 0);

    assert(hal_i2c_enable(I2C_NUM) == 0);

}

#if MYNEWT_VAL(UWBCFG_ENABLED)
static bool uwb_config_updated = false;

/**
 * @fn uwb_config_update
 *
 * Called from the main event queue as a result of the uwbcfg packet
 * having received a commit/load of new uwb configuration.
 */
int
uwb_config_updated_func()
{
    /* Workaround in case we're stuck waiting for ccp with the
     * wrong radio settings */
    struct uwb_dev * udev = uwb_dev_idx_lookup(0);
    struct uwb_ccp_instance *ccp = (struct uwb_ccp_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_CCP);
    if (dpl_sem_get_count(&ccp->sem) == 0) {
        uwb_phy_forcetrxoff(udev);
        uwb_mac_config(udev, NULL);
        uwb_txrf_config(udev, &udev->config.txrf);
        uwb_start_rx(udev);
        return 0;
    }

    uwb_config_updated = true;
    return 0;
}
#endif

#if MYNEWT_VAL(CONCURRENT_NRNG)

static void
range_slot_cb(struct dpl_event * ev){
    assert(ev);

    tdma_slot_t * slot = (tdma_slot_t *) dpl_event_get_arg(ev);
    tdma_instance_t * tdma = slot->parent;
    struct uwb_ccp_instance *ccp = tdma->ccp;
    struct uwb_dev * udev = tdma->dev_inst;
    uint16_t idx = slot->idx;
    struct nrng_instance *nrng = (struct nrng_instance *)slot->arg;

    /* Avoid colliding with the ccp in case we've got out of sync */
    if (dpl_sem_get_count(&ccp->sem) == 0) {
        return;
    }

    if (ccp->local_epoch==0 || udev->slot_id == 0xffff) return;

    if (udev->role&UWB_ROLE_ANCHOR) {
        /* Listen for a ranging tag */
        uwb_set_delay_start(udev, tdma_rx_slot_start(tdma, idx));
        uint16_t timeout = uwb_phy_frame_duration(udev, sizeof(nrng_request_frame_t))
            + nrng->config.rx_timeout_delay;

        /* Padded timeout to allow us to receive any nmgr packets too */
        uwb_set_rx_timeout(udev, timeout + 0x1000);
        nrng_listen(nrng, UWB_BLOCKING);
    } else {
        /* Range with the anchors */
        if (idx%MYNEWT_VAL(NRNG_NTAGS) != udev->slot_id) {
            return;
        }

        /* Range with the anchors */
        uint64_t dx_time = tdma_tx_slot_start(tdma, idx) & 0xFFFFFFFFFE00UL;
        uint32_t slot_mask = 0;
        for (uint16_t i = MYNEWT_VAL(NODE_START_SLOT_ID);
             i <= MYNEWT_VAL(NODE_END_SLOT_ID); i++) {
            slot_mask |= 1UL << i;
        }

        if(nrng_request_delay_start(
               nrng, UWB_BROADCAST_ADDRESS, dx_time,
               UWB_DATA_CODE_SS_TWR_NRNG, slot_mask, 0).start_tx_error) {
            uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
            printf("{\"utime\": %lu,\"msg\": \"slot_timer_cb_%d:start_tx_error\"}\n",
                   utime,idx);
        }
        extern char* TX_Data;
        // printf("TEST\n");
        // printf("%s\n\n\n",TX_Data);
    }
}
#endif

/*!
 * @fn slot_cb(struct dpl_event * ev)
 *
 * In this example, slot_cb schedules the turning of the transceiver to receive mode at the desired epoch.
 * The precise timing is under the control of the DW1000, and the dw_time variable defines this epoch.
 * Note the slot_cb itself is scheduled MYNEWT_VAL(OS_LATENCY) in advance of the epoch to set up the transceiver accordingly.
 *
 * Note: The epoch time is referenced to the Rmarker symbol, it is therefore necessary to advance the rxtime by the SHR_duration such
 * that the preamble are received. The transceiver, when transmitting adjust the txtime accordingly.
 *
 * input parameters
 * @param inst - struct dpl_event *
 *
 * output parameters
 *
 * returns none
 */

static void
stream_slot_cb(struct dpl_event * ev)
{
    uint64_t dxtime, dxtime_end;
    uint64_t preamble_duration;
    assert(ev);
    tdma_slot_t * slot = (tdma_slot_t *) dpl_event_get_arg(ev);
    tdma_instance_t * tdma = slot->parent;
    struct uwb_ccp_instance *ccp = tdma->ccp;

    uint16_t idx = slot->idx;
    uwb_transport_instance_t * uwb_transport = (uwb_transport_instance_t *)slot->arg;
    /* Avoid colliding with the ccp in case we've got out of sync */
    if (dpl_sem_get_count(&ccp->sem) == 0) {
        return;
    }
#if MYNEWT_VAL(UWBCFG_ENABLED)
    struct uwb_dev * inst = tdma->dev_inst;
    if (uwb_config_updated) {
        uwb_mac_config(inst, NULL);
        uwb_txrf_config(inst, &inst->config.txrf);
        uwb_config_updated = false;
        return;
    }
#endif
    preamble_duration = (uint64_t) ceilf(uwb_usecs_to_dwt_usecs(uwb_phy_SHR_duration(tdma->dev_inst)));
    dxtime = tdma_tx_slot_start(tdma, idx);
    dxtime_end = (tdma_tx_slot_start(tdma, idx+1) -
                  ((preamble_duration + MYNEWT_VAL(OS_LATENCY))<<16)) & UWB_DTU_40BMASK;
    dxtime_end &= UWB_DTU_40BMASK;
    if (uwb_transport_dequeue_tx(uwb_transport, dxtime, dxtime_end) == false) {
        dxtime = tdma_rx_slot_start(tdma, idx);
        dxtime_end = (tdma_rx_slot_start(tdma, idx+1) -
                      ((preamble_duration + MYNEWT_VAL(OS_LATENCY))<<16)) & UWB_DTU_40BMASK;
        dxtime_end &= UWB_DTU_40BMASK;
        uwb_transport_listen(uwb_transport, UWB_BLOCKING, dxtime, dxtime_end);
    }
}

// static uint8_t g_idx = 0;
// static uint32_t g_missed_count = 0;
// static uint32_t g_ok_count = 0;


/**
 * @brief Reciever Callback Function
 * 
 * @param inst 
 * @param uid 
 * @param mbuf 
 * @return true 
 * @return false 
 */
static bool
uwb_transport_cb(struct uwb_dev * inst, uint16_t uid, struct dpl_mbuf * mbuf)
{

    // get the length of the data in the memory buffer
    uint16_t len = DPL_MBUF_PKTLEN(mbuf);

    // char receiver[len];

    // copy data from the memory buffer to our local variable
    dpl_mbuf_copydata(mbuf, 0, sizeof(reciever), reciever);
    dpl_mbuf_free_chain(mbuf);
    // g_idx++;


    /* First byte stores crc */
    uint8_t crc = (uint8_t) (reciever[0]); 

    // since I am sending string data here the string won't always be the length of the reciever buffer
        // later I will worry about variable length packets
    if (crc != crc8_calc(0, reciever+1, sizeof(reciever)-1) || len != sizeof(reciever))
    {
        uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
        printf("{\"utime\": %lu,\"error\": \" crc mismatch len=%d, sizeof(test) = %d\"}\n",utime, len, sizeof(reciever));
    }
    // } else if (test[1] != g_idx) {
    //     /* Second byte stores an index */
    //     uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
    //     g_ok_count++;
    //     g_missed_count += (test[1] - g_idx)&0xff;
    //     printf("{\"utime\": %lu,\"error\": \" idx mismatch (got %d != expected %d) (missed:%ld, ok:%ld\"}\n",
    //            utime, test[1], g_idx, g_missed_count, g_ok_count);
    // } 
    else 
    {
        // g_ok_count++;
        uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
        printf("{\"utime\": %lu , message:%s\"}\n",
               utime, reciever);

        
    }

    // g_idx = test[1];
    return true;
}

static struct dpl_callout fuel_gauge_callout;

static void fuel_gauge_data_fetch_cb (struct dpl_event * ev)
{
     uint8_t fg_payload[512 - sizeof(uwb_transport_frame_header_t) - 2];

    dpl_callout_reset(&fuel_gauge_callout, OS_TICKS_PER_SEC);

    volatile uint16_t voltage = get_voltage_mV_BQ27441_g1(fuel_gauge_ptr);

    volatile int16_t current = get_average_current_mA_BQ27441_g1(fuel_gauge_ptr);

    volatile uint16_t state_of_charge = get_state_of_charge_BQ27441_g1(fuel_gauge_ptr);

    // volatile uint16_t state_of_health = get_state_of_health_BQ27441_g1(fuel_gauge_ptr);

    sprintf(fuel_gauge_string, "Fuel Gauge Voltage (mV): %d, Current (mA) %d, SOC: %d %%\n", voltage, current, state_of_charge);
    printf("Fuel Gauge Voltage (mV): %d, Current (mA) %d, SOC (\%): %d\n", voltage, current, state_of_charge);


   
    uwb_transport_instance_t * uwb_transport = (uwb_transport_instance_t *)dpl_event_get_arg(ev);
    struct uwb_ccp_instance * ccp = (struct uwb_ccp_instance *)uwb_mac_find_cb_inst_ptr(uwb_transport->dev_inst, UWBEXT_CCP);

    for (uint8_t i = 0; i < 18; i++)
    {
        uint16_t destination_uid = ccp->frames[0]->short_address;
        if (!destination_uid) break;
        struct dpl_mbuf * mbuf;
        if (uwb_transport->config.os_msys_mpool)
        {
            // Add packet headers to the memory buffer
            mbuf = dpl_msys_get_pkthdr(sizeof(fg_payload), sizeof(uwb_transport_user_header_t));
        }
        else
        {
            mbuf = dpl_mbuf_get_pkthdr(uwb_transport->omp, sizeof(uwb_transport_user_header_t));
        }
        if (mbuf)
        {
            // /* Second byte stores an index */
            // test[1]++;
            /* First byte stores crc */
            fg_payload[0] = crc8_calc(0, fg_payload+1, sizeof(fg_payload)-1);
            dpl_mbuf_copyinto(mbuf, 0, fg_payload, sizeof(fg_payload));
            uwb_transport_enqueue_tx(uwb_transport, destination_uid, 0xDEAD, 8, mbuf);
        }else{
            break;
        }
    }

}

#if MYNEWT_VAL(UWB_TRANSPORT_ROLE) == 1
static struct dpl_callout stream_callout;

/**
 * @brief Trransmit function
 * 
 * @param ev [-] event structure
 */
static void
stream_timer(struct dpl_event *ev)
{
    // dpl_callout_reset(&stream_callout, OS_TICKS_PER_SEC/80);
    // for (uint16_t i=1; i < 512 - 1; i++)        // Need to add macro for 512, name it def size or something
    //     payload[i] = TX_Data[i-1];

    // for (uint16_t i=1; i < 512 - 1; i++)        // Need to add macro for 512, name it def size or something
    //     payload[i] = fuel_gauge_string[i-1];


    for (payload_increment ; payload_increment < 3; payload_increment++){
        if          (payload_increment==0){     // Stream ranging data
            for (uint16_t j=1; j < 512 - 1; j++)        // Need to add macro for 512, name it def size or something
            payload[j] = TX_Data[j-1];
            payload_increment++;
            break;


        }else if    (payload_increment==1){     // Stream battery data
            for (uint16_t j=1; j < 512 - 1; j++)        // Need to add macro for 512, name it def size or something
            payload[j] = fuel_gauge_string[j-1];
            payload_increment++;
            break;


        }else{                                  // Reset count
            payload_increment = 0;
            break;
        }

    }


    // Change timer frequency to 1 Hz
    dpl_callout_reset(&stream_callout, OS_TICKS_PER_SEC);

    uwb_transport_instance_t * uwb_transport = (uwb_transport_instance_t *)dpl_event_get_arg(ev);
    struct uwb_ccp_instance * ccp = (struct uwb_ccp_instance *)uwb_mac_find_cb_inst_ptr(uwb_transport->dev_inst, UWBEXT_CCP);

    for (uint8_t i = 0; i < 18; i++)
    {
        uint16_t destination_uid = ccp->frames[0]->short_address;
        if (!destination_uid) break;
        struct dpl_mbuf * mbuf;
        if (uwb_transport->config.os_msys_mpool)
        {
            // Add packet headers to the memory buffer
            mbuf = dpl_msys_get_pkthdr(sizeof(payload), sizeof(uwb_transport_user_header_t));
        }
        else
        {
            mbuf = dpl_mbuf_get_pkthdr(uwb_transport->omp, sizeof(uwb_transport_user_header_t));
        }
        if (mbuf)
        {
            // /* Second byte stores an index */
            // test[1]++;
            /* First byte stores crc */
            payload[0] = crc8_calc(0, payload+1, sizeof(payload)-1);
            dpl_mbuf_copyinto(mbuf, 0, payload, sizeof(payload));
            uwb_transport_enqueue_tx(uwb_transport, destination_uid, 0xDEAD, 8, mbuf);
        }else{
            break;
        }
    }
}
#endif




int main(int argc, char **argv){
    int rc;

    sysinit();


    

    uint8_t buf[2];

    initialize_i2c();

    // ==============================================================================

    // initialize the memory size
    TX_Data = (char *) malloc(512 * sizeof(char));

    fuel_gauge_string = (char *) malloc(512 * sizeof(char));

    struct uwb_dev * udev = uwb_dev_idx_lookup(0);

#if MYNEWT_VAL(USE_DBLBUFFER)
    /* Make sure to enable double buffring */
    udev->config.dblbuffon_enabled = 1;
    udev->config.rxauto_enable = 0;
    uwb_set_dblrxbuff(udev, true);
#else
    udev->config.dblbuffon_enabled = 0;
    udev->config.rxauto_enable = 1;
    uwb_set_dblrxbuff(udev, false);
#endif

#if MYNEWT_VAL(UWBCFG_ENABLED)
    /* Register callback for UWB configuration changes */
    struct uwbcfg_cbs uwb_cb = {
        .uc_update = uwb_config_updated_func
    };
    uwbcfg_register(&uwb_cb);
    /* Load config from flash */
    conf_load();
#endif

    hal_gpio_init_out(LED_BLINK_PIN, 1);
    hal_gpio_init_out(LED_1, 1);
    hal_gpio_init_out(LED_3, 1);

    struct _uwb_transport_instance * uwb_transport = (struct _uwb_transport_instance *)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_TRANSPORT);
    assert(uwb_transport);

    struct _uwb_transport_extension extension = {
        .tsp_code = 0xDEAD,
        .receive_cb = uwb_transport_cb
    };

    uwb_transport_append_extension(uwb_transport, &extension);

    struct uwb_ccp_instance * ccp = (struct uwb_ccp_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_CCP);
    assert(ccp);

    if ((udev->role & UWB_ROLE_CCP_MASTER) || MYNEWT_VAL(UWB_TRANSPORT_ROLE) == 0) {
        /* Start as clock-master */
        uwb_ccp_start(ccp, CCP_ROLE_MASTER);
    } else {
        uwb_ccp_start(ccp, CCP_ROLE_SLAVE);
    }

#if MYNEWT_VAL(BLE_ENABLED)
    ble_init(udev->euid);
#endif

#if MYNEWT_VAL(DW1000_DEVICE_0)
    // Using GPIO5 and GPIO6 to study timing.
    dw1000_gpio5_config_ext_txe( hal_dw1000_inst(0));
    dw1000_gpio6_config_ext_rxe( hal_dw1000_inst(0));
#endif

    uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
    printf("{\"utime\": %lu,\"exec\": \"%s\"}\n",utime,__FILE__);
    printf("{\"device_id\"=\"%lX\"",udev->device_id);
    printf(",\"panid=\"%X\"",udev->pan_id);
    printf(",\"addr\"=\"%X\"",udev->uid);
    printf(",\"part_id\"=\"%lX\"",(uint32_t)(udev->euid&0xffffffff));
    printf(",\"lot_id\"=\"%lX\"}\n",(uint32_t)(udev->euid>>32));
    printf("{\"utime\": %lu,\"msg\": \"frame_duration = %d usec\"}\n",utime,uwb_phy_frame_duration(udev, sizeof(test) + sizeof(uwb_transport_frame_header_t)));
    printf("{\"utime\": %lu,\"msg\": \"SHR_duration = %d usec\"}\n",utime,uwb_phy_SHR_duration(udev));
    printf("UWB_TRANSPORT_ROLE = %d\n",  MYNEWT_VAL(UWB_TRANSPORT_ROLE));

    tdma_instance_t * tdma = (tdma_instance_t*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_TDMA);
    assert(tdma);

#if MYNEWT_VAL(CONCURRENT_NRNG)
    struct nrng_instance * nrng = (struct nrng_instance *)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_NRNG);
    assert(nrng);
    /* Slot 0:ccp, Slot 1+2:PAN , the rest of the slots we play around with */
    for (uint16_t i = 3; i < MYNEWT_VAL(TDMA_NSLOTS) - 1; i++){
        if( (i%20 != 0 ) )
        {
            tdma_assign_slot(tdma, stream_slot_cb,  i, (void*)uwb_transport); 
        }
        else 
            // tdma_assign_slot(tdma, stream_slot_cb,  i, (void*)uwb_transport);
            tdma_assign_slot(tdma, range_slot_cb,  i, (void*)nrng);
        
    }
#else
/* Slot 0:ccp, 1-160 stream */
    for (uint16_t i = 3; i < MYNEWT_VAL(TDMA_NSLOTS) - 1; i++)
            tdma_assign_slot(tdma, stream_slot_cb,  i, (void*)uwb_transport);
#endif

    // char* message = "UWB Test";
    // char* message = "{\"utime\": 14450645,\"seq\": 186,\"uid\": 54541,\"ouid\": [51749],\"rng\": [2.896]}";
    // char* *message = "{"utime": 14450645,"seq": 186,"uid": 54541,"ouid": [51749],"rng": [2.896]}"};
    char* message = TX_Data;
    
    // char* str = TX_Data;
    // int len = strlen(str);
    // char* new_str = (char*) malloc(len + 1);
    // if (new_str == NULL) {
    //     printf("Memory allocation failed\n");
    //     exit(1);
    // }
    // int j = 0;
    // for (int i = 0; i < len; i++) {
    //     if (str[i] != '"') {
    //         new_str[j++] = str[i];
    //     }
    // }
    // new_str[j] = '\0';

    // message = TX_Data;


    // printf("%s\n\n\n\n",message);

    // printf("%s\n\n\n\n",TX_Data);       // This is a test to see if I can print the location data from nrng_encode.c, here in main.c. Tis a success!

    

#if MYNEWT_VAL(UWB_TRANSPORT_ROLE) == 1
    dpl_callout_init(&stream_callout, dpl_eventq_dflt_get(), stream_timer, uwb_transport);
    dpl_callout_reset(&stream_callout, DPL_TICKS_PER_SEC);

    // Nick's Battery stuff:            Need to play around with this
    dpl_callout_init(&fuel_gauge_callout, dpl_eventq_dflt_get(), fuel_gauge_data_fetch_cb, uwb_transport);
    dpl_callout_reset(&fuel_gauge_callout, DPL_TICKS_PER_SEC);

#endif

    while (1) {
        dpl_eventq_run(dpl_eventq_dflt_get());
    }
    assert(0);
    return rc;
}
