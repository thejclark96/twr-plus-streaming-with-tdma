/**
 * @file FuelGauge_BQ27441_g1.h
 * @author Nick Goralka (NickGoralka@gmail.com)
 * @brief Driver for the BQ27441_g1 Fuel Gauge
 * @version 0.2
 * @date 2023-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 */

#include <inttypes.h>

#include "BQ27441_g1_definitions.h"

// Allow the C code to be compatible with a C++ project if need be
#ifdef __cplusplus 
extern "C" {
#endif


/**
 * @brief Typedef for function pointer to make code more readible
 * @note an function that meets this spec has the format of 
 * 
 * `void i2c_read/write (uint8_t addr, uint16_t buffer_len, uint8_t* buffer, bool stop);`
 *
 *      - addr [-] the address being writen to
 *      - buffer_len [-] number of bytes to be written/read 
 *      - buffer [-] pointer to buffer where to read/write to/from
 *      - stop 
 *           - STOP [-] throw a stop bit and end the transmission
 *           - NO_STOP [-] do not throw stop bit and keep transmission open
 * 
 * 
 */
typedef int (* i2c_func_ptr) (uint8_t, uint16_t, uint8_t*, bool);


/**
 * @brief Stucture that contains all of the attributes of the Fuel gauge object instance
 * 
 */
typedef struct 
{

    /**
     * @brief Pointer to the I2C read bytes implementation
     * @details This function pointer is implemented in order keep the
     * driver MCU/framework agnostic.
     * 
     * 
     * A I2C read multiple bytes function must be implemented in your specific framework/BSP and 
     * conform to the following semantics
     * 
     * 
     * `bool i2c_read_bytes (uint8_t addr, uint16_t buffer_len, uint8_t* buffer);`
     *
     *      - addr [-] the address being writen to
     *      - buffer_len [-] number of bytes to be read 
     *      - buffer [-] pointer to buffer where to write the data
     *      - stop 
     *           - STOP [-] throw a stop bit and end the transmission
     *           - NO_STOP [-] do not throw stop bit and keep transmission open
     * 
     *      - returns false if error was detected
     * 
     * @todo [-] documentation: Add diagram for something similar to 9.5.4.1 in the datasheet
     */
    i2c_func_ptr i2c_read_bytes;


    /**
     * @brief Pointer to the I2C write bytes implementation
     * @details This function pointer is implemented in order keep the
     * driver MCU/framework agnostic.
     * 
     * 
     * A I2C write multiple bytes function must be implemented in your specific framework/BSP and 
     * conform to the following semantics
     * 
     * 
     * `bool i2c_write_bytes (uint8_t addr, uint16_t buffer_len, uint8_t* buffer);`
     *
     *      - addr [-] the address being writen to
     *      - buffer_len [-] number of bytes to be writeen 
     *      - buffer [-] pointer to buffer where to read the data
     *      - stop 
     *           - STOP [-] throw a stop bit and end the transmission
     *           - NO_STOP [-] do not throw stop bit and keep transmission open
     * 
     * @todo [-] documentation: Add diagram for something similar to 9.5.4.1 in the datasheet
     */
    i2c_func_ptr i2c_write_bytes;
    

} FuelGauge_BQ27441_g1_t;


/**
 * @brief Stucture used to decode control status information 
 * 
 * @note Please see section 4.1.1 in the BQ27441-G1 Technical Reference Manual 
 * (https://www.ti.com/lit/ug/sluuac9a/sluuac9a.pdf?ts=1668356190482&ref_url=https%253A%252F%252Fduckduckgo.com%252F)
 * 
 */
typedef struct 
{
    /***************************************************************************************************
    * HIGH BYTE
    ***************************************************************************************************/ 

    /**
     * @brief Shutdown Enable
     * @details Indicates the fuel gauge has received the SHUTDOWN_ENABLE subcommand and is enabled for
     *   SHUTDOWN. Active when set
     * 
     */
	uint8_t shutdownen;

    /**
     * @brief Watchdog Resest
     * @details Indicates the fuel gauge has performed a Watchdog Reset. Active when set.
     */
	uint8_t wdreset;

    /**
     * @brief Sealed State
     * @details Indicates the fuel gauge is in the SEALED state. Active when set.
     * 
     */
	uint8_t ss;

    /**
     * @brief Calibration Mode
     * @details Indicates the fuel gauge is in calibration mode. Active when set.
     * 
     */
	uint8_t calmode;

    /**
     * @brief Coulomb Counter Auto-Calibrate
     * @details Indicates the fuel gauge Coulomb Counter Auto-Calibration routine is active. The CCA routine will take place
     * approximately 3 minutes and 45 seconds after the initialization as well as periodically as conditions permit.
     * Active when set
     */
	uint8_t cca;

    /**
     * @brief Board Calibration Active
     * @details Indicates the fuel gauge board calibration routine is active. Active when set
     * 
     */
	uint8_t bca;

    /**
     * @brief Max Charge has been updated
     * @details Indicates Qmax has updated. True when set. This bit is cleared after a POR or when the Flags() [BAT_DET]
bit is set. When this bit is cleared, it enables fast learning of battery Qmax
     */
	uint8_t qmax_up;

    /**
     * @brief Resitance Updated
     * @details Indicates that resistance has been updated. True when set. This bit is cleared after a POR or when the
     * Flags() [BAT_DET] bit is set. Also, this bit can only be set after Qmax is updated ([QMAX_UP] bit is set).
     * When this bit is cleared, it enables fast learning of battery impedance.
     */
	uint8_t res_up;

    /******************************************************************************************************************
     * LOW BYTE
     *****************************************************************************************************************/

    /**
     * @brief Initialization is Complete
     * @details Initialization completion bit indicating the initialization is complete. True when set
     * 
     */
	uint8_t initcomp;

    /**
     * @brief Hiberanate request has been made
     * @details Indicates a request for entry into HIBERNATE from SLEEP mode has been issued. True when set.
     * 
     */
	uint8_t hibernate;

    /**
     * @brief Device is in sleep mode
     * @details Indicates the fuel gauge is in SLEEP mode. True when set.
     * 
     */
	uint8_t sleep;

    /**
     * @brief Indicates the algorithm is using constant-power model. True when set. Default is 1
     * 
     */
	uint8_t ldmd;

    /**
     * @brief Indicates the fuel gauge Ra table updates are disabled. Updates are disabled when set.
     * 
     */
	uint8_t rup_dis;

    /**
     * @brief Indicates cell voltages are ok for Qmax updates. True when set.
     * 
     */
	uint8_t vok;
} control_status_BQ27441_g1_t;


/**
 * @brief Decoded Flags
 * @details Contents of the fuel gauging status register, depicting the current
 * operating status
 * 
 */
typedef struct {
     /***********************************************************************************************
      * HIGH BYTE
      ***********************************************************************************************/
     
     /**
      * @brief Over temperature condition detected
      * @details Set when Temperature() ≥ Over Temp (default = 55°C). [OT] is
      * cleared when Temperature() < Over Temp – Temp Hys.
      */
     uint8_t over_temperature;

     /**
      * @brief Under temperature condition detected
      * @details [UT] is set when Temperature() ≤ Under Temp (default = 0°C). [UT] is
      * cleared when Temperature() > Under Temp + Temp Hys
      */
     uint8_t under_temperature;

     /**
      * @brief Set when full charge detected
      * @details If the FC Set% is a positive threshold, [FC] is set when SOC ≥ FC Set % and is cleared
      * when SOC ≤ FC Clear % (default = 98%). By default, FC Set% = –1, therefore [FC] is set when the fuel gauge
      * has detected charge termination
      * 
      */
     uint8_t full_charge;

     /**
      * @brief Fast charging allowed
      * @details  If SOC changes from 98% to 99% during charging, the [CHG] bit is cleared. The [CHG]
      * bit will become set again when SOC ≤ 95%
      * 
      */
     uint8_t fast_charge;

     /***********************************************************************************************
      * LOW BYTE
      **********************************************************************************************/
     
     /**
      * @brief Cleared on entry to relax mode and set to 1 when OCV measurement is performed in relax mode.
      * 
      */
     uint8_t ocv_taken;

     /**
      * @brief Set when Power on Reset (POR) has occured.
      * @details If set, this bit generally indicates that the RAM
      * configuration registers have been reset to default values and the host should reload the configuration
      * parameters using the CONFIG UPDATE mode. This bit is cleared after the SOFT_RESET subcommand is
      * received.
      * 
      */
     uint8_t it_por;

     /**
      * @brief Set when in configuration update mode
      * @details Fuel gauge is in CONFIG UPDATE mode. True when set. Default is 0. 
      * 
      */
     uint8_t config_update_mode;

     /**
      * @brief Battery insertion detected
      * @details  True when set. When OpConfig [BIE] is set, [BAT_DET] is set by detecting a logic
      * high-to-low transition at the BIN pin. When OpConfig [BIE] is low, [BAT_DET] is set when host issues
      * BAT_INSERT subcommand and is cleared when host issues the BAT_REMOVE subcommand. Gauge
      * predictions are not valid unless [BAT_DET] is set.
      * 
      */
     uint8_t battery_detected;

     /**
      * @brief Set if below state of charge (SOC1) threshold
      * @details  If set, StateOfCharge() ≤ SOC1 Set Threshold. The [SOC1] bit will remain set until StateOfCharge() ≥ SOC1
      * Clear Threshold
      * 
      */
     uint8_t below_soc1_thresh;

     /**
      * @brief Set if below SOCF threshold
      * @details If set, StateOfCharge() ≤ SOCF Set Threshold. The [SOCF] bit will remain set until StateOfCharge() ≥ SOCF
      * Clear Threshold
      * 
      */
     uint8_t below_socf_thresh;

     /**
      * @brief Set when discharge is detected
      * 
      */
     uint8_t discharge;

} flags_BQ27441_g1_t;


/**
 * @brief Structure used to decode operation configuration register
 * @note Please see 6.4.1.5.1 in the technical reference manual
 */
typedef struct {

     /*******************************************************************************************************
      * HIGH BYTE
      ******************************************************************************************************/
     
     /**
      * @brief Battery insert enable
      * @details If set, the battery insertion is detected via the BIN pin input. If cleared, the
      * detection relies on the host to issue the BAT_INSERT subcommand to indicate battery presence in the
      * system
      */
     uint8_t battery_insert_enable;

     /**
      * @brief Battery insert enable
      * @details Enables internal weak pullup resistor on the BIN pin. True when set. If false, an external pullup resistor
      * is expected.
      * 
      */
     uint8_t bi_pu_en;

     /**
      * @brief Polarity of the GPIO pin
      * @details GPOUT pin is active-high if set or active-low if cleared
      * 
      */
     uint8_t gpio_pol;

     /*******************************************************************************************************
      * LOW BYTE
      ******************************************************************************************************/
     
     /**
      * @brief The fuel gauge can enter sleep, if operating conditions allow. True when set
      * 
      */
     uint8_t sleep;

     /**
      * @brief RM is updated with the value from FCC on valid charge termination. True when set
      * 
      */
     uint8_t rmfcc;

     /**
      * @brief If set, the BAT_LOW function for GPOUT pin is selected. If cleared, the SOC_INT function is selected
      * for GPOUT.
      * 
      */
     uint8_t bat_low_en;

     /**
      * @brief Selects the temperature source
      * @details  Enables the host to write Temperature() if set. If cleared, the internal
      * temperature sensor is used for Temperature
      * 
      */
     uint8_t temp_source;


} op_config_BQ27441_g1_t ;


/**********************************************************************************************************
 * Standard Command Functions
 *********************************************************************************************************/

/**
 * @brief Get the internal temperature of the sensor in units of 0.1°K
 * @details This read- and write-word function returns an unsigned integer value of the temperature in units of 0.1°K
 * measured by the fuel gauge. 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] temperature (0.1°K)
 */
uint16_t get_temperature_K_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the internal temperature of the sensor in units of Celsius
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return float [-] temperature (°C)
 */
float get_temperature_C_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the voltage of the cell pack (mV)
 * @details Measured cell-pack voltage in mV with a range of 0 to 6000 mV.
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] cell-pack voltage (mV)
 */
