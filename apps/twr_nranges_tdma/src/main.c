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
#include "hal/hal_gpio.h"
#include "hal/hal_bsp.h"
#include "imgmgr/imgmgr.h"

#include <uwb/uwb.h>
#include <uwb/uwb_mac.h>
#include "uwbcfg/uwbcfg.h"
#include <config/config.h>
#include <tdma/tdma.h>

#include <uwb_ccp/uwb_ccp.h>
#include <nrng/nrng.h>
#if MYNEWT_VAL(TIMESCALE)
#include <timescale/timescale.h>
#endif
#if MYNEWT_VAL(UWB_WCS_ENABLED)     // WCS = wireless clock synchronization
#include <uwb_wcs/uwb_wcs.h>
#endif
#if MYNEWT_VAL(SURVEY_ENABLED)
#include <survey/survey.h>
#endif
#if MYNEWT_VAL(NMGR_UWB_ENABLED)
#include <nmgr_uwb/nmgr_uwb.h>
#endif
#if MYNEWT_VAL(BLEPRPH_ENABLED)
#include "bleprph/bleprph.h"
#endif
#if MYNEWT_VAL(UWB_PAN_ENABLED)
#include <uwb_pan/uwb_pan.h>
#include <panmaster/panmaster.h>
#include <bootutil/image.h>

#endif
/*
The first part, starting with the declaration of the static variable "uwb_config_updated", defines a callback function "uwb_config_updated_cb()" that is triggered when there is an update to the UWB (Ultra-Wideband) configuration. This function is intended as a workaround in case the system is stuck waiting for a Clock Calibration Packet (CCP) with the wrong radio settings. It starts by looking up the device information in the "udev" variable, and then it looks up the Clock Calibration Packet (CCP) instance in the "ccp" variable.
The function then checks if there are no CCP semaphores by calling "dpl_sem_get_count(&ccp->sem)" and if there are none, it turns off the transceiver with "uwb_phy_forcetrxoff(udev)", configures the MAC layer with "uwb_mac_config(udev, NULL)", configures the transmitter with "uwb_txrf_config(udev, &udev->config.txrf)", and activates reception mode (rx) with "uwb_start_rx(udev)".
If there are CCP semaphores, the function sets the "uwb_config_updated" variable to true, and returns 0.
*/
static bool uwb_config_updated = false;             // Flag to indicate whether the UWB configuration has been updated.
int uwb_config_updated_cb()
{
    /* Workaround in case we're stuck waiting for ccp with the wrong radio settings */
    struct uwb_dev * udev = uwb_dev_idx_lookup(0);  // udev holds all the information about the device itself
                                                    // Likely used to look up a UWB device by its index. Arg 0 is likely used to refer to the first device.

    struct uwb_ccp_instance *ccp = (struct uwb_ccp_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_CCP);    // CCP = Clock Calibration Packet
                                                    // Finds the first instance pointer to the callback structure setup with a specific id(for this case it's UWBEXT_CCP).

    if (dpl_sem_get_count(&ccp->sem) == 0) {        // Checks if there are no CCP semaphores
        uwb_phy_forcetrxoff(udev);                  // Turns off transceiver
        uwb_mac_config(udev, NULL);                 // Configure MAC layer, it uses NULL for the uwb_dev_config for some reason
        uwb_txrf_config(udev, &udev->config.txrf);  // configs transmitter, includes power and pulse generator delay, pointer points to data structure that that holds all configurable items
        uwb_start_rx(udev);                         // Activate reception mode (rx).
        return 0;
    }

    uwb_config_updated = true;                      // It seems like every time the configs are updated, this variable gets set to true
    return 0;
}
// Register callback for UWB configuration changes
struct uwbcfg_cbs uwb_cb = {                        // This block of code seems to appear in every app. I can't figure out why. Nevermind, look at the comment below.
    .uc_update = uwb_config_updated_cb              // Register callback for UWB configuration changes
};

