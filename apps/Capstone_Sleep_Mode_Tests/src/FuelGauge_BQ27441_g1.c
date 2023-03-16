/**
 * @file FuelGauge_BQ27441_g1.c
 * @author Nick Goralka (NickGoralka@gmail.com)
 * @brief Driver for the BQ27441_g1 Fuel Guage
 * @version 0.3
 * @date 2023-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>

#include "FuelGauge_BQ27441_g1.h"

// Allow the C code to be compatible with a C++ project if need be
#ifdef __cplusplus 
extern "C" {
#endif

/***************************************************************************************************
 * Utility Functions
 **************************************************************************************************/

uint16_t read_control_function(FuelGauge_BQ27441_g1_t* fuel_gauge, uint16_t control_func)
{
    uint8_t write_buffer[2];
    uint8_t read_buffer[2] = {0, 0};


    write_buffer[0]  = BQ27441_G1_CONTROL_CMD;
    write_buffer[1]  = (uint8_t) (control_func & 0x00FF);
    write_buffer[2]  = (uint8_t) (control_func >> 8);

    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 3, write_buffer, STOP);
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, write_buffer, STOP);
    fuel_gauge->i2c_read_bytes(BQ27441_G1_ADDR, 2, read_buffer, STOP);

    return (((uint16_t) read_buffer[1] << 8)  | read_buffer[0]);
}

void execute_control_function(FuelGauge_BQ27441_g1_t* fuel_gauge, uint16_t control_func)
{
    uint8_t write_buffer[2];

    write_buffer[0]  = (uint8_t) (control_func & 0x00FF);
    write_buffer[1]  = (uint8_t) (control_func >> 8);

    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 2, write_buffer, STOP);
}

uint16_t read_standard(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t regAddr)
{
    uint8_t buffer[2];
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, &regAddr, NO_STOP);  
    fuel_gauge->i2c_read_bytes(BQ27441_G1_ADDR, 2, buffer, STOP);
    return ((uint16_t) buffer[1] << 8) | buffer[0];
}

flags_BQ27441_g1_t parse_flags (uint16_t regVal)
{
    flags_BQ27441_g1_t flags;

    // LOW BYTE
    flags.discharge           = (regVal & 0x01);
    flags.below_socf_thresh   = (regVal & 0x02) >> 1;
    flags.below_soc1_thresh   = (regVal & 0x04) >> 2;
    flags.battery_detected    = (regVal & 0x08) >> 3;
    flags.config_update_mode  = (regVal & 0x10) >> 4;
    flags.it_por              = (regVal & 0x20) >> 5;
    flags.ocv_taken           = (regVal & 0x80) >> 7;

    // HIGH BYTE
    flags.fast_charge         = (regVal & 0x100) >> 8;
    flags.full_charge         = (regVal & 0x200) >> 9;
    flags.under_temperature   = (regVal & 0x4000) >> 14;
    flags.over_temperature    = (regVal & 0x8000) >> 15;

    return flags;
}

op_config_BQ27441_g1_t parse_op_config (uint16_t regValue)
{
    op_config_BQ27441_g1_t config;

    // LOW BYTE
    config.temp_source         = (regValue & 0x01);
    config.bat_low_en          = (regValue & 0x04) >> 2;
    config.rmfcc               = (regValue & 0x10) >> 4;
    config.sleep               = (regValue & 0x20) >> 5;

    // HIGH BYTE
    config.gpio_pol                 = (regValue & 0x800) >> 11;
    config.bi_pu_en                 = (regValue & 0x1000) >> 12;
    config.battery_insert_enable    = (regValue & 0x2000) >> 13;
}

uint16_t encode_op_config (op_config_BQ27441_g1_t config)
{
    uint16_t encoded = 0x0000;

    // LOW BYTE
    encoded |= (config.temp_source);
    encoded |= (config.bat_low_en << 2);
    encoded |= (config.rmfcc << 4);
    encoded |= (config.sleep << 5);

    // HIGH BYTE
    encoded |= (config.gpio_pol << 11);
    encoded |= (config.bi_pu_en << 12);
    encoded |= (config.battery_insert_enable << 13);

    return encoded;

}

control_status_BQ27441_g1_t parse_control_status(uint16_t regValue)
{
    control_status_BQ27441_g1_t status;

    // LOW BYTE
    status.vok                                = (regValue & 0x2) >> 1;
    status.rup_dis                            = (regValue & 0x4) >> 2;
    status.ldmd                               = (regValue & 0x8) >> 3;
    status.sleep                              = (regValue & 0x10) >> 4;
    status.hibernate                          = (regValue & 0x40) >> 6;
    status.initcomp                           = (regValue & 0x80) >> 7;


    // HIGH BYTE
    status.res_up                             = (regValue & 0x100) >> 8;
    status.qmax_up                            = (regValue & 0x200) >> 9;
    status.bca                                = (regValue & 0x400) >> 10;
    status.cca                                = (regValue & 0x800) >> 11;
    status.calmode                            = (regValue & 0x1000) >> 12;
    status.ss                                 = (regValue & 0x2000) >> 13;
    status.wdreset                            = (regValue & 0x4000) >> 14;
    status.shutdownen                         = (regValue & 0x8000) >> 15; 
}