uint16_t get_voltage_mV_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the Flags
 *
 * @param fuel_Gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return flags_BQ27441_g1_t [-] contents of the fuel gauging status register, depicting the current
 * operating status
 */
flags_BQ27441_g1_t get_flags_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_Gauge);

/**
 * @brief Read the nominal available capacity (mAh)
 * @details Reads the uncompensated (less than C/20 load) battery capacity
 * remaining. Units are mAh
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] nominal available capacity (mAh)
 */
uint16_t get_nominal_available_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Reads the full available capacity (mAh)
 * @details Gets the uncompensated (less than C/20 load) capacity of the battery
 * when fully charged. FullAvailableCapacity() is updated at regular intervals.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] full remaining capacity (mAh)
 */
uint16_t get_full_available_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the remaining capacity (mAh)
 * @details Reads the remaining battery capacity compensated for load and temperature.
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] remaining capacity (mAh)
 */
uint16_t get_remaining_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the full charge capacity (mAh)
 * @details Reads compensated capacity of the battery when fully charged. 
 * FullChargeCapacity() is updated at regular intervals and is compensated for load and temperature
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] capacity of the battery when fully charged
 */
uint16_t get_full_charge_capacity_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the average current (mA)
 * @details Reads the average current flow through the
 * sense resistor. In NORMAL mode, it is updated once per second and is calculated by dividing the 1-
 * second change in coulomb counter data by 1 second. Large current spikes of short duration will be
 * averaged out in this measurement
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return int16_t [-] average current (mA)
 */
