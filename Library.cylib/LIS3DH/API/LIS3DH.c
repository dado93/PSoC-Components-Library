/**
  *  \file           `$INSTANCE_NAME`.c
  *  \brief          Source file for `$INSTANCE_NAME` interface.
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

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_RegMap.h"
#include "`$INSTANCE_NAME`_I2C.h"

/***********************************
*          API Constants           *
************************************/

/**
 *  \brief          WHO AM I register value.
 */
#define `$INSTANCE_NAME`_WHO_AM_I_VALUE             0x33

/**
 *  \brief Parameter used for X Axis in API Calls.
 */
#define `$INSTANCE_NAME`_X_AXIS_PARAM               0x00

/**
 *  \brief Parameter used for Y Axis in API Calls.
 */
#define `$INSTANCE_NAME`_Y_AXIS_PARAM               0x01

/**
 *  \brief Parameter used for Z Axis in API Calls.
 */
#define `$INSTANCE_NAME`_Z_AXIS_PARAM               0x02

/**
 *  \brief Parameter used for all Axis in API Calls.
 */
#define `$INSTANCE_NAME`_ALL_AXIS_PARAM             0x03

/**
 *  \brief Parameter used for ADC Channel 1 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_1_PARAM             0x00

/**
 *  \brief Parameter used for ADC Channel 2 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_2_PARAM             0x01

/**
 *  \brief Parameter used for ADC Channel 3 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_3_PARAM             0x02

/**
 *  \brief Parameter used for ADC All Channels API Calls.
 */
#define `$INSTANCE_NAME`_ADC_ALL_CH_PARAM           0x03

/***********************************
*            Macros                *
************************************/
#define `$INSTANCE_NAME`_I2C_ADDRESS `$I2C_Address`


/***********************************
*     Function Decalarations       *
************************************/

static uint8_t `$INSTANCE_NAME`_Read(uint8_t register_address,
                                        uint8_t* value);

static uint8_t `$INSTANCE_NAME`_ReadMulti(uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* value);

static uint8_t `$INSTANCE_NAME`_Write(uint8_t register_address,
                                        uint8_t value);

static uint8_t `$INSTANCE_NAME`_ReadRawAccData(uint8_t axis,
                                                uint16_t* data);

static uint8_t `$INSTANCE_NAME`_ReadRawAccDataAllAxis(uint16_t* x_axis, 
                                                    uint16_t* y_axis, 
                                                    uint16_t* z_axis);

static uint8_t `$INSTANCE_NAME`_ReadRawADCData(uint8_t channel,
                                                uint16_t* data);

static uint8_t `$INSTANCE_NAME`_ReadRawADCDataAllChannels(uint16_t* ch_1,
                                                uint16_t* ch_2,
                                                uint16_t* ch_3);

static uint8_t `$INSTANCE_NAME`_ReadAccData(uint8_t axis,
                                                float* data);

static uint8_t `$INSTANCE_NAME`_ReadAccDataAllAxis(float* x_axis,
                                                        float* y_axis,
                                                        float* z_axis);

static uint8_t `$INSTANCE_NAME`_ReadADCData(uint8_t channel,
                                                float* data);

static uint8_t `$INSTANCE_NAME`_ReadADCDataAllChannels(float* ch_1,
                                                        float* ch_2,
                                                        float* ch_3);

static uint8_t `$INSTANCE_NAME`_ClearBit(uint8_t register_address,
                                        uint8_t bit_pos);

static uint8_t `$INSTANCE_NAME`_SetBit(uint8_t register_address,
                                        uint8_t bit_pos);

static uint8_t `$INSTANCE_NAME`_CheckAxisOverrun(uint8_t axis, uint8_t* overrun);

static uint8_t `$INSTANCE_NAME`_CheckAxisNewData(uint8_t axis, uint8_t* new_data);

static uint8_t `$INSTANCE_NAME`_CheckADCOverrun(uint8_t axis, uint8_t* overrun);

static uint8_t `$INSTANCE_NAME`_CheckADCNewData(uint8_t axis, uint8_t* new_data);

/***********************************
*          Module Variables         *
************************************/

static struct {
    uint8_t     Init;   
    uint8_t     LowPowerEnabled; 
    uint8_t     FullScaleRange; 
    uint8_t     HighResolutionMode;
    uint8_t     NumberOfShiftBits;
    uint8_t     ADCNumberOfShiftBits;
    uint8_t     Sensitivity;
} `$INSTANCE_NAME`_Config;

static const uint8_t `$INSTANCE_NAME`_Sensitivity[4][3] = { {1,  4,  16},   /* FS Range +/- 2g */
                                                    {2,  8,  32},           /* FS Range +/- 4g */
                                                    {4, 16,  64},           /* FS Range +/- 8g */
                                                    {12,48, 192}};          /* FS Range +/- 16g */