/***************************************************************************************************
 * Standard Commands
 **************************************************************************************************/

uint16_t get_temperature_K_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_TEMPERATURE_CMD);
}

float get_temperature_C_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint16_t temp_centi_kelvin = get_temperature_K_BQ27441_g1(fuel_gauge);
    return centikelvin_to_celsius(temp_centi_kelvin);
}

uint16_t get_voltage_mV_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_VOLTAGE_CMD);
}

flags_BQ27441_g1_t get_flags_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint16_t flags = read_standard(fuel_gauge, BQ27441_G1_FLAGS_CMD);
    return parse_flags(flags);
}

uint16_t get_nominal_available_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_NOMINAL_AVALIABLE_CAPACITY_CMD);
}

uint16_t get_full_available_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gague)
{
    return read_standard(fuel_gague, BQ27441_G1_FULL_AVALIABLE_CAPACITY_CMD);
}

uint16_t get_remaining_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_REMAINING_CAPACITY_CMD);
}

uint16_t get_full_charge_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_FULL_CHARGE_CAPACITY_CMD);
}

int16_t get_average_current_mA_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return (int16_t) read_standard(fuel_gauge, BQ27441_G1_AVERAGE_CURRENT_CMD);
}

int16_t get_standby_current_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return (int16_t) read_standard(fuel_gauge, BQ27441_G1_STANDBY_CURRENT_CMD);
}

int16_t get_max_load_current_mA_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return (int16_t) read_standard(fuel_gauge, BQ27441_G1_MAX_LOAD_CURRENT_CMD);
}

int16_t get_average_power_mW_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return (int16_t) read_standard(fuel_gauge, BQ27441_G1_AVERAGE_POWER_CMD);
}

uint16_t get_state_of_charge_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_STATE_OF_CHARGE_CMD);
}

uint16_t get_state_of_health_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_STATE_OF_HEALTH_CMD);
}

uint16_t get_state_of_health_status_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_STATE_OF_HEALTH_STATUS_CMD);
}

uint16_t get_remaining_capacity_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_REMAINING_CAPACITY_UNFILTERED_CMD);
}

uint16_t get_remaining_capacity_filtered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_REMAINING_CAPACITY_FILTERED_CMD);
}

uint16_t get_full_charge_capacity_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_FULL_CHARGE_CAPACITY_UNFILTERED_CMD);
}

uint16_t get_full_charge_capacity_filtered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_FULL_CHARGE_CAPACITY_FILTERED_CMD);
}

uint16_t get_state_of_charge_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_STATE_OF_CHARGE_UNFILTERED_CMD);
}


/**********************************************************************************************************************
 * Control Subcommands
 *********************************************************************************************************************/

control_status_BQ27441_g1_t get_control_status_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint16_t status =  read_control_function(fuel_gauge, BQ27441_G1_CONTROL_STATUS_SUBCMD);
    return parse_control_status(status);
}

uint16_t get_device_type_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_control_function(fuel_gauge, BQ27441_G1_DEVICE_TYPE_SUBCMD);
}

uint16_t get_firmware_version_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_control_function(fuel_gauge,BQ27441_G1_FW_VERSION_SUBCMD);
}

uint16_t get_data_memory_code_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_control_function(fuel_gauge, BQ27441_G1_DM_CODE_SUBCMD);
}

uint16_t get_previous_mac_write_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_control_function(fuel_gauge, BQ27441_G1_PREV_MACWRITE_SUBCMD);
}

uint16_t get_chemical_id_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_control_function(fuel_gauge, BQ27441_G1_CHEM_ID_SUBCMD);
}

void battery_insert_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_BAT_INSERT_SUBCMD);
}

void battery_remove_BQ27441_G1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_BAT_REMOVE_SUBCMD);
}

void set_hibernate_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SET_HIBERNATE_SUBCMD);
}

void clear_hibernate_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_CLEAR_HIBERNATE_SUBCMD);
}

void set_config_update_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SET_CFGUPDATE_SUBCMD);
}

void set_shutdown_enable_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SHUTDOWN_ENABLE_SUBCMD);
}

void shutdown_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SHUTDOWN_SUBCMD);
}

void seal_device_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SEALED_SUBCMD);
}

void pulse_gpio_pin_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_TOGGLE_GPOUT_SUBCMD);
}

void reset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_RESET_SUBCMD);
}

void soft_reset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_SOFT_RESET_SUBCMD);
}

void exit_config_update_mode_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_EXIT_CFGUPDATE_SUBCMD);
}

void exit_config_update_mode_and_resim_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    execute_control_function(fuel_gauge, BQ27441_G1_EXIT_RESIM_SUBCMD);
}

