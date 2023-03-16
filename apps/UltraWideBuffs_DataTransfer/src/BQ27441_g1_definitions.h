/**
 * @file BQ27441_g1_definitions.h
 * @author Nick Goralka (NickGoralka@gmail.com)
 * @brief Definitions for BQ27441_G1 Driver
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Address of the BQ27441 on the I2C bus
 * @note see section 9.5.4.1 in the datasheet
 * 
 */
#define BQ27441_G1_ADDR									0x55

/**********************************************************************************************
 * Standard Commands
 *********************************************************************************************/
#define BQ27441_G1_CONTROL_CMD							0x00
#define BQ27441_G1_TEMPERATURE_CMD						     0x02
#define BQ27441_G1_VOLTAGE_CMD							0x04
#define BQ27441_G1_FLAGS_CMD							     0x06
#define BQ27441_G1_NOMINAL_AVALIABLE_CAPACITY_CMD		          0x08
#define BQ27441_G1_FULL_AVALIABLE_CAPACITY_CMD			     0x0A
#define BQ27441_G1_REMAINING_CAPACITY_CMD				     0x0C
#define BQ27441_G1_FULL_CHARGE_CAPACITY_CMD				     0x0E
#define BQ27441_G1_AVERAGE_CURRENT_CMD					     0x10
#define BQ27441_G1_STANDBY_CURRENT_CMD					     0x12
#define BQ27441_G1_MAX_LOAD_CURRENT_CMD					     0x14
#define BQ27441_G1_AVERAGE_POWER_CMD					     0x18
#define BQ27441_G1_STATE_OF_CHARGE_CMD					     0x1C
#define BQ27441_G1_INTERNAL_TEMPERATURE_CMD				     0x1E
#define BQ27441_G1_STATE_OF_HEALTH_CMD					     0x20
#define BQ27441_G1_STATE_OF_HEALTH_STATUS_CMD                    0x21
#define BQ27441_G1_REMAINING_CAPACITY_UNFILTERED_CMD	          0x28
#define BQ27441_G1_REMAINING_CAPACITY_FILTERED_CMD		     0x2A
#define BQ27441_G1_FULL_CHARGE_CAPACITY_UNFILTERED_CMD	          0x2C
#define BQ27441_G1_FULL_CHARGE_CAPACITY_FILTERED_CMD	          0x2E
#define BQ27441_G1_STATE_OF_CHARGE_UNFILTERED_CMD		          0x30


/**********************************************************************************************
 * Control Command Subcommands
 *********************************************************************************************/ 
#define BQ27441_G1_CONTROL_STATUS_SUBCMD				0x0000
#define BQ27441_G1_DEVICE_TYPE_SUBCMD					0x0001
#define BQ27441_G1_FW_VERSION_SUBCMD					0x0002
#define BQ27441_G1_DM_CODE_SUBCMD						0x0004
#define BQ27441_G1_PREV_MACWRITE_SUBCMD					0x0007
#define BQ27441_G1_CHEM_ID_SUBCMD						0x0008
#define BQ27441_G1_BAT_INSERT_SUBCMD					0x000C
#define BQ27441_G1_BAT_REMOVE_SUBCMD					0x000D
#define BQ27441_G1_SET_HIBERNATE_SUBCMD					0x0011
#define BQ27441_G1_CLEAR_HIBERNATE_SUBCMD				0x0012
#define BQ27441_G1_SET_CFGUPDATE_SUBCMD					0x0013
#define BQ27441_G1_SHUTDOWN_ENABLE_SUBCMD				0x001B
#define BQ27441_G1_SHUTDOWN_SUBCMD						0x001C
#define BQ27441_G1_SEALED_SUBCMD						0x0020 
#define BQ27441_G1_TOGGLE_GPOUT_SUBCMD					0x0023
#define BQ27441_G1_RESET_SUBCMD					     0x0041
#define BQ27441_G1_SOFT_RESET_SUBCMD					0x0042
#define BQ27441_G1_EXIT_CFGUPDATE_SUBCMD				0x0043
#define BQ27441_G1_EXIT_RESIM_SUBCMD					0x0044


/*********************************************************************************************
 * Extended Commands
 ********************************************************************************************/ 
#define  BQ27441_G1_OP_CONFIG_CMD						0x3A
#define  BQ27441_G1_DESIGN_CAPACITY_CMD					0x3C
#define  BQ27441_G1_DATA_CLASS_CMD						0x3E
#define  BQ27441_G1_DATA_BLOCK_CMD						0x3F
#define  BQ27441_G1_BLOCK_DATA_CMD						0x40
#define  BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD				0x60
#define  BQ27441_G1_BLOCK_DATA_CONTROL_CMD				0x61



/*********************************************************************************************
 * State of Health Prediction Statuses
 *********************************************************************************************/
#define BQ27441_G1_SOH_NOT_VALID                            0x00
#define BQ27441_G1_INSTANT_SOH_VALUE_READY                  0x01
#define BQ27441_G1_INITIAL_SOH_VALUE_READY                  0x02
#define BQ27441_G1_SOH_VALUE_READY                          0x03



/**********************************************************************************************
 * I2C Stop Bit
 *********************************************************************************************/
#define STOP    true
#define NO_STOP false