/***********************************
*          Generic Functions       *
************************************/

/**
 *  \brief          Start the LIS3DH Component.
 *
 *  Start the component dedicated to I2C communication, 
 *  and check the presence of the device on the I2C bus.
 *  If the device is present, it initialies it with the
 *  default configuration values provided in the 
 *  component dialog.
 */
uint8_t `$INSTANCE_NAME`_Start(void)
{
    /* Start I2C Master Component */
    `$INSTANCE_NAME`_I2C_Start();
    
    /* Check WHO AM I register value */
    uint8_t who_am_i, error;
    if (`$INSTANCE_NAME`_ReadWhoAmI(&who_am_i) == `$INSTANCE_NAME`_OK)
    {
        if (who_am_i != `$INSTANCE_NAME`_WHO_AM_I_VALUE)
        {
            return `$INSTANCE_NAME`_DEV_NOT_FOUND;
        }
    }
    else
    {
        return `$INSTANCE_NAME`_DEV_NOT_FOUND;
    }
    
    /* Check if we need to disconnect pull-up */
    if (`$I2C_Pullup`)
    {
        error = `$INSTANCE_NAME`_DisconnectPullUp();
    }
    else
    {
        error = `$INSTANCE_NAME`_ConnectPullUp();
    }
    
    /* Check if we need to enable X Axis */
    if (`$en_x_axis`)
    {
        error = `$INSTANCE_NAME`_EnableXAxis();
    }
    else
    {
        error =`$INSTANCE_NAME`_DisableXAxis();
    }
    
    /* Check if we need to enable Y Axis */
    if (`$en_y_axis`)
    {
        error = `$INSTANCE_NAME`_EnableYAxis();
    }
    else
    {
        error =`$INSTANCE_NAME`_DisableYAxis();
    }
    
    /* Check if we need to enable Z Axis */
    if (`$en_z_axis`)
    {
        error = `$INSTANCE_NAME`_EnableZAxis();
    }
    else
    {
        error =`$INSTANCE_NAME`_DisableZAxis();
    }
    
    /* Check if we need to enable ADC */
    if (`$en_adc`)
    {
        error = `$INSTANCE_NAME`_EnableADC();
    }
    else
    {
        error =`$INSTANCE_NAME`_DisableADC();
    }
    
    /* Check if we need to enable temperature sensor */
    if (`$en_temperature_sensor`)
    {
        error = `$INSTANCE_NAME`_EnableTempSensor();
    }
    else
    {
        error = `$INSTANCE_NAME`_DisableTempSensor();
    }
    
    /* Check if we need to enable low power mode */
    if (`$en_low_power`)
    {
        error = `$INSTANCE_NAME`_EnableLowPowerMode();
    }
    else
    {
        error = `$INSTANCE_NAME`_DisableLowPowerMode();
    }
    
    /* Set output data rate */
    error = `$INSTANCE_NAME`_SetOutputDataRate(`$acc_odr`);
    
    /* Set full scale range */
    error = `$INSTANCE_NAME`_SetFullScaleRange(`$acc_fsr`);
    
    `$INSTANCE_NAME`_Config.ADCNumberOfShiftBits = 6;
    
    if ( error == `$INSTANCE_NAME`_OK )
    {
        `$INSTANCE_NAME`_Config.Init = 1;
    }
    
    return error;
}

uint8_t `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_I2C_Stop();
    return `$INSTANCE_NAME`_OK;
}

/***********************************
*     Read Register Functions      *
************************************/

/**
 *  \brief          Read Who Am I register from device.
 *  \param[out]     Value of the Who Am I register.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ReadWhoAmI(uint8_t* value)
{
    return `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_WHO_AM_I_REGISTER, value);
}

/***********************************
*     Configuration Functions      *
************************************/
/**
 *  \brief          Disconnect Pull-Up resistor from SDO/SA0 pin.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_I2C_ERR if error occurred during I2C communication.
 */
uint8_t `$INSTANCE_NAME`_DisconnectPullUp(void)
{
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, 7);
}

/**
 *  \brief          Connect Pull-Up resistor to SDO/SA0 pin.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_I2C_ERR if error occurred during I2C communication.
 */
uint8_t `$INSTANCE_NAME`_ConnectPullUp(void)
{
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, 7);
}

/**
 *  \brief          Enable ADC.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 *  \note           Block Data Update is enabled for ADC correct functionality.
 */