/***********************************************************************************************************************
 * Extended Commands
 **********************************************************************************************************************/

op_config_BQ27441_g1_t get_op_config_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint16_t config = read_standard(fuel_gauge, BQ27441_G1_OP_CONFIG_CMD);
    return parse_op_config(config);
}

void write_op_config_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, op_config_BQ27441_g1_t config)
{
    uint16_t encoded_config = encode_op_config(config);

    uint8_t write_buffer [2];
    write_buffer[0] = ((uint8_t) encoded_config >> 8);
    write_buffer[1] = ((uint8_t) encoded_config & 0xFFFF);

    write_extended_data_BQ27441_g1_t(fuel_gauge, BQ27441_G1_BLOCK_DATA_CMD, 0, encode_op_config, 2);

}

uint16_t get_design_capacity_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    return read_standard(fuel_gauge, BQ27441_G1_DESIGN_CAPACITY_CMD);
}

void block_data_control_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint8_t enableByte = 0x00;

    uint8_t data = {BQ27441_G1_BLOCK_DATA_CONTROL_CMD, enableByte};
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, data, STOP);
}

void block_data_class_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t id)
{
    uint8_t data = {BQ27441_G1_DATA_CLASS_CMD, id};
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, data, STOP);
}

void block_data_offset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset)
{
    uint8_t data = {BQ27441_G1_BLOCK_DATA_CONTROL_CMD, offset};
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, data, STOP);
}

uint8_t get_block_data_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint8_t buff;
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD, NO_STOP);
    fuel_gauge->i2c_read_bytes(BQ27441_G1_ADDR, 1, &buff, STOP);
    return buff;
}

uint8_t read_block_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset)
{
    uint8_t ret;
    uint8_t addr = offset + BQ27441_G1_BLOCK_DATA_CMD;
    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, &addr, NO_STOP);
    fuel_gauge->i2c_read_bytes(BQ27441_G1_ADDR, 1, &ret, STOP);
    return ret;
}

void write_block_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset, uint8_t data)
{
    uint8_t addr = offset + BQ27441_G1_BLOCK_DATA_CMD;

    uint8_t write_buff[2] = {addr, data};

    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 2, write_buff, STOP);
}

uint8_t compute_block_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge)
{
    uint8_t data[32];

    uint8_t regAddr = BQ27441_G1_BLOCK_DATA_CMD;

    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 1, regAddr, NO_STOP);
    fuel_gauge->i2c_read_bytes(BQ27441_G1_ADDR, 32, data, STOP);

    uint8_t checksum = 0;
    for (int i = 0; i < 32; i++)
    {
        checksum += data[i];
    }

    checksum = 255 - checksum; 

    return checksum;

}

void write_block_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t csum)
{
    uint8_t write_buffer = { BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD, csum };

    fuel_gauge->i2c_write_bytes(BQ27441_G1_ADDR, 2, write_buffer, STOP);
}

uint8_t read_extended_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t classID, uint8_t offset)
{
    uint8_t retData = 0;

    // enter config mode
    set_config_update_BQ27441_g1_t(fuel_gauge);

    // enable block data memory control
    block_data_control_BQ27441_g1_t(false);

    // write class id 
    block_data_class_BQ27441_g1_t(fuel_gauge, classID);

    // write 32-bit block offset
    block_data_offset_BQ27441_g1_t(fuel_gauge, offset/32);

    // compute the checksum
    compute_block_checksum_BQ27441_g1_t(fuel_gauge);

    uint8_t old_check_sum = block_data_checksum_BQ27441_g1_t(fuel_gauge);

    retData = read_block_data_BQ27441_g1_t(fuel_gauge, offset % 32);

    exit_config_update_mode_BQ27441_g1_t(fuel_gauge);

    return retData;
    
}

void write_extended_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t classID, uint8_t offset, uint8_t* data, uint8_t len)
{
    // config mode
    set_config_update_BQ27441_g1_t(fuel_gauge);

    // enable block memory control 
    block_data_control_BQ27441_g1_t(fuel_gauge);

    // write class id 
    block_data_class_BQ27441_g1_t(fuel_gauge, classID);

    block_data_offset_BQ27441_g1_t(fuel_gauge, offset / 32);

    compute_block_checksum_BQ27441_g1_t(fuel_gauge);

    uint8_t old_checksum = compute_block_checksum_BQ27441_g1_t(fuel_gauge);

    for (int i = 0; i < len; i++)
    {
        write_block_data_BQ27441_g1_t(fuel_gauge, (offset % 32) + i, data[i]);
    }

    uint8_t new_checksum = compute_block_checksum_BQ27441_g1_t(fuel_gauge);
    write_block_checksum_BQ27441_g1_t(fuel_gauge, new_checksum);

    exit_config_update_mode_BQ27441_g1_t(fuel_gauge);

}

#ifdef __cplusplus 
}
#endif
