/**
  *  \file           `$INSTANCE_NAME`.c
  *  \brief          Source file for LIS3DH interface.
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
#define `$INSTANCE_NAME`_X_AXIS_PARAM               0x01

/**
 *  \brief Parameter used for Y Axis in API Calls.
 */
#define `$INSTANCE_NAME`_Y_AXIS_PARAM               0x02

/**
 *  \brief Parameter used for Z Axis in API Calls.
 */
#define `$INSTANCE_NAME`_Z_AXIS_PARAM               0x03

/**
 *  \brief Parameter used for all Axis in API Calls.
 */
#define `$INSTANCE_NAME`_ALL_AXIS_PARAM             0x04

/**
 *  \brief Parameter used for ADC Channel 1 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_1_PARAM             0x01

/**
 *  \brief Parameter used for ADC Channel 2 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_2_PARAM             0x02

/**
 *  \brief Parameter used for ADC Channel 3 in API Calls.
 */
#define `$INSTANCE_NAME`_ADC_CH_3_PARAM             0x03

/**
 *  \brief Parameter used for ADC All Channels API Calls.
 */
#define `$INSTANCE_NAME`_ADC_ALL_CH_PARAM           0x04

/***********************************
*            Macros                *
************************************/



/***********************************
*     Function Decalarations       *
************************************/

static uint8_t `$INSTANCE_NAME`_Read(uint8_t register_address,
                                        uint8_t* value);

static uint8_t `$INSTANCE_NAME`_ReadRawData(uint8_t register_address,
                                        uint16_t* value);

static uint8_t `$INSTANCE_NAME`_ReadData(uint8_t register_address,
                                        uint16_t* value);

static uint8_t `$INSTANCE_NAME`_ReadMulti(uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* value);

static uint8_t `$INSTANCE_NAME`_Write(uint8_t register_address,
                                        uint8_t value);

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
    uint8_t     `$INSTANCE_NAME`_Init;   
    uint8_t     `$INSTANCE_NAME`_LowPowerEnabled; 
    uint8_t     `$INSTANCE_NAME`_FullScaleRange; 
} `$INSTANCE_NAME`_Config;


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
        error =`$INSTANCE_NAME`_ConnectPullUp();
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
        error =`$INSTANCE_NAME`_DisableTempSensor();
    }
    
    /* Check if we need to enable low power mode */
    if (`$en_low_power`)
    {
        error = `$INSTANCE_NAME`_EnableLowPowerMode();
    }
    else
    {
        error =`$INSTANCE_NAME`_DisableLowPowerMode();
    }
    
    /* Set output data rate */
    error = `$INSTANCE_NAME`_SetOutputDataRate(`$acc_odr`);
    
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
 *  \retval         #`$INSTANCE_NANE`_I2C_ERR if error occurred during I2C communication.
 */
uint8_t `$INSTANCE_NAME`_DisconnectPullUp(void)
{
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, 7);
}

/**
 *  \brief          Connect Pull-Up resistor to SDO/SA0 pin.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_I2C_ERR if error occurred during I2C communication.
 */
uint8_t `$INSTANCE_NAME`_ConnectPullUp(void)
{
    return `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, 7);
}

/**
 *  \brief          Enable ADC.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableADC(void)
{
    /* Set bit 7 of TEMP_CFG_REG */
    return `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_TEMP_CFG_REGISTER, 7);
    
}

/**
 *  \brief          Enable temperature sensor.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_EnableLowPowerMode(void)
{
    /* Set bit 3 of CTRL_REG1 */
    uint8_t error = `$INSTANCE_NAME`_SetBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 3);  
    if ( error == `$INSTANCE_NAME`_OK)
    {
        `$INSTANCE_NAME`_low_power_enabled = 1;
    }
    return error;
}

/**
 *  \brief          Disable low power mode.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
 */
uint8_t `$INSTANCE_NAME`_DisableLowPowerMode(void)
{
    /* Clear bit 3 of CTRL_REG1 */
    uint8_t error = `$INSTANCE_NAME`_ClearBit(`$INSTANCE_NAME`_CTRL_REG1_REGISTER, 3);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        `$INSTANCE_NAME`_low_power_enabled = 0;
    }
    return error;
}