int16_t get_average_current_mA_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the standby current (mA)
 * 
 * @details This read-only function returns a signed integer value of the measured standby current through the sense
 * resistor. The StandbyCurrent() is an adaptive measurement. Initially, it reports the standby current
 * programmed in Initial Standby and, after spending several seconds in standby, reports the measured
 * standby current.
 * 
 * 
 * The register value is updated every second when the measured current is above the Deadband and is
 * less than or equal to 2 × Initial Standby. The first and last values that meet this criteria are not averaged
 * in, because they may not be stable values. To approximate a 1-minute time constant, each new
 * StandbyCurrent() value is computed by taking approximately 93% of the last measured standby current
 * and approximately 7% of the currently measured average current.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return int16_t [-] standby current (mA)
 */
int16_t get_standby_current_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the max load current (mA)
 * 
 * @details This read-only function returns a signed integer value, in units of mA, of the maximum load conditions.
 * The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load
 * current programmed in Initial MaxLoad current. If the measured current is greater than Initial MaxLoad,
 * then MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the
 * previous value and Initial MaxLoad whenever the battery is charged to full after a previous discharge to
 * an SOC less than 50%. This prevents the reported value from maintaining an unusually high value
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return int16_t [-] max load current (mA)
 */
int16_t get_max_load_current_mA_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the average power (mW)
 * 
 * @details Signed integer value of the average power during charging and
 * discharging of the battery. It is negative during discharge and positive during charge. A value of 0
 * indicates that the battery is not being discharged. The value is reported in units of mW
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return int16_t [-] average power (mW)
 */