uint8_t `$INSTANCE_NAME`_EnableADC(void)
{
    /* Enable BDU */
    uint8_t error = `$INSTANCE_NAME`_EnableBlockDataUpdate();
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Set bit 7 of TEMP_CFG_REG */
        error = `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_TEMP_CFG_REGISTER, 7);
    }
    return error;
}

/**
 *  \brief          Enable temperature sensor.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableTempSensor(void)
{
    /* Set bit 6 of TEMP_CFG_REG */
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_TEMP_CFG_REGISTER, 6);
}

/**
 *  \brief          Disable ADC.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 *  \note           Block Data Update is note disabled when disabling ADC.
 */
uint8_t `$INSTANCE_NAME`_DisableADC(void)
{
    /* Set bit 7 of TEMP_CFG_REG */
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_TEMP_CFG_REGISTER, 7);
    
}

/**
 *  \brief          Disable temperature sensor.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableTempSensor(void)
{
    /* Set bit 6 of TEMP_CFG_REG */
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_TEMP_CFG_REGISTER, 6);
}

/**
 *  \brief          Enable low power mode.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if device is in high resolution mode.
 */
uint8_t `$INSTANCE_NAME`_EnableLowPowerMode(void)
{
    if ( `$INSTANCE_NAME`_Config.HighResolutionMode )
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Set bit 3 of CTRL_REG1 */
    uint8_t error = `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 3);  
    if ( error == `$INSTANCE_NAME`_OK)
    {
        `$INSTANCE_NAME`_Config.LowPowerEnabled = 1;
        `$INSTANCE_NAME`_Config.NumberOfShiftBits = 8;
    }
    return error;
}

/**
 *  \brief          Disable low power mode.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableLowPowerMode(void)
{
    /* Clear bit 3 of CTRL_REG1 */
    uint8_t error = `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 3);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        `$INSTANCE_NAME`_Config.LowPowerEnabled = 0;
        `$INSTANCE_NAME`_Config.NumberOfShiftBits = 6;
    }
    return error;
}

/**
 *  \brief          Set accelerometer full scale range.
 *  \param[in]      fsr: the full scale range to be set. Available options are:
 *                      \ref `$INSTANCE_NAME`_FSR_2g
 *                      \ref `$INSTANCE_NAME`_FSR_4g
 *                      \ref `$INSTANCE_NAME`_FSR_8g
 *                      \ref `$INSTANCE_NAME`_FSR_16g
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref fsr is not a valid option.
*/
uint8_t `$INSTANCE_NAME`_SetFullScaleRange(uint8_t fsr)
{
    if (fsr > `$INSTANCE_NAME`_FSR_16g)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    uint8_t temp_reg_data;
    /* FSR bits are bits [5:4] of CTRL_REG4 */
    uint8_t error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, &temp_reg_data);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Clear bits [5:4] */
        temp_reg_data &= 0xCF;
        /* Set bits [5:4] with desired value of FSR, make sure to keep lowest 2 bits */
        fsr &= 0x03;
        temp_reg_data |= (fsr << 4);
        error = `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, temp_reg_data);
        if ( error == `$INSTANCE_NAME`_OK)
        {
            /* Update current sensitivity level */
            `$INSTANCE_NAME`_Config.FullScaleRange = fsr;
            uint8_t sens_index = 1;
            if( `$INSTANCE_NAME`_Config.LowPowerEnabled )
            {
                sens_index = 2;
            }
            else if ( `$INSTANCE_NAME`_Config.HighResolutionMode )
            {
                sens_index = 0;
            }
            `$INSTANCE_NAME`_Config.Sensitivity = `$INSTANCE_NAME`_Sensitivity[`$INSTANCE_NAME`_Config.FullScaleRange][sens_index];
            return error;
        }
    }
    
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/**
 *  \brief          Enable Block Data Update (BDU).
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.        
 */
uint8_t `$INSTANCE_NAME`_EnableBlockDataUpdate(void)
{
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, 7);
}

/**
 *  \brief          Disable Block Data Update (BDU).
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.        
 */
uint8_t `$INSTANCE_NAME`_DisableBlockDataUpdate(void)
{
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, 7);
}

/**
 *  \brief          Enable High Resolution mode.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.  
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if device is in low power mode.  
 */
uint8_t `$INSTANCE_NAME`_EnableHighResolution(void)
{
    if ( `$INSTANCE_NAME`_Config.LowPowerEnabled )
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    uint8_t error = `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, 3);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        `$INSTANCE_NAME`_Config.HighResolutionMode = 1;
        `$INSTANCE_NAME`_Config.NumberOfShiftBits = 4;
        `$INSTANCE_NAME`_Config.Sensitivity = `$INSTANCE_NAME`_Sensitivity[`$INSTANCE_NAME`_Config.FullScaleRange][0];
    }
    return error;
}

/**
 *  \brief          Disable High Resolution mode.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.   
 */
uint8_t `$INSTANCE_NAME`_DisableHighResolution(void)
{
    uint8_t error = `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG4_REGISTER, 3);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Switch back to normal mode configuration */
        `$INSTANCE_NAME`_Config.HighResolutionMode = 0;
        `$INSTANCE_NAME`_Config.NumberOfShiftBits = 6;
        `$INSTANCE_NAME`_Config.Sensitivity = `$INSTANCE_NAME`_Sensitivity[`$INSTANCE_NAME`_Config.FullScaleRange][1];
    }
    return error;
}