/*
"nrng_complete_cb", which is a callback function that gets triggered when a "dpl_event" (Decawave Porting Layer event) occurs. The function starts by asserting that the input "ev" is not NULL and that the argument of the event is not NULL. It then toggles the state of the blue LED on the device. It then assigns the "nrng" variable to the nrng_instance struct that is passed as the argument of the dpl_event. It also assigns the variable "frame" to a specific element of the "frames" array of the nrng_instance struct.
The function then has some code inside a preprocessor directive "#ifdef VERBOSE" which is only executed if the preprocessor symbol "VERBOSE" is defined. This code is only there for debugging purposes and prints out various error messages if certain conditions are met.
The last step in the function is to check if the code of the "frame" variable is equal to either UWB_DATA_CODE_DS_TWR_NRNG_FINAL or UWB_DATA_CODE_DS_TWR_NRNG_EXT_FINAL, if so the code of the frame variable is set to UWB_DATA_CODE_DS_TWR_NRNG_END.
*/


/**
 * @brief 
 * 
 * @param ev  
 */
static void nrng_complete_cb(struct dpl_event *ev) {// DPL = Decawave Porting Layer
    struct uwb_dev * inst = uwb_dev_idx_lookup(0);  
    assert(ev != NULL);                             // Checks if event and event argument is NOT NULL
    assert(dpl_event_get_arg(ev) != NULL);

    hal_gpio_toggle(LED_BLINK_PIN);                 // Toggle blue LED

    struct nrng_instance * nrng = (struct nrng_instance *) dpl_event_get_arg(ev);
    nrng_frame_t * frame = nrng->frames[(nrng->idx)%nrng->nframes];

// #ifdef VERBOSE                                      // If VERBOSE enabled, prints out more info for debugging errors
    if (inst->status.start_rx_error)
        printf("{\"utime\": %lu,\"timer_ev_cb\": \"start_rx_error\"}\n",os_cputime_ticks_to_usecs(os_cputime_get32()));
    if (inst->status.start_tx_error)
        printf("{\"utime\": %lu,\"timer_ev_cb\":\"start_tx_error\"}\n",os_cputime_ticks_to_usecs(os_cputime_get32()));
    if (inst->status.rx_error)
        printf("{\"utime\": %lu,\"timer_ev_cb\":\"rx_error\"}\n",os_cputime_ticks_to_usecs(os_cputime_get32()));
    if (inst->status.rx_timeout_error)
        printf("{\"utime\": %lu,\"timer_ev_cb\":\"rx_timeout_error\"}\n",os_cputime_ticks_to_usecs(os_cputime_get32()));
// #endif

    if (frame->code == UWB_DATA_CODE_DS_TWR_NRNG_FINAL || frame->code == UWB_DATA_CODE_DS_TWR_NRNG_EXT_FINAL){
        frame->code = UWB_DATA_CODE_DS_TWR_NRNG_END;// Checks the frame type, if a final frame (either extended type or regular), frame type is changed to END type. Looks like it ony applies is double sided (DS) twr is enabled
    }
}

/*
Defines a static variable called "nrng_complete_event" of type "struct dpl_event" and a function called "complete_cb" that takes in two arguments of type "struct uwb_dev *" and "struct uwb_mac_interface *". The function checks if the "fctrl" field of the "uwb_dev" struct is equal to "FCNTL_IEEE_RANGE_16", if so, it puts the "nrng_complete_event" into the default event queue using the "dpl_eventq_put" function and returns true. If the "fctrl" field is not equal to "FCNTL_IEEE_RANGE_16", the function returns false.
*/
static struct dpl_event nrng_complete_event;
static bool complete_cb(struct uwb_dev * inst, struct uwb_mac_interface * cbs)
{
    if(inst->fctrl != FCNTL_IEEE_RANGE_16){         // Checks if received frame is an IEEE range frame
        return false;
    }
    dpl_eventq_put(dpl_eventq_dflt_get(), &nrng_complete_event);
    return true;                                    // If true, puts the "nrng_complete_event" into the default event queue
}