int16_t get_average_power_mW_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Read predicted state of charge (%)
 * 
 * @details Get the predicted remaining battery capacity expressed as a percentage of FullChargeCapacity() with a range of 0 to 100%
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] predicted remaining battery capacity (%)
 */
uint16_t get_state_of_charge_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the state of health (%)
 * 
 * @details Gets the ratio of predicted FCC(25°C, SOH LoadI) over the DesignCapacity(). The FCC(25°C,
 * SOH LoadI) is the calculated FCC at 25°C and the SOH LoadI which is factory programmed (default =
 * –400 mA). The range of the returned SOH percentage is 0x00 to 0x64, indicating 0 to 100%,
 * correspondingly
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] SOH (%)
 */
uint16_t get_state_of_health_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the status of the state of health prediction
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] Status of the SOH prediction
 * 
 *          - BQ27441_G1_SOH_NOT_VALID  [-] not valid
 *          - BQ27441_G1_INSTANT_SOH_VALUE_READY  [-] instant SOH value ready
 *          - BQ27441_G1_INITIAL_SOH_VALUE_READY [-] initial SOH value ready
 *                   - Calculation based on default Qmax
 *                   - May not reflect SOH for currently inserted pack
 *          - BQ27441_G1_SOH_VALUE_READY 
 *                  - Calculation based on learned Qmax
 *                  - Most accurate SOH for currently inserted pack following a Qmax update
 */
uint16_t get_state_of_health_status_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the remaining unfiltered capacity (mAh)
 * 
 * @details Gets the true battery capacity remaining. This value can jump as the
 * gauge updates its predictions dynamically
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] remaining unfiltered capacity (mAh)
 */