uint8_t `$INSTANCE_NAME`_EnableSelfTest0(void)
{
    
}

uint8_t `$INSTANCE_NAME`_EnableSelfTest1(void)
{
}

uint8_t `$INSTANCE_NAME`_DisableSelfTest0(void)
{
    
}

uint8_t `$INSTANCE_NAME`_DisableSelfTest1(void)
{
}
/***********************************
*      Acceleration Functions      *
************************************/

/**
 *  \brief          Enable X Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableXAxis(void)
{
    /* Set bit 0 of CTRL_REG1 */
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 0);  
}

/**
 *  \brief          Disable X Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableXAxis(void)
{
    /* Clear bit 0 of CTRL_REG1 */
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 0); 
}

/**
 *  \brief          Enable Y Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableYAxis(void)
{
    /* Set bit 1 of CTRL_REG1 */
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 1);  
}

/**
 *  \brief          Disable Y Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableYAxis(void)
{
    /* Clear bit 1 of CTRL_REG1 */
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 1); 
}

/**
 *  \brief          Enable Z Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableZAxis(void)
{
    /* Set bit 2 of CTRL_REG1 */
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 2);  
}

/**
 *  \brief          Disable Z Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableZAxis(void)
{
    /* Clear bit 2 of CTRL_REG1 */
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 2); 
}

