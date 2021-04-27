/**
  *  \file           LIS3DH.c
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
#include "`$INSTANCE_NAME`_I2C.h"

/***********************************
*          API Constants           *
************************************/
/**
 *  \brief          WHO AM I register value.
 */
#define `$INSTANCE_NAME`_WHO_AM_I_VALUE         0x33

/**
 *  \brief          WHO AM I register address.
 */
#define `$INSTANCE_NAME`_WHO_AM_I_REGISTER      0x0F

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
    uint8_t who_am_i = 0;
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
        `$INSTANCE_NAME`_DisconnectPullUp();
    }
    else
    {
        `$INSTANCE_NAME`_ConnectPullUp();
    }
    
}

uint8_t `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_I2C_Stop();
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
uint8_t `$INSTANCE_NAME`_DisconnectPullUp(void)
{
    
}

uint8_t `$INSTANCE_NAME`_ConnectPullUp(void)
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