uint16_t get_remaining_capacity_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the remaining capacity filtered (mAh)
 * 
 * @details the filtered battery capacity remaining. This value is not allowed to
 * jump unless RemainingCapacityUnfiltered() reaches empty or full before RemainingCapacityFiltered()
 * does
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] remaining filtered capacity (mAh)
 */
uint16_t get_remaining_capacity_filtered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the full charge capacity unfiltered (mAh)
 * @details The compensated capacity of the battery when fully charged
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] full charge capacity unfiltered (mAh)
 */
uint16_t get_full_charge_capacity_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the full charge capacity filtered (mAh)
 * @details Gets the filtered compensated capacity of the battery when fully charged
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] full charge capacity filtered (mAh)
 */
uint16_t get_full_charge_capacity_filtered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the state of charge unfiltered (mAh)
 * 
 * @details  Gets the true state-of-charge. Units are %. StateOfChargeUnfiltered() is
 * updated at regular intervals, and may jump as the gauge updates its predictions dynamically
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] unfiltered state of charge (mAh)
 */
uint16_t get_state_of_charge_unfiltered_mAh_BQ27441_g1(FuelGauge_BQ27441_g1_t* fuel_gauge);


/***********************************************************************************************************
 * Utility Functions
 **********************************************************************************************************/

/**
 * @brief Decode the control status register
 * 
 * @param regValue [-] register value
 * @return control_status_BQ27441_g1_t [-] decoded control status
 */
static control_status_BQ27441_g1_t parse_control_status(uint16_t regValue);

/**
 * @brief Parse the Flags Register
 * 
 * @param regVal [-] register value
 * @return flags_BQ27441_g1_t [-] decoded flag values
 */
static flags_BQ27441_g1_t parse_flags (uint16_t regVal);

/**
 * @brief Parse the OpConfig Register
 * 
 * @param regValue [-] register value
 * @return op_config_BQ27441_g1_t [-] decode op config
 */
static op_config_BQ27441_g1_t parse_op_config (uint16_t regValue);

/**
 * @brief Encode the Operation Configuration
 * 
 * @param config [-] configuration structure
 * @return uint16_t [-] 2 byte data to be sent over the I2C bus
 */
static uint16_t encode_op_config (op_config_BQ27441_g1_t config);

/**
 * @brief 0.1 K to C
 * 
 * @param temp [-] temp in 0.1 K
 * @return float [-] temp in C
 */
static inline float centikelvin_to_celsius (uint16_t temp) { return ((float) temp * 10) - 273.15;}

/**
 * @brief Read 16 bits from given subaddress
 * 
 * @note This is the read function used for all standard commands
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param regAddr [-] register address
 * @return uint16_t [-] data from register
 * 
 * @todo [-] documentation : write out bit by bit what this is supposed to do
 */
static inline uint16_t read_standard(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t regAddr);


/**
 * @brief Read using a control command
 * @details Issuing a Control() command requires a subsequent 2-byte subcommand. These additional bytes specify
 * the particular control function desired. (see 4.1 in the Technical Reference Manual)
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param control_func [-] 2 byte control function command
 * @return uint16_t [-] 2 bytes read from the device
 * @todo [-] documentation : write out bit by bit what this is supposed to do
 * 
 */
static inline uint16_t read_control_function(FuelGauge_BQ27441_g1_t* fuel_gauge, uint16_t control_func);


/**
 * @brief Execute a particular control command
 * @details Issuing a Control() command requires a subsequent 2-byte subcommand. These additional bytes specify
 * the particular control function desired. (see 4.1 in the Technical Reference Manual)
 * 
 * @param [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param control_func [-] 2 byte control function command

 * @todo [-] documentation : write out bit by bit what this is supposed to do
 */
static inline void execute_control_function(FuelGauge_BQ27441_g1_t* fuel_gauge, uint16_t control_func);



/***********************************************************************************************************
 * Control Subcommands 
 **********************************************************************************************************/

/**
 * @brief Return the Control Status Information
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return control_status_BQ27441_g1_t [-] decoded control status information 
 */
control_status_BQ27441_g1_t get_control_status_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Gets device type
 * @details Instructs the fuel gauge to return the device type to addresses 0x00 and 0x01. The value returned is
 * 0x0421. (Note: Value returned is 0x0421 even if the product is bq27441-G1 so the distinguishing
 * identification requires both DEVICE_TYPE and DM_CODE)
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] Device ID
 */
uint16_t get_device_type_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the firmware version 
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] FW version
 */