/*!
 * @fn slot_timer_cb(struct os_event * ev)
 *
 * @brief In this example this timer callback is used to start_rx.
 * This code is a callback function that gets called when a TDMA slot event occurs. It is intended to be used in a TDMA-based protocol for wireless communication.
 * The function starts by casting the event argument to a pointer to a tdma_slot_t struct, and then uses this struct to access information about the TDMA instance and the UWB device instance. It then checks various conditions, such as if the UWB device's role is an anchor or a tag and if the current idx is greater than 6 and less than the total number of slots minus 6 and is divisible by 4, and based on these conditions, it performs different operations.
 * Some of the operations performed include configuring the UWB device and its PHY and TXRF settings, processing the transmission queue for the nmgr_uwb_instance, starting ranging operations, and sending range requests to other devices. The function also includes debug output for certain conditions, such as if a transmission error occurs.
 *
 * input parameters
 * @param inst - struct os_event *
 *
 * output parameters
 *
 * returns none
 */
static void slot_cb(struct dpl_event * ev){     // ev = os_event = dpl_event (dpl = Decawave Porting Layer)
    assert(ev);                     // Break if event == NULL

    tdma_slot_t * slot = (tdma_slot_t *) dpl_event_get_arg(ev);     // dpl_event_get_arg takes in os_event(same as dpl_event) and returns the os_event's argument to pass to the event queue callback
                                                                    // so slot = event callback argument casted to type tdma_slot_t
    tdma_instance_t * tdma = slot->parent;                          // tdma = slot's parent (type tdma_instance_t)

    struct uwb_ccp_instance *ccp = tdma->ccp;                       // ccp = tdma_instance_t(tdma)->ccp instance (since uwb ccp is enabled)
                                                                    // AKA ccp = this tdma's ccp instance
    struct uwb_dev * udev = tdma->dev_inst;                         // udev = this tdma's uwb device instance
    uint16_t idx = slot->idx;                                       // idx = this tdma_slot_t's slot number
    struct nrng_instance *nrng = (struct nrng_instance *)slot->arg; // nrng = this tdma_slot_t's optional argument, which in this case is an nrng_instance

    /* Avoid colliding with the ccp in case we've got out of sync */
    if (dpl_sem_get_count(&ccp->sem) == 0) {
        return;
    }

    /* Update config if needed */
    if (uwb_config_updated) {                                       // If config has been updated:
        uwb_config_updated = false;                                 // Set to false
        uwb_phy_forcetrxoff(udev);                                  // Force the transceiver to turn off 
        uwb_mac_config(udev, NULL);                                 // Configure the MAC layer of the UWB Device. udev is the pointer to the device, the "NULL" argument is probably used as a placeholder for some reason.
        uwb_txrf_config(udev, &udev->config.txrf);                  // configure the transmitter of the UWB device,  sets the power level and pulse generator delay for the transmitter, and the "&udev->config.txrf" argument is likely a pointer to a struct that holds all the configurable items for the transmitter.
        return;
    }

    if (ccp->local_epoch==0 || udev->slot_id == 0xffff) return; // If ccp's epoch==0 AND slot ID is all 1s, return

    /* Process any newtmgr packages queued up */
    if (idx > 6 && idx < (tdma->nslots-6) && (idx%4)==0) {      // if tdma slot # is greater than 6 AND less than the (total slots - 6) AND divisible by 4:
        nmgr_uwb_instance_t *nmgruwb = (nmgr_uwb_instance_t *)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_NMGR_UWB);
                                                                // Likely used to find a specific callback instance pointer which is likely related to the newtmgr package queued up

        assert(nmgruwb);                                        // End if newt mgr instance is NULL
        
        if (uwb_nmgr_process_tx_queue(nmgruwb, tdma_tx_slot_start(tdma, idx))) {
            return;
        }
    }


    
    if (udev->role&UWB_ROLE_ANCHOR) {                                   // ONLY ANCHORS run this code
        /* Listen for a ranging tag */
        uwb_set_delay_start(udev, tdma_rx_slot_start(tdma, idx));       // Specify a time in future to turn on the receiver
                                                                        // Second parameter is the delayed send/recieve time, in dwt timeunits = UWB microseconds * 65535

        uint16_t timeout = uwb_phy_frame_duration(udev, sizeof(nrng_request_frame_t))   // Calculate the frame duration (airtime) in usecs (not uwb usecs)
            + nrng->config.rx_timeout_delay;                                            // timeout = frame duration + receive response timeout

        /* Padded timeout to allow us to receive any nmgr packets too */
        uwb_set_rx_timeout(udev, timeout + 0x1000);                     // Indicates how long the receiver remains on from the RX enable command. The time parameter used here is in 1.0256 * us (512/499.2MHz) units. If set to 0 the timeout is disabled.
                                                                        // When using .rxauto_enable feature it is important to understand the role of rx_timeout, in this situation it is the timeout that actually turns-off the receiver and returns the transeiver to the idle state. NOTE: On dw1000 the timeout is a 16bit field only.

        nrng_listen(nrng, UWB_BLOCKING);                                // Initialise range request and start blocking


    } else { // If device is NOT an ANCHOR
        /* Range with the anchors */
        if (idx%MYNEWT_VAL(NRNG_NTAGS) != udev->slot_id) {              // NRNG_NTAGS = Max number of tags to allow in slots | slot_id =  Assigned slot_id
            return;                                                     // Checks if current slot index (idx) % max # of tags != the device's slot id
        }                                                               // If this is not the right slot index for the current device, do NOT attempt to range

        /* Range with the anchors */
        uint64_t dx_time = tdma_tx_slot_start(tdma, idx) & 0xFFFFFFFFFE00UL; // dx_time=Delay before starting TX, in dwt timeunits (uwb usecs << 16).
                                                                        // Calculates rx time using bitwise AND operation to clear some of the lower bits of the start time
        uint32_t slot_mask = 0;
        for (uint16_t i = MYNEWT_VAL(NODE_START_SLOT_ID);               // Creates slot mask variable then sets bits corresponding to slot range
             i <= MYNEWT_VAL(NODE_END_SLOT_ID); i++) {                  // given from SYSCFG.YML! 
            slot_mask |= 1UL << i;
        }

        if(nrng_request_delay_start(                                    // Start transmission after delay (dx_time)
               nrng, UWB_BROADCAST_ADDRESS, dx_time,
               UWB_DATA_CODE_SS_TWR_NRNG, slot_mask, 0).start_tx_error) {
            uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
            printf("{\"utime\": %lu,\"msg\": \"slot_timer_cb_%d:start_tx_error\"}\n",
                   utime,idx);                                          // If the function returns a "start_tx_error", it prints an error message to the console.
        }
    }
}