/**
 *  \brief          Set acceleration and ADC output data rate.
 *  \param[in]      odr: output data rate.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_SetOutputDataRate(uint8_t odr)
{
    if (odr > 9)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    uint8_t temp_reg_value;
   /* Read CTRL_REG1 register */
    uint8_t error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {    
        /* Clear required bits [7:4] */
        temp_reg_value &= 0x0F;
        temp_reg_value |= (odr << 4);
        error = `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, temp_reg_value);
        if ( error != `$INSTANCE_NAME`_OK)
        {
            return `$INSTANCE_NAME`_I2C_ERR;
        }
        return error;
    }
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
        
}

/**
 *  \brief          Check if X axis has overrun.
 *  \param[out]     overrun : 1 if X axis has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_XAxisHasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckAxisOverrun(`$INSTANCE_NAME`_X_AXIS_PARAM, overrun);
}

/**
 *  \brief          Check if Y axis has overrun.
 *  \param[out]     overrun : 1 if Y axis has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_YAxisHasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckAxisOverrun(`$INSTANCE_NAME`_Y_AXIS_PARAM , overrun);
}

/**
 *  \brief          Check if Z axis has overrun.
 *  \param[out]     overrun : 1 if Z axis has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ZAxisHasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckAxisOverrun(`$INSTANCE_NAME`_Z_AXIS_PARAM , overrun);
}

/**
 *  \brief          Check if all axis have overrun.
 *  \param[out]     overrun : 1 if all axis has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_AxisHasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckAxisOverrun(`$INSTANCE_NAME`_ALL_AXIS_PARAM , overrun);
}

/**
 *  \brief          Check for axis overrun.
 *  \param[in]      axis: the axis to be checked (1 for X axis, 4 for any axis)
 *  \param[out]     overrun : 1 if any axis has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref axis is out of range
 */
static uint8_t `$INSTANCE_NAME`_CheckAxisOverrun(uint8_t axis, uint8_t* overrun)
{
    if ( axis > `$INSTANCE_NAME`_ALL_AXIS_PARAM )
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_STATUS_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Check bit based on axis parameter */
        *overrun = (temp_reg_value & (1<<(3+axis))) > 0 ? 1 : 0;
        return error;
    }   
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/**
 *  \brief          Check if X axis has new data.
 *  \param[out]     overrun : 1 if X axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_XAxisHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckAxisNewData(`$INSTANCE_NAME`_X_AXIS_PARAM, new_data);
}

/**
 *  \brief          Check if Y axis has new data.
 *  \param[out]     new_data : 1 if Y axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_YAxisHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckAxisNewData(`$INSTANCE_NAME`_Y_AXIS_PARAM, new_data);
}

/**
 *  \brief          Check if Z axis has new data.
 *  \param[out]     overrun: 1 if Z axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ZAxisHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckAxisNewData(`$INSTANCE_NAME`_Z_AXIS_PARAM, new_data);
}

/**
 *  \brief          Check if all axis has new data.
 *  \param[out]     new_data: 1 if all axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_AxisHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckAxisNewData(`$INSTANCE_NAME`_ALL_AXIS_PARAM, new_data);
}

/**
 *  \brief          Check for axis new data.
 *  \param[in]      axis: the axis to be checked (1 for axis 1, 4 for any axis)
 *  \param[out]     new_data : 1 if any axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref axis is out of range
 */
static uint8_t `$INSTANCE_NAME`_CheckAxisNewData(uint8_t axis, uint8_t* new_data)
{
    if ( axis > `$INSTANCE_NAME`_ALL_AXIS_PARAM )
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_STATUS_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Check bit based on axis parameter */
        *new_data = (temp_reg_value & (1 << axis)) > 0 ? 1 : 0;
        return error;
    }   
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/*
 *  \brief          Read raw X Axis data.
 *  \param[out]     data: the raw 16-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_XAxisReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawAccData(`$INSTANCE_NAME`_X_AXIS_PARAM, data);
}

/*
 *  \brief          Read raw Y Axis data.
 *  \param[out]     data: the raw 16-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_YAxisReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawAccData(`$INSTANCE_NAME`_Y_AXIS_PARAM, data);
}

/*
 *  \brief          Read raw Z Axis data.
 *  \param[out]     data: the raw 16-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ZAxisReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawAccData(`$INSTANCE_NAME`_Z_AXIS_PARAM, data);
}

/**
 *  \brief          Read raw acceleration data from all axis.
 *  \param[out]     x_axis: the raw x axis data read from the device.
 *  \param[out]     y_axis: the raw y axis data read from the device.
 *  \param[out]     z_axis: the raw z axis data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_AxisReadRaw(uint16_t* x_axis, 
                                                uint16_t* y_axis,
                                                uint16_t* z_axis)
{
    /* Read starting from OUT_X_L register */
    uint8_t temp_data[6];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(`$INSTANCE_NAME`_OUT_X_L_REGISTER, 6, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *x_axis = (((uint16_t)temp_data[1])) << 8 | temp_data[0];
        *y_axis = (((uint16_t)temp_data[3])) << 8 | temp_data[2];
        *z_axis = (((uint16_t)temp_data[5])) << 8 | temp_data[4];
    }
    return error;
}

/**
 *  \brief          Read acceleration data from X axis.
 *  \param[out]     data: floating point acceleration of X axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_XAxisRead(float* data)
{
    return `$INSTANCE_NAME`_ReadAccData(`$INSTANCE_NAME`_X_AXIS_PARAM, data);
}

/**
 *  \brief          Read acceleration data from Y axis.
 *  \param[out]     data: floating point acceleration of Y axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_YAxisRead(float* data)
{
    return `$INSTANCE_NAME`_ReadAccData(`$INSTANCE_NAME`_Y_AXIS_PARAM, data);
}

/**
 *  \brief          Read acceleration data from Z axis.
 *  \param[out]     data: floating point acceleration on Z axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ZAxisRead(float* data)
{
    return `$INSTANCE_NAME`_ReadAccData(`$INSTANCE_NAME`_Z_AXIS_PARAM, data);
}

/**
 *  \brief          Read acceleration data from all axis.
 *  \param[out]     x_axis: floating point acceleration on X axis.
 *  \param[out]     y_axis: floating point acceleration on Y axis.
 *  \param[out]     z_axis: floating point acceleration on Z axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_AxisRead(float* x_axis, 
                                        float* y_axis,
                                        float* z_axis)
{
    return `$INSTANCE_NAME`_ReadAccDataAllAxis(x_axis, y_axis, z_axis);
}

/***********************************
*          ADC Functions           *
************************************/

/**
 *  \brief          Check if ADC Channel 1 has overrun.
 *  \param[out]     overrun : 1 if ADC Channel 1 has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC1HasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckADCOverrun(`$INSTANCE_NAME`_ADC_CH_1_PARAM, overrun);
}

/**
 *  \brief          Check if ADC Channel 2 has overrun.
 *  \param[out]     overrun : 1 if ADC Channel 2 has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC2HasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckADCOverrun(`$INSTANCE_NAME`_ADC_CH_2_PARAM, overrun);
}

/**
 *  \brief          Check if ADC Channel 3 has overrun.
 *  \param[out]     overrun : 1 if ADC Channel 3 has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC3HasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckADCOverrun(`$INSTANCE_NAME`_ADC_CH_3_PARAM, overrun);
}

/**
 *  \brief          Check if any ADC Channel has overrun.
 *  \param[out]     overrun : 1 if any ADC Channel has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADCHasOverrun(uint8_t* overrun)
{
    return `$INSTANCE_NAME`_CheckADCOverrun(`$INSTANCE_NAME`_ADC_ALL_CH_PARAM, overrun);
}

/**
 *  \brief          Check for ADC overrun.
 *  \param[in]      ch: the channel to be checked (1 for ADC Channel 1, 4 for any channel)
 *  \param[out]     overrun : 1 if any channel has ovverun, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref axis is out of range
 */
static uint8_t `$INSTANCE_NAME`_CheckADCOverrun(uint8_t ch, uint8_t* overrun)
{
    if (ch > `$INSTANCE_NAME`_ADC_ALL_CH_PARAM)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_STATUS_REG_AUX_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Check bit based on axis parameter */
        *overrun = (temp_reg_value & (1<<(3+ch))) > 0 ? 1 : 0;
        return error;
    }   
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/**
 *  \brief          Check if ADC Channel 1 has new data.
 *  \param[out]     overrun : 1 if ADC Channel 1 has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC1HasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckADCNewData(`$INSTANCE_NAME`_ADC_CH_1_PARAM, new_data);
}

/**
 *  \brief          Check if ADC Channel 2 has new data.
 *  \param[out]     new_data : 1 if ADC Channel 2 has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC2HasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckADCNewData(`$INSTANCE_NAME`_ADC_CH_2_PARAM, new_data);
}

/**
 *  \brief          Check if ADC Channel 3 has new data.
 *  \param[out]     overrun : 1 if ADC Channel 3 has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC3HasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckADCNewData(`$INSTANCE_NAME`_ADC_CH_3_PARAM, new_data);
}

/**
 *  \brief          Check if any ADC channel has new data.
 *  \param[out]     new_data : 1 if any ADC channel has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADCHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckADCNewData(`$INSTANCE_NAME`_ADC_ALL_CH_PARAM, new_data);
}

/**
 *  \brief          Check for ADC new data.
 *  \param[in]      ch: the ADC channel to be checked (1 for Channel 1 1, 4 for any channel)
 *  \param[out]     new_data : 1 if any axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref axis is out of range
 */
static uint8_t `$INSTANCE_NAME`_CheckADCNewData(uint8_t ch, uint8_t* new_data)
{
    if (ch > `$INSTANCE_NAME`_ADC_ALL_CH_PARAM)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_STATUS_REG_AUX_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Check bit based on axis parameter */
        *new_data = (temp_reg_value & (1 << ch)) > 0 ? 1 : 0;
        return error;
    }   
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/*
 *  \brief          Read raw ADC Channel 1 data.
 *  \param[out]     data: the raw 8/10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC1ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawADCData(`$INSTANCE_NAME`_ADC_CH_1_PARAM, data);
}
    
uint8_t `$INSTANCE_NAME`_ADC1Read(float* data)
{
    return `$INSTANCE_NAME`_ReadADCData(`$INSTANCE_NAME`_ADC_CH_1_PARAM, data);
}

/*
 *  \brief          Read raw ADC Channel 2 data.
 *  \param[out]     data: the raw 8/10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC2ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawADCData(`$INSTANCE_NAME`_ADC_CH_2_PARAM, data);
}

uint8_t `$INSTANCE_NAME`_ADC2Read(float* data)
{
    return `$INSTANCE_NAME`_ReadADCData(`$INSTANCE_NAME`_ADC_CH_2_PARAM, data);
}

/*
 *  \brief          Read raw ADC Channel 3 data.
 *  \param[out]     data: the raw 8/10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ADC3ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawADCData(`$INSTANCE_NAME`_ADC_CH_3_PARAM, data);
}

uint8_t `$INSTANCE_NAME`_ADC3Read(float* data)
{
    return `$INSTANCE_NAME`_ReadADCData(`$INSTANCE_NAME`_ADC_CH_3_PARAM, data);
}

uint8_t `$INSTANCE_NAME`_ADCReadRaw(uint16_t* ch_1, uint16_t* ch_2, uint16_t* ch_3)
{
    return `$INSTANCE_NAME`_ReadRawADCDataAllChannels(ch_1, ch_2, ch_3);
}

uint8_t `$INSTANCE_NAME`_ADCRead(float* ch_1, float* ch_2, float* ch_3)
{
    return `$INSTANCE_NAME`_ReadADCDataAllChannels(ch_1, ch_2, ch_3);
}

/***********************************
*           I2C Functions          *
************************************/
/**
 *  \brief          Read a register via I2C.
 * 
 *  \param[in]      register_address: the address of the register to be read.
 *  \param[out]     value: the value read from the register.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_Read(uint8_t register_address,
                                        uint8_t* value)
{
    uint8_t temp_value = 0;
    uint8_t error = `$INSTANCE_NAME`_I2C_ReadRegister(`$INSTANCE_NAME`_I2C_ADDRESS,
                                                        register_address,
                                                        &temp_value);
    if (error == `$INSTANCE_NAME`_I2C_OK)
    {
        *value = temp_value;
        return `$INSTANCE_NAME`_OK;
    }

    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/**
 *  \brief          Read multiple registers via I2C.
 * 
 *  \param[in]      register_address: the starting address of the registers to be read.
 *  \param[in]      register_count: the total number of registers to be read.
 *  \param[out]     data: the data read from the registers.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadMulti(uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data)
{
    register_address |= 0x80;   // auto-increment register address
    return `$INSTANCE_NAME`_I2C_ReadMultiRegister(`$INSTANCE_NAME`_I2C_ADDRESS, 
                                                    register_address,
                                                    register_count,
                                                    data);
}    

/**
 *  \brief          Read raw acceleration data single axis.
 *  \param[in]      axis: the axis of interest.
 *  \param[out]     data: the raw data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadRawAccData(uint8_t axis, uint16_t* data)
{
    /* Read starting from OUT_X_L register */
    uint8_t temp_data[6];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(`$INSTANCE_NAME`_OUT_X_L_REGISTER, 6, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *data = (((uint16_t)temp_data[(axis<<1)+1]) << 8) | temp_data[axis << 1];
    }
    return error;
}

/**
 *  \brief          Read raw ADC data from single channel.
 *  \param[in]      channel: the channel of interest.
 *  \param[out]     data: the raw data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadRawADCData(uint8_t channel, uint16_t* data)
{
    /* Read starting from OUT_X_L register */
    uint8_t temp_data[6];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(`$INSTANCE_NAME`_OUT_ADC_1_L_REGISTER, 6, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *data = (((uint16_t)temp_data[(channel<<1)+1]) << 8) | temp_data[channel << 1];
    }
    return error;
}

/**
 *  \brief          Read raw acceleration data all axis.
 *  \param[out]     x_axis: the raw data read from the x axis.
 *  \param[out]     y_axis: the raw data read from the y axis.
 *  \param[out]     z_axis: the raw data read from the z axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadRawAccDataAllAxis(uint16_t* x_axis, 
                                                        uint16_t* y_axis, 
                                                        uint16_t* z_axis)
{
    /* Read starting from OUT_X_L register */
    uint8_t temp_data[6];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(`$INSTANCE_NAME`_OUT_X_L_REGISTER, 6, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *x_axis = ((uint16_t)temp_data[1] << 8) | temp_data[0];
        *y_axis = ((uint16_t)temp_data[3] << 8) | temp_data[2];
        *z_axis = ((uint16_t)temp_data[5] << 8) | temp_data[4];
    }
    return error;
}

/**
 *  \brief          Read raw ADC data from all channels.
 *  \param[out]     ch_1: the raw data read from channel 1.
 *  \param[out]     ch_2: the raw data read from channel 2.
 *  \param[out]     ch_3: the raw data read from channel 3.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadRawADCDataAllChannels(uint16_t* ch_1, 
                                                        uint16_t* ch_2, 
                                                        uint16_t* ch_3)
{
    /* Read starting from OUT_X_L register */
    uint8_t temp_data[6];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(`$INSTANCE_NAME`_OUT_ADC_1_L_REGISTER, 6, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *ch_1 = ((uint16_t)temp_data[1] << 8) | temp_data[0];
        *ch_2 = ((uint16_t)temp_data[3] << 8) | temp_data[2];
        *ch_3 = ((uint16_t)temp_data[5] << 8) | temp_data[4];
    }
    return error;
}

/**
 *  \brief          Read acceleration data from single axis.
 *  \param[in]      axis: the axis of intereset.
 *  \param[out]     data: the floating point data read from axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref axis value is out of range.
 */
static uint8_t `$INSTANCE_NAME`_ReadAccData(uint8_t axis,
                                                float* data)
{
    if ( axis > `$INSTANCE_NAME`_Z_AXIS_PARAM)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Get raw bits */
    int16_t raw_data;
    uint8_t error = `$INSTANCE_NAME`_ReadRawAccData(axis, (uint16_t*)&raw_data);
    
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Shift with proper number of bits */
        raw_data = raw_data >> `$INSTANCE_NAME`_Config.NumberOfShiftBits;
        
        /* Convert to float */
        *data = `$INSTANCE_NAME`_Config.Sensitivity * ((float) raw_data);
    }
    return error;
}

/*
 *  \brief          Read acceleration data in float format from all axis.
 *  \param[out]     x_axis: x axis acceleration.
 *  \param[out]     y_axis: y axis acceleration.
 *  \param[out]     z_axis: z axis acceleration.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadAccDataAllAxis(float* x_axis,
                                                float* y_axis,
                                                float* z_axis)
{
    /* Get raw bits with sign*/
    int16_t raw_x_axis, raw_y_axis, raw_z_axis;
    uint8_t error = `$INSTANCE_NAME`_ReadRawAccDataAllAxis((uint16_t*)&raw_x_axis, 
                                                           (uint16_t*)&raw_y_axis, 
                                                           (uint16_t*)&raw_z_axis);

    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Shift with proper number of bits */
        raw_x_axis = raw_x_axis >> `$INSTANCE_NAME`_Config.NumberOfShiftBits;
        raw_y_axis = raw_y_axis >> `$INSTANCE_NAME`_Config.NumberOfShiftBits;
        raw_z_axis = raw_z_axis >> `$INSTANCE_NAME`_Config.NumberOfShiftBits;
        
        /* Convert to float */
        *x_axis = `$INSTANCE_NAME`_Config.Sensitivity * ((float) raw_x_axis);
        *y_axis = `$INSTANCE_NAME`_Config.Sensitivity * ((float) raw_y_axis);
        *z_axis = `$INSTANCE_NAME`_Config.Sensitivity * ((float) raw_z_axis);   
    }
    return error;
}

/*
 *  \brief          Read ADC data in float format from a given channel.
 *  \param[in]      channel: the ADC channel of interest.
 *  \param[out]     value: the floating point 8/10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref channel is out of range.
 */
static uint8_t `$INSTANCE_NAME`_ReadADCData(uint8_t channel,
                                        float* value)
{
    if ( channel > `$INSTANCE_NAME`_ADC_CH_3_PARAM)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Get raw bits */
    int16_t raw_data;
    uint8_t error = `$INSTANCE_NAME`_ReadRawADCData(channel, (uint16_t*)&raw_data);
    
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Shift with proper number of bits (8 in LP, 6 otherwise) */
        raw_data = raw_data >> `$INSTANCE_NAME`_Config.ADCNumberOfShiftBits;
        
        /* Convert to float */
        *value = ((float) raw_data);
    }
    return error;
}

/*
 *  \brief          Read ADC data in float format from all channels.
 *  \param[out]     x_axis: x axis acceleration.
 *  \param[out]     y_axis: y axis acceleration.
 *  \param[out]     z_axis: z axis acceleration.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadADCDataAllChannels(float* ch_1,
                                                float* ch_2,
                                                float* ch_3)
{
    /* Get raw bits with sign*/
    int16_t raw_ch_1, raw_ch_2, raw_ch_3;
    uint8_t error = `$INSTANCE_NAME`_ReadRawADCDataAllChannels((uint16_t*)&raw_ch_1, 
                                                           (uint16_t*)&raw_ch_2, 
                                                           (uint16_t*)&raw_ch_3);

    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Shift with proper number of bits */
        raw_ch_1 = raw_ch_1 >> `$INSTANCE_NAME`_Config.ADCNumberOfShiftBits;
        raw_ch_2 = raw_ch_2 >> `$INSTANCE_NAME`_Config.ADCNumberOfShiftBits;
        raw_ch_3 = raw_ch_3 >> `$INSTANCE_NAME`_Config.ADCNumberOfShiftBits;
        
        /* Convert to float */
        *ch_1 = (float) raw_ch_1;
        *ch_2 = (float) raw_ch_2;
        *ch_3 = (float) raw_ch_3;   
    }
    return error;
}

/**
 *  \brief          Write a register via I2C.
 * 
 *  \param[in]      register_address: the address of the register to be written.
 *  \param[in]      value: the value to be written to the register.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_Write(uint8_t register_address,
                                        uint8_t value)
{
    uint8_t error = `$INSTANCE_NAME`_I2C_WriteRegister(`$INSTANCE_NAME`_I2C_ADDRESS, register_address, value);
    if (error == `$INSTANCE_NAME`_I2C_OK)
    {
        return `$INSTANCE_NAME`_OK;
    }

    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}

/**
 *  \brief          Clear bit in the I2C register.
 *  \param[in]      register_address: address of the I2C register.
 *  \param[in]      bit_pos: position of the bit to be cleared.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref bit_pos is out of range
 */
static uint8_t `$INSTANCE_NAME`_ClearBit(uint8_t register_address,
                                        uint8_t bit_pos)
{
    if (bit_pos > 7)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(register_address, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Clear bit of the register */
        temp_reg_value &= ~(1 << bit_pos);
        error = `$INSTANCE_NAME`_Write(register_address, temp_reg_value);
        
        /* Return error based on check */
        if ( error == `$INSTANCE_NAME`_OK)
        {
            return error;
        }
        else
        {
            return `$INSTANCE_NAME`_I2C_ERR;
        }
        
    }
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}    

/**
 *  \brief          Set bit in the I2C register.
 *  \param[in]      register_address: address of the I2C register.
 *  \param[in]      bit_pos: position of the bit to be set.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NAME`_CONF_ERR if \ref bit_pos is out of range
 */
static uint8_t `$INSTANCE_NAME`_SetBit(uint8_t register_address,
                                        uint8_t bit_pos)
{
    if (bit_pos > 7)
    {
        return `$INSTANCE_NAME`_CONF_ERR;
    }
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(register_address, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Set bit of the register */
        temp_reg_value |= 1 << bit_pos;
        error = `$INSTANCE_NAME`_Write(register_address, temp_reg_value);
        
        /* Return error based on check */
        if ( error == `$INSTANCE_NAME`_OK)
        {
            return error;
        }
        else
        {
            return `$INSTANCE_NAME`_I2C_ERR;
        }
        
    }
    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}
/* [] END OF FILE */