uint16_t get_firmware_version_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the data memory code 
 * @details Instructs the fuel gauge to return the 8-bit DM Code as the least significant byte of the 16-bit return value
 * at addresses 0x00 and 0x01. The DM_CODE subcommand provides a simple method to determine the
 * configuration code stored in Data Memory
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] DM Code
 */
uint16_t get_data_memory_code_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the previous command writen
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] previous command written
 */
uint16_t get_previous_mac_write_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Get the chemical id
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] chemical id
 */
uint16_t get_chemical_id_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Forces battery present flag when autodetection is disabled
 * @details Forces the Flags() [BAT_DET] bit to set when the battery insertion detection is disabled via OpConfig
 * [BIE] = 0. In this case, the gauge does not detect battery insertion from the BIN pin logic state, but relies
 * on the BAT_INSERT host subcommand to indicate battery presence in the system. This subcommand
 * also starts Impedance Track™ gauging.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void battery_insert_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Forces battery present flag when autodetection is disabled
 * @details Forces the Flags() [BAT_DET] bit to clear when the battery insertion detection is disabled via OpConfig
 * [BIE] = 0. In this case, the gauge does not detect battery removal from the BIN pin logic state, but relies
 * on the BAT_REMOVE host subcommand to indicate battery removal from the system.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void battery_remove_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Set hibernation bit
 * @details Instructs the fuel gauge to force the CONTROL_STATUS [HIBERNATE] bit to 1. If the necessary
 * conditions are met, this enables the gauge to enter the HIBERNATE power mode after the transition to
 * SLEEP power state is detected. The [HIBERNATE] bit is automatically cleared upon exiting from
 * HIBERNATE mode
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void set_hibernate_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Clear hibernation bit
 * @details Instructs the fuel gauge to force the CONTROL_STATUS [HIBERNATE] bit to 0. This prevents the gauge
 * from entering the HIBERNATE power mode after the transition to SLEEP power state is detected. It can
 * also be used to force the gauge out of HIBERNATE mode
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void clear_hibernate_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Set the config update bit
 * @details Instructs the fuel gauge to set the Flags() [CFGUPMODE] bit to 1 and enter CONFIG UPDATE mode. This
 * command is only available when the fuel gauge is UNSEALED
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void set_config_update_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Set the shutdown enable bit
 * @details Instructs the fuel gauge to enable SHUTDOWN mode and set the CONTROL_STATUS [SHUTDOWNEN]
 * status bit
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void set_shutdown_enable_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Shutdown the device
 * @details Instructs the fuel gauge to immediately enter SHUTDOWN mode after receiving this subcommand. The
 * SHUTDOWN mode is effectively a power-down mode with only a small circuit biased by the BAT pin
 * which is used for wake-up detection. To enter SHUTDOWN mode, the SHUTDOWN_ENABLE
 * subcommand must have been previously received. To exit SHUTDOWN mode, the GPOUT pin must be
 * raised from logic low to logic high for at least 200 μs.
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void shutdown_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Seal the device
 * @details Instructs the fuel gauge to transition from UNSEALED state to SEALED state and will set bit 7 (0x80) in
 * the Update Status register to 1. The fuel gauge should always be set to the SEALED state for use in end
 * equipment. The SEALED state blocks accidental writes of specific subcommands  and
 * most Standard and Extended Commands.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void seal_device_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Unseal the device
 * @details  The SEALED state blocks accidental writes of specific subcommands  and
 * most Standard and Extended Commands. In order to unblock these commands you need to
 * unseal the device
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void unseal_device_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Send a pulse on the GPIO pin
 * @details This subcommand can be useful for system level debug or test purposes. It instructs the fuel gauge to
 * pulse the GPOUT pin for approximately 1 ms within 1 second of receiving the command.
 * @note The GPOUT pin must be configured for the SOC_INT output function with the OpConfig
 * [BATLOWEN] bit cleared.
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void pulse_gpio_pin_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Reset the device
 * @details This command instructs the fuel gauge to perform a full device reset and reinitialize RAM data to the
 * default values from ROM and is therefore not typically used in field operation. The gauge sets the Flags()
 * [ITPOR] bit and enters the INITIALIZE mode. This command is only available when the
 * fuel gauge is UNSEALED
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void reset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Soft Reset
 * @details This subcommand instructs the fuel gauge to perform a partial (soft) reset from any mode with an OCV
 * measurement. The Flags() [ITPOR] and [CFGUPMODE] bits are cleared and a resimulation occurs to
 * update both StateOfCharge() and StateOfChargeUnfiltered(). Upon exit from CONFIG
 * UPDATE mode, the fuel gauge will check bit 7 (0x80) in the Update Status register. If bit 7 (0x80) in the
 * Update Status register is set, the fuel gauge will be placed into the SEALED state. This subcommand is
 * only available when the fuel gauge is UNSEALED.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void soft_reset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Exit the config update mode
 * @details This subcommand exits CONFIG UPDATE mode without an OCV measurement and without resimulating
 * to update StateOfChargeUnfiltered() or StateOfCharge(). The Flags() [ITPOR] and [CFGUPMODE] bits
 * are cleared. Upon exit from CONFIG UPDATE mode, the fuel gauge will check bit 7 (0x80) in the Update
 * Status register. If bit 7 (0x80) in the Update Status register is set the fuel gauge will be placed into the
 * SEALED state
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void exit_config_update_mode_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Exit config update mode w/ resim SOC
 * @details This subcommand exits CONFIG UPDATE mode without an OCV measurement. The Flags() [ITPOR] and
 * [CFGUPMODE] bits are cleared and a resimulation occurs to update StateOfChargeUnfiltered(). Upon exit
 * from CONFIG UPDATE mode, the fuel gauge will check bit 7 (0x80) in the Update Status register. If bit 7
 * (0x80) in the Update Status register is set, the fuel gauge will be placed into the SEALED state. This
 * subcommand is only available when the fuel gauge is UNSEALED.
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void exit_config_update_mode_and_resim_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);