/*
This code defines a callback function pan_complete_cb() that is called when a PAN (personal area network) operation is completed. The function takes a single argument, a pointer to a dpl_event structure. The code uses the dpl_event_get_arg() function to retrieve the argument passed to the event, which is expected to be a pointer to a uwb_pan_instance structure.
The function then checks the slot_id field of the uwb_dev structure that is embedded inside the uwb_pan_instance to see if it is equal to 0xffff. If it is, the function does nothing. If it is not, the function uses the printf() function to print two messages to the console. The first message is a JSON string that contains the current time in microseconds, as well as the value of the slot_id field. The second message is also a JSON string that contains the current time in microseconds, as well as the value of the device's short address(euid16). It's likely that this function is used for logging or debugging purposes.
*/
static void pan_complete_cb(struct dpl_event * ev)
{
    assert(ev != NULL);                                                 // Verify event and event argument are both not NULL
    assert(dpl_event_get_arg(ev) != NULL);
    struct uwb_pan_instance *pan = (struct uwb_pan_instance*) dpl_event_get_arg(ev);

    if (pan->dev_inst->slot_id != 0xffff) {
        uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
        printf("{\"utime\": %lu,\"msg\": \"slot_id = %d\"}\n", utime, pan->dev_inst->slot_id);
        printf("{\"utime\": %lu,\"msg\": \"euid16 = 0x%X\"}\n", utime, pan->dev_inst->my_short_address);
    }
}

/* This function allows the ccp to compensate for the time of flight
 * from the master anchor to the current anchor.
 * Ideally this should use a map generated and make use of the euid in case
 * the ccp packet is relayed through another node.
 */
