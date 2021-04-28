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

#define `$INSTANCE_NAME`_X_AXIS_PARAM               0x01
#define `$INSTANCE_NAME`_Y_AXIS_PARAM               0x02
#define `$INSTANCE_NAME`_Z_AXIS_PARAM               0x03
#define `$INSTANCE_NAME`_ALL_AXIS_PARAM             0x04

#define `$INSTANCE_NAME`_ADC_CH_1_PARAM             0x01
#define `$INSTANCE_NAME`_ADC_CH_2_PARAM             0x02
#define `$INSTANCE_NAME`_ADC_CH_3_PARAM             0x03
#define `$INSTANCE_NAME`_ADC_ALL_CH_PARAM           0x04
/***********************************
*            Macros                *
************************************/
#define `$INSTANCE_NAME`_ClearBit(value, bit_pos)   value = 


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

static uint8_t `$INSTANCE_NAME`_CheckAxisOverrun(uint8_t axis, uint8_t* overrun);

static uint8_t `$INSTANCE_NAME`_CheckAxisNewData(uint8_t axis, uint8_t* new_data);

static uint8_t `$INSTANCE_NAME`_CheckADCOverrun(uint8_t axis, uint8_t* overrun);

static uint8_t `$INSTANCE_NAME`_CheckADCNewData(uint8_t axis, uint8_t* new_data);

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
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Set bit 7 of the register */
        temp_reg_value |= 1 << 7;
        error = `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, temp_reg_value);
        
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
 *  \brief          Connect Pull-Up resistor to SDO/SA0 pin.
 *  \retval         #`$INSTANCE_NAME`_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_DEV_NOT_FOUND if device was not found on the bus.
 *  \retval         #`$INSTANCE_NANE`_I2C_ERR if error occurred during I2C communication.
 */
uint8_t `$INSTANCE_NAME`_ConnectPullUp(void)
{
    /* Read register value */
    uint8_t temp_reg_value, error;
    error = `$INSTANCE_NAME`_Read(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, &temp_reg_value);
    if ( error == `$INSTANCE_NAME`_OK)
    {
        /* Clear bit 7 of the register */
        temp_reg_value &= ~(1 << 7);
        error = `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_CTRL_REG0_REGISTER, temp_reg_value);
        
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
/* [] END OF FILE */