/***************************************************************************************************************************************
 * Extended Commands
 **************************************************************************************************************************************/

/**
 * @brief Get the contents operation configuration register
 * @details This command returns the OpConfig Data Memory register setting
 * which is most useful for system level debug to quickly determine device configuration
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return op_config_BQ27441_g1_t [-] decoded op config structure
 *
 * 
 */
op_config_BQ27441_g1_t get_op_config_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Update the contents of the operation configuration register
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param config [-] config structure
 */
void write_op_config_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, op_config_BQ27441_g1_t config);

/**
 * @brief Get the design capacity (mAh)
 * @details This command returns the Design Capacity Data Memory value and
 * is most useful for system level debug to quickly determine device configuration.
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint16_t [-] Design Capacity (mAh)
 */
uint16_t get_design_capacity_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Allow access to RAM
 * @details This command is used to control the data access mode. Writing 0x00 to this
 * command enables BlockData() to access to RAM
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 */
void block_data_control_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Set data class to be accessed
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param id [-] class id
 */
void block_data_class_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t id);

/**
 * @brief Set the block offset
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param offset [-] block offset
 */
void block_data_offset_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset);

/**
 * @brief The the data block's checksum
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint8_t [-] checksum
 */
uint8_t get_block_data_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Read the contents of a particular block
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param offset [-] block offset
 * @return uint8_t [-] block data
 */
uint8_t read_block_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset);

/**
 * @brief Write to a particular data blcok
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param offset [-] block offset
 * @param data [-] data to be written
 * 
 */
void write_block_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t offset, uint8_t data);

/**
 * @brief Compute a new checksum
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @return uint8_t [-] checksum
 */
uint8_t compute_block_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge);

/**
 * @brief Update block checksum 
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param csum [-] checksum
 */
void write_block_checksum_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t csum);

/**
 * @brief Read a block of extended data
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param classID [-] class id
 * @param offset [-] block offset
 * @return uint8_t [-] data pulled from the fuel gauge's RAM
 */
uint8_t read_extended_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t classID, uint8_t offset);

/**
 * @brief Write a block of extended data
 * 
 * @param fuel_gauge [-] pointer to the stucture that contains all of the attributes of the fuel gauge object instance
 * @param classID [-] Class ID
 * @param offset [-] block offset 
 * @param data [-] data buffer
 * @param len [-] number of bytes
 */
void write_extended_data_BQ27441_g1_t(FuelGauge_BQ27441_g1_t* fuel_gauge, uint8_t classID, uint8_t offset, uint8_t* data, uint8_t len);

#ifdef __cplusplus 
}
#endif