static uint32_t tof_comp_cb(uint16_t short_addr)
{
    float x = MYNEWT_VAL(UWB_CCP_TOF_COMP_LOCATION_X);
    float y = MYNEWT_VAL(UWB_CCP_TOF_COMP_LOCATION_Y);
    float z = MYNEWT_VAL(UWB_CCP_TOF_COMP_LOCATION_Z);
    float dist_in_meters = sqrtf(x*x+y*y+z*z);
#ifdef VERBOSE
    printf("d=%dm, %ld dwunits\n", (int)dist_in_meters,
           (uint32_t)(dist_in_meters/uwb_rng_tof_to_meters(1.0)));
#endif
    return dist_in_meters/uwb_rng_tof_to_meters(1.0);
}



// Main
int main(int argc, char **argv){
    int rc;

    sysinit();
    uwbcfg_register(&uwb_cb);
    conf_load();

    hal_gpio_init_out(LED_BLINK_PIN, 0);    // Blue
    hal_gpio_init_out(LED_1, 1);            // Green
    hal_gpio_init_out(LED_3, 1);            // Red

    struct uwb_dev * udev = uwb_dev_idx_lookup(0);              // Grab device instance, assign to udev
    udev->config.rxauto_enable = false;                         // Turn of rx auto enable
    udev->config.dblbuffon_enabled = false;                     // disable double buffer in device settings
    uwb_set_dblrxbuff(udev, udev->config.dblbuffon_enabled);    // Applies double buffer disabled setting

    struct nrng_instance* nrng = (struct nrng_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_NRNG);
    assert(nrng);   // this code initializes a pointer to a struct and makes sure that the returned pointer points to a valid location in the memory before proceeding with the code.

    dpl_event_init(&nrng_complete_event, nrng_complete_cb, nrng);// Initializes dpl event with inputs: dpl_event, dpl_event_fn, and an argument, nrng (nrng_instance type)

    //This code is initializing a struct uwb_mac_interface called "cbs" with the id UWBEXT_APP0, a pointer to the instance "nrng", and a callback function "complete_cb". Then it is calling the function "uwb_mac_append_interface" with the "udev" device and the "cbs" struct as arguments. This function probably adds the "cbs" struct to the list of interfaces associated with the "udev" device.
    struct uwb_mac_interface cbs = (struct uwb_mac_interface){  //! Structure of extension callbacks structure common for mac layer.
        .id = UWBEXT_APP0,                                      //!< Identifier
        .inst_ptr = nrng,                                       //!< Pointer to instance owning this interface
        .complete_cb = complete_cb                              //!< Completion event interface callback
    };

    uwb_mac_append_interface(udev, &cbs);                       // Adds cdbs struct to list of interfaces associated with device "udev"
    udev->slot_id = 0xffff;                                     // Changes this device's slot_id to 0xffff, I'm not sure why

#if MYNEWT_VAL(BLEPRPH_ENABLED)
    ble_init(udev->euid);                                       // initializes the BLE stack if the BLE peripheral is enabled in the MYNEWT_VAL configuration.
#endif
    // Creates ccp, pan and rng structs then ensures instances are present and correctly initialized via assert statements
    struct uwb_ccp_instance *ccp = (struct uwb_ccp_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_CCP);
    assert(ccp);
    struct uwb_pan_instance *pan = (struct uwb_pan_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_PAN);
    assert(pan);
    struct uwb_rng_instance* rng = (struct uwb_rng_instance*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_RNG);
    assert(rng);

    if (udev->role&UWB_ROLE_CCP_MASTER) {                       // If device is master node (anchor), it starts as the ccp clock master
        /* Start as clock-master */                             // API to start clock calibration packets (CCP) blinks with a pulse repetition period of MYNEWT_VAL(UWB_CCP_PERIOD).
        uwb_ccp_start(ccp, CCP_ROLE_MASTER);
    } else {
        uwb_ccp_start(ccp, CCP_ROLE_SLAVE);                     // If slave anchor or tag, start as clock slave
        uwb_ccp_set_tof_comp_cb(ccp, tof_comp_cb);              // Sets the CB that estimate the tof in dw units to the node with euid provided as paramater. Used to compensate for the tof from the clock source
    }

    if (udev->role&UWB_ROLE_PAN_MASTER) {
        /* As pan-master, first lookup our address and slot_id */
        struct image_version fw_ver;
        struct panmaster_node *node;

        panmaster_idx_find_node(udev->euid, NETWORK_ROLE_ANCHOR, &node);
        assert(node);                                           // I think this might check if the panmaster is seen as an anchor and asserts if that's true

        imgr_my_version(&fw_ver);                               // Returns version number of current image (if available)
        node->fw_ver.iv_major = fw_ver.iv_major;                // Then assigns all firmware version data to the node's struct
        node->fw_ver.iv_minor = fw_ver.iv_minor;
        node->fw_ver.iv_revision = fw_ver.iv_revision;
        node->fw_ver.iv_build_num = fw_ver.iv_build_num;

        udev->my_short_address = node->addr;                    // Assign short address to pan_master node struct element, addr
        udev->slot_id = node->slot_id;                          // Assign slot ID so corresponding pan_master node slot ID
        panmaster_postprocess();
        uwb_pan_start(pan, UWB_PAN_ROLE_MASTER, NETWORK_ROLE_ANCHOR);
        // ^^ A Personal Area Network blink is a discovery phase in which a TAG/ANCHOR seeks to discover an available PAN Master. The pan_master does not need to call this function.

    } else {    // If NOT the master anchor/node:
        uwb_pan_set_postprocess(pan, pan_complete_cb);
        network_role_t role = (udev->role&UWB_ROLE_ANCHOR)?     // Assign NETWORK role as anchor or tag
            NETWORK_ROLE_ANCHOR : NETWORK_ROLE_TAG;
        uwb_pan_start(pan, UWB_PAN_ROLE_RELAY, role);           // Start pan as pan relay, not master (or slave) for some reason
    }

    uint32_t utime = os_cputime_ticks_to_usecs(os_cputime_get32());
    printf("{\"utime\": %lu,\"exec\": \"%s\"}\n",utime,__FILE__);
    printf("{\"device_id\":\"%lX\"",udev->device_id);
    printf(",\"panid\":\"%X\"",udev->pan_id);
    printf(",\"addr\":\"%X\"",udev->uid);
    printf(",\"part_id\":\"%lX\"",(uint32_t)(udev->euid&0xffffffff));
    printf(",\"lot_id\":\"%lX\"}\n",(uint32_t)(udev->euid>>32));
    printf("{\"utime\": %lu,\"msg\": \"frame_duration = %d usec\"}\n",utime, uwb_phy_frame_duration(udev, sizeof(twr_frame_final_t)));
    printf("{\"utime\": %lu,\"msg\": \"SHR_duration = %d usec\"}\n",utime, uwb_phy_SHR_duration(udev));
    printf("{\"utime\": %lu,\"msg\": \"holdoff = %d usec\"}\n",utime,(uint16_t)ceilf(uwb_dwt_usecs_to_usecs(rng->config.tx_holdoff_delay)));

    /* Pan is slots 1&2 */
    tdma_instance_t * tdma = (tdma_instance_t*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_TDMA);
    assert(tdma);
    tdma_assign_slot(tdma, uwb_pan_slot_timer_cb, 1, (void*)pan);
    tdma_assign_slot(tdma, uwb_pan_slot_timer_cb, 2, (void*)pan);

#if MYNEWT_VAL(SURVEY_ENABLED)
    survey_instance_t *survey = (survey_instance_t*)uwb_mac_find_cb_inst_ptr(udev, UWBEXT_SURVEY);

    tdma_assign_slot(tdma, survey_slot_range_cb, MYNEWT_VAL(SURVEY_RANGE_SLOT), (void*)survey);
    tdma_assign_slot(tdma, survey_slot_broadcast_cb, MYNEWT_VAL(SURVEY_BROADCAST_SLOT), (void*)survey);
    for (uint16_t i = 6; i < MYNEWT_VAL(TDMA_NSLOTS); i++)
#else
    for (uint16_t i = 3; i < MYNEWT_VAL(TDMA_NSLOTS); i++)
#endif
        tdma_assign_slot(tdma, slot_cb, i, (void*)nrng);

    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }

    assert(0);
    return rc;
}
