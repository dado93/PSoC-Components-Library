/**
  *  \file           `$INSTANCE_NAME`.h
  *  \brief          Header file for `$INSTANCE_NAME` interface.
  *
  *  \author         Davide Marzorati
  */
 
/*******************************************************************************
 * Copyright (c) 2021 Marzorati Davide
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#ifndef __`$INSTANCE_NAME`_H__
    #define __`$INSTANCE_NAME`_H__
    
    #include "cytypes.h"
    #include "`$INSTANCE_NAME`_Defs.h"

    /**
    *   \brief Number of samples stored in the circular buffer.
    *
    *   This value sets the number of samples stored in the
    *   circular buffer with MAX30101 data. If you have
    *   enough RAM, you can increase it as long as you 
    *   have memory available.
    */
    #define BUFFER_STORAGE_SIZE 8
    
    /**
    *   \brief Circular buffer for MAX30101 data.
    */
    typedef struct 
    {
        uint32_t red[BUFFER_STORAGE_SIZE];      ///< Data from RED channel.
        uint32_t IR[BUFFER_STORAGE_SIZE];       ///< Data from IR channel.
        uint32_t green[BUFFER_STORAGE_SIZE];    ///< Data from GREEN channel.
        uint8_t head;   ///< Current head of the circular buffer.
        uint8_t tail;   ///< Current tail of the circular buffer.
    } MAX30101_Data; //This is our circular buffer of readings from the sensor

    
    //==============================================
    //           Main functions
    //==============================================
    /**
    *   \brief Start the `$INSTANCE_NAME` component.
    *   \retval `#`$INSTANCE_NAME`_OK` if device is present.
    */
    uint8_t `$INSTANCE_NAME`_Start(void);
    
    /**
    *   \brief Check if `$INSTANCE_NAME` is present on I2C bus.
    *
    *   \retval `#`$INSTANCE_NAME`_OK` if device is present.
    *   \retval `#MAX30101_DEV_NOT_FOUND` if device is not present.
    */
    uint8_t `$INSTANCE_NAME`_IsDevicePresent(void);
    
    //==============================================
    //          Interrupt functions
    //==============================================
    
    /**
    *   \brief Check if FIFO A Full interrupt was set.
    *
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsFIFOAFull(uint8_t* flag);
    
    /**
    *   \brief Check if PPG Ready interrupt was set.
    *
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval `#MAX30101_OK` if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsPPGReady(uint8_t* flag);
    
    /**
    *   \brief Check if ALC Overflow interrupt was set.
    *
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsALCOverflow(uint8_t* flag);
    
    /**
    *   \brief Check if power ready interrupt was set.
    *
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsPowerReady(uint8_t* flag);
    
    /**
    *   \brief Check if temperature ready interrupt was set.
    *
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsTempReady(uint8_t* flag);
    
    /**
    *   \brief Enable FIFO A Full interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableFIFOAFullInt(void);
    
    /**
    *   \brief Enable PPG Ready interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnablePPGReadyInt(void);
    
    /**
    *   \brief Enable ALC Overflow interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableALCOverflowInt(void);
    
    /**
    *   \brief Enable Temperature ready interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableTempReadyInt(void);
    
    /**
    *   \brief Disable FIFO A Full interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisableFIFOAFullInt(void);
    
    /**
    *   \brief Disable PPG ready interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisablePPGReadyInt(void);
    
    /**
    *   \brief Disable ALC Overflow interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisableALCOverflowInt(void);
    
    /**
    *   \brief Disable temperature ready interrupt.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_DisableTempReadyInt(void);
    
    //==============================================
    //          MAX30101 FIFO FUNCTIONS
    //==============================================
    
    /**
    *   \brief Read FIFO Write pointer.
    *
    *   \param wr pointer to variable where the write pointer will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadWritePointer(uint8_t* wr);
    
    /**
    *   \brief Read FIFO Overflow counter.
    *
    *   \param oc pointer to variable where the overflow counter will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadOverflowCounter(uint8_t* oc);
    
    /**
    *   \brief Read FIFO read pointer.
    *
    *   \param oc pointer to variable where the read pointer will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadReadPointer(uint8_t* rr);
    
    /**
    *   \brief Clear FIFO.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ClearFIFO(void);
    
    /**
    *   \brief Read FIFO data as single bytes.
    *
    *   This function reads the data in the FIFO of the MAX30101
    *   according to the specified settings. Based on the number
    *   of samples to be read and the number of active leds this
    *   function will perform a complete reading of the FIFO.
    *   Data will be returned as raw uint8_t data.
    *   \param[in] num_samples number of samples to be read
    *   \param[in] active_leds number of active leds
    *   \param[out] data pointer to variable storing raw data from FIFO
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadRawFIFOBytes(uint8_t num_samples, uint8_t active_leds, uint8_t* data);
    
    /**
    *   \brief Read FIFO data.
    *
    *   This function reads the data in the FIFO of the MAX30101
    *   according to the specified settings. Based on the number
    *   of samples to be read and the number of active leds this
    *   function will perform a complete reading of the FIFO.
    *   Data will be returned as uint32_t.
    *   \param[in] num_samples number of samples to be read
    *   \param[in] active_leds number of active leds
    *   \param[out] data pointer to variable storing raw data from FIFO
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadRawFIFO(uint8_t num_samples, uint8_t active_leds, uint32_t* data);
    
    /**
    *   \brief Read FIFO data and place them in a circular buffer.
    *
    *   This function reads the data in the FIFO of the MAX30101
    *   according to the specified settings. Based on the number
    *   of samples to be read and the number of active leds this
    *   function will perform a complete reading of the FIFO.
    *   Data will be returned inside the circular buffer passed
    *   in as parameter to the function.
    *   \param[in] num_samples number of samples to be read
    *   \param[in] active_leds number of active leds
    *   \param[out] data pointer to circular buffer storing data from FIFO
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadFIFO(uint8_t num_samples, uint8_t active_leds, MAX30101_Data* data);
    
    //==============================================
    //     MAX30101 FIFO CONFIGURATION FUNCTIONS
    //==============================================
    
    /**
    *   \brief Set the number of samples averaged per sample in FIFO.
    *   
    *   This function sets the number of samples to be averaged per FIFO sample.
    *   Available choices go from 1 to 32.
    *   \param samples number of samples to be averaged.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetSampleAverage(uint8_t samples);
    
    /**
    *   \brief Enable FIFO Rollover.
    *   
    *   This function enables FIFO Rollover. When enabled, 
    *   the FIFO Address rolls over to zero and the FIFO continues to fill with new data. 
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_EnableFIFORollover(void);
    
    /**
    *   \brief Disable FIFO Rollover.
    *
    *   This function disables FIFO Rollover. When disabled, 
    *   FIFO is not updated until #MAX30101_FIFO_DATA is read or the 
    *   #MAX30101_FIFO_WP or #MAX30101_FIFO_RP positions are changed.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_DisableFIFORollover(void);
    
    /**
    *   \brief Set number of samples for FIFO Almost Full.
    *
    *   This function sets the number of samples required to
    *   trigger a FIFO Almost Full interrupt. 
    *   \param[in] samples number of samples required to trigger a FIFO A FULL interrupt.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_SetFIFOAlmostFull(uint8_t samples);
    
    //==============================================
    //     MAX30101 MODE CONFIGURATION FUNCTIONS
    //==============================================
    
    /**
    *   \brief Shutdown the MAX30101.
    *
    *   The MAX30101 can be put into a power-save mode. 
    *   While in power-save mode, all registers retain their values, and write/read operations
    *   function as normal. All interrupts are cleared to zero in this mode.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_Shutdown(void);
    
    /**
    *   \brief Wake up the MAX30101.
    *
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_WakeUp(void);
    
    /**
    *   \brief Reset the MAX30101.
    *
    *   This function resets the MAX30101 via software by setting
    *   the reset bit in the register #MAX30101_MODE_CONF to 1.
    *   All configuration, threshold, and data registers are reset 
    *   to their power-on-state through a power-on reset
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_Reset(void);
    
    /**
    *   \brief Set the operation mode for the MAX30101.
    *   
    *   This function sets the current LED pulse amplitude mode for 
    *   the MAX30101. Available choices are:
    *       - #MAX30101_HR_MODE: RED Led ON
    *       - #MAX30101_SPO2_MODE: RED and IR Led ON
    *       - #MAX30101_MULTI_MODE: configurable Leds
    *   \param mode mode to be set in the #MAX30101_MODE_CONF register
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetMode(uint8_t mode);
    
    //==============================================
    //     MAX30101 SPO2 CONFIGURATION FUNCTIONS
    //==============================================
      
    /**
    *   \brief Set MAX30101 SpO2 ADC Range.
    *
    *   This function sets the value for the SpO2 ADC
    *   range. Values that can be passed as input to this
    *   function are:
    *       - #MAX30101_ADC_RANGE_2048
    *       - #MAX30101_ADC_RANGE_4096
    *       - #MAX30101_ADC_RANGE_8192
    *       - #MAX30101_ADC_RANGE_16384
    *   \param range the value of SpO2 ADC range to be set.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetSpO2SampleRate(uint8_t range);
    
    /**
    *   \brief Set MAX30101 SpO2 Sample Rate.
    *
    *   This function sets the value for the SpO2 sample
    *   rate. Values that can be passed as input to this
    *   function are:
    *       - #MAX30101_SAMPLE_RATE_50
    *       - #MAX30101_SAMPLE_RATE_100
    *       - #MAX30101_SAMPLE_RATE_200
    *       - #MAX30101_SAMPLE_RATE_400
    *       - #MAX30101_SAMPLE_RATE_800
    *       - #MAX30101_SAMPLE_RATE_1000
    *       - #MAX30101_SAMPLE_RATE_1600
    *       - #MAX30101_SAMPLE_RATE_3200
    *   \param sr the value of SpO2 sample rate to be set.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetSpO2ADCRange(uint8_t sr);
    
    /**
    *   \brief Set MAX30101 LED Pulse Width.
    *
    *   This function sets the value for the SpO2 sample
    *   rate. Values that can be passed as input to this
    *   function are:
    *       - #MAX30101_PULSEWIDTH_69
    *       - #MAX30101_PULSEWIDTH_118
    *       - #MAX30101_PULSEWIDTH_215
    *       - #MAX30101_PULSEWIDTH_411
    *   \param pw the value of LED Pulse Width to be set.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetSpO2PulseWidth(uint8_t pw);
    
    /**
    *   \brief Set the pulse amplitude for a MAX30101 channel.
    *   
    *   This function sets the current LED pulse amplitude a given
    *   channel of the MAX30101.
    *   Pulse amplitude values range from 0x00 to 0xFF.
    *   \param led_channel the channel for which to set the pulse amplitude.
    *   \param pa the value of pulse amplitude to be set,.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetLEDPulseAmplitude(uint8_t led_channel, uint8_t pa);
    
    //======================================================
    //    MAX30101 MULTI LED MODE CONFIGURATION FUNCTIONS
    //======================================================
    /**
    *   \brief Enable a slot in Multi-LED mode.
    *   
    *   In multi-LED mode, each sample is split into up to four time slots, 
    *   SLOT1 through SLOT4. These control registers determine which LED is
    *   active in each time slot, making for a very flexible configuration.
    *   In MAX30101 Both LED3 and LED4 are wired to Green LED. 
    *   Green LED sinks current out of #MAX30101_LED3_PA and #MAX30101_LED4_PA 
    *   if enabled in multi-LED mode.
    *   
    *   \param slot the slot to be enabled (1 through 4)
    *   \param led the led to be activated. It can be one of:
    *       - #MAX30101_SLOT_RED
    *       - #MAX30101_SLOT_IR
    *       - #MAX30101_SLOT_GREEN
    *       - #MAX30101_SLOT_NONE
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_EnableSlot(uint8_t slot, uint8_t led);
    
    /**
    *   \brief Disable all slot configurations in Multi-LED mode.
    *
    *   Disable all the configurations that were set for Multi-LED mode.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_DisableSlots(void);
    
    //======================================================
    //            MAX30101 DIE TEMPERATURE FUNCTIONS
    //======================================================
    
    /**
    *   \brief Read Die Temperature from MAX30101 in float format.
    *
    *   This functions reads the die temperature data from the MAX30101
    *   and returns its value in float format. The temperature value
    *   can be used to calibrate the SpO2 readings.
    *   \param[out] temperature float value of die temperature
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.   
    */
    uint8_t MAX30101_ReadTemperature(float* temperature);
    
    /**
    *   \brief Read Die Temperature from MAX30101 in raw format.
    *
    *   This functions reads the die temperature data from the MAX30101
    *   and returns its integer and fractional parts. The temperature value
    *   can be used to calibrate the SpO2 readings.
    *   \param[out] integer integer value of die temperature
    *   \param[out] frac fractional value of die temperature
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.   
    */
    uint8_t MAX30101_ReadRawTemperature(int8_t* integer, uint8_t* frac);
    
    
    /**
    *   \brief Start temperature conversion on the MAX30101.
    *
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.     
    */
    uint8_t MAX30101_StartTemperatureConversion(void);
    
    //======================================================
    //            MAX30101 PART/REVISION ID FUNCTIONS
    //======================================================
    /**
    *   \brief Read Part ID number from MAX30101.
    *   
    *   \param part_id pointer to variable where part ID value will be stored.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_ReadPartID(uint8_t* part_id);
    
    /**
    *   \brief Read Revision ID number from MAX30101.
    *   
    *   \param revision_id pointer to variable where revision ID value will be stored.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_ReadRevisionID(uint8_t* revision_id);
    
    //======================================================
    //            MAX30101 HELPER FUNCTIONS
    //======================================================
    /**
    *   \brief Read a register from the MAX30101.
    *   
    *   \param[in] reg_addr address of the register to be read.
    *   \param[out] reg_value pointer to variable where register data will be stored.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_ReadRegister(uint8_t reg_addr, uint8_t* reg_value);
    
    /**
    *   \brief Log the values of all MAX30101 registers.
    *   
    *   This function logs all the current values of the 
    *   MAX30101 registers. Be aware that reading some of the
    *   registers may clear interrupts.
    *   \param[in] fun_ptr pointer to the function used for logging.
    *   \param[in] reg_addr address of the register to be read.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_LogRegisters(void (*fun_ptr)(const char*));
    
    /**
    *   \brief Print the value of a MAX30101 register.
    *   
    *   This function prints the value of a MAX30101 register.
    *   Be aware that reading some of the registers may cler interrupts.
    *   registers fun_ptr pointer to the function used for logging.
    *   \param[in] reg_addr address of the register to be read.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_PrintRegister(void (*print_fun)(const char*), uint8_t reg_addr);

#endif
/* [] END OF FILE */

/* [] END OF FILE */