/**
 *  \brief          Enable X Axis.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if parameter error.
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
/***********************************
*      Axis Overrun Functions      *
************************************/

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
 *  \brief          Check if any axis has overrun.
 *  \param[out]     overrun : 1 if any axis has ovverun, 0 otherwise.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref axis is out of range
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

/***********************************
*      ADC Overrun Functions       *
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref axis is out of range
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

/***********************************
*      Axis New Data Functions     *
************************************/

/**
 *  \brief          Check if X axis has new data.
 *  \param[out]     overrun : 1 if X axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_XAxisDHasNewData(uint8_t* new_data)
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
 *  \param[out]     overrun : 1 if Z axis has new data, 0 otherwise.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
uint8_t `$INSTANCE_NAME`_ZAxisHasNewData(uint8_t* new_data)
{
    return `$INSTANCE_NAME`_CheckAxisNewData(`$INSTANCE_NAME`_Z_AXIS_PARAM, new_data);
}

/**
 *  \brief          Check if any axis has new data.
 *  \param[out]     new_data : 1 if any axis has new data, 0 otherwise.
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref axis is out of range
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

/***********************************
*      ADC New Data Functions     *
************************************/

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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref axis is out of range
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

/***********************************
*        ADC Read Functions        *
************************************/
uint8_t `$INSTANCE_NAME`_ADC1ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawData(`$INSTANCE_NAME`_OUT_ADC_1_L_REGISTER, data);
}
    
uint8_t `$INSTANCE_NAME`_ADC1Read(int16_t* data)
{
    
}

uint8_t `$INSTANCE_NAME`_ADC2ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawData(`$INSTANCE_NAME`_OUT_ADC_2_L_REGISTER, data);
}

uint8_t `$INSTANCE_NAME`_ADC2Read(int16_t* data)
{
    
}

uint8_t `$INSTANCE_NAME`_ADC3ReadRaw(uint16_t* data)
{
    return `$INSTANCE_NAME`_ReadRawData(`$INSTANCE_NAME`_OUT_ADC_3_L_REGISTER, data);
}

uint8_t `$INSTANCE_NAME`_ADC3Read(int16_t* data)
{
    
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
    uint8_t error = `$INSTANCE_NAME`_I2C_ReadRegister(`$I2C_Address`, register_address, &temp_value);
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
    uint8_t temp[register_count];
    uint8_t error = `$INSTANCE_NAME`_I2C_ReadMultiRegister(`$I2C_Address`, 
                                                            register_address,
                                                            register_count,
                                                            temp);
    if (error == `$INSTANCE_NAME`_I2C_OK)
    {
        data = temp;
        return `$INSTANCE_NAME`_OK;
    }

    return `$INSTANCE_NAME`_DEV_NOT_FOUND;
}    

/**
 *  \brief          Read raw 10-bit data from I2C registers.
 *  \param[in]      register_address: the starting address for I2C read operation.
 *  \param[out]     value: the raw 10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadRawData(uint8_t register_address,
                                        uint16_t* value)
{
    uint8_t temp_data[2];
    uint8_t error = `$INSTANCE_NAME`_ReadMulti(register_address, 2, temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        *value = (((uint16_t)temp_data[1])) << 8 | temp_data[0];
    }
    return error;
}

/*
 *  \brief          Read data in two's complement format from I2C registers.
 *  \param[in]      register_address: the starting address for I2C read operation.
 *  \param[out]     value: the floating point 8/10-bit data read from the device.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 */
static uint8_t `$INSTANCE_NAME`_ReadData(uint8_t register_address,
                                        float* value)
{
    /* Get raw 10 bits */
    uint16_t temp_data;
    uint8_t error = `$INSTANCE_NAME`_ReadRawData(register_address, &temp_data);
    if ( error == `$INSTANCE_NAME`_OK )
    {
        /* Convert in two's complement */
        
    }
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
    uint8_t error = `$INSTANCE_NAME`_I2C_WriteRegister(`$I2C_Address`, register_address, value);
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref bit_pos is out of range
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
 *  \retval         #`$INSTANCE_NANE`_CONF_ERR if \ref bit_pos is out of range
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
