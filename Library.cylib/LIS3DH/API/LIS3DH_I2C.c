/**
  *  \file           `$INSTANCE_NAME`_I2C.c
  *  \brief          Source file for `$INSTANCE_NAME` I2C interface.
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

#include "`$INSTANCE_NAME`_I2C.h"
#include "`$I2C_Master`.h"

/**
 *  \brief          Start the I2C master component.
 */
void `$INSTANCE_NAME`_I2C_Start(void) 
{
    `$I2C_Master`_Start();  
}

/**
 *  \brief          Stop the I2C master component.
 */
void `$INSTANCE_NAME`_I2C_Stop(void) 
{
    `$I2C_Master`_Stop();  
}

/**
 *  \brief          Read single I2C register from device.
 *
 *  \param[in]      device_address: the address of the I2C device to read data from.
 *  \param[in]      register_address: the address of the I2C device register.
 *  \param[out]     data: the data read from the device.
 *  \retval         #`$INSTANCE_NAME`_I2C_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_I2C_DEV_NOT_FOUND if device was not found.
 */
uint8_t `$INSTANCE_NAME`_I2C_ReadRegister(uint8_t device_address, 
                                        uint8_t register_address,
                                        uint8_t* data)
{
    // Send start condition
    uint8_t error = `$I2C_Master`_MasterSendStart(device_address,`$I2C_Master`_WRITE_XFER_MODE);
    if (error == `$I2C_Master`_MSTR_NO_ERROR)
    {
        // Write address of register to be read
        error = `$I2C_Master`_MasterWriteByte(register_address);
        if (error == `$I2C_Master`_MSTR_NO_ERROR)
        {
            // Send restart condition
            error = `$I2C_Master`_MasterSendRestart(device_address, `$I2C_Master`_READ_XFER_MODE);
            if (error == `$I2C_Master`_MSTR_NO_ERROR)
            {
                // Read data without acknowledgement
                *data = `$I2C_Master`_MasterReadByte(`$I2C_Master`_ACK_DATA);
                // Send stop condition and return no error
                `$I2C_Master`_MasterSendStop();
                return `$INSTANCE_NAME`_I2C_OK;
            }
        }
    }
    // Send stop condition 
    `$I2C_Master`_MasterSendStop();
    // Return error code
    return `$INSTANCE_NAME`_I2C_DEV_NOT_FOUND;
}

/**
 *  \brief          Read multiple I2C registers from device.
 *
 *  \param[in]      device_address: the address of the I2C device to read data from.
 *  \param[in]      register_address: the address of the I2C device register.
 *  \param[in]      register_count: total number of registers to be read.
 *  \param[out]     data: the data read from the device.
 *  \retval         #`$INSTANCE_NAME`_I2C_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_I2C_DEV_NOT_FOUND if device was not found.
 */
uint8_t `$INSTANCE_NAME`_I2C_ReadMultiRegister(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data)
{
    // Send start condition
    uint8_t error = `$I2C_Master`_MasterSendStart(device_address,`$I2C_Master`_WRITE_XFER_MODE);
    if (error == `$I2C_Master`_MSTR_NO_ERROR)
    {
        error = `$I2C_Master`_MasterWriteByte(register_address);
        
        if (error == `$I2C_Master`_MSTR_NO_ERROR)
        {
            // Send restart condition
            error = `$I2C_Master`_MasterSendRestart(device_address, `$I2C_Master`_READ_XFER_MODE);
            if (error == `$I2C_Master`_MSTR_NO_ERROR)
            {
                // Continue reading until we have register to read
                uint8_t counter = register_count;
                while( counter > 1 )
                {
                    data[register_count-counter] =
                        `$I2C_Master`_MasterReadByte(`$I2C_Master`_ACK_DATA);
                    counter--;
                }
                // Read last data without acknowledgement
                data[register_count-1] = `$I2C_Master`_MasterReadByte(`$I2C_Master`_NAK_DATA);
                // Send stop condition and return no error
                `$I2C_Master`_MasterSendStop();
                return `$INSTANCE_NAME`_I2C_OK;
            }
        }
    }
    // Send stop condition
    `$I2C_Master`_MasterSendStop();
    // Return error code
    return `$INSTANCE_NAME`_I2C_DEV_NOT_FOUND;
}

/**
 *  \brief          Write new data to a I2C register.
 *
 *  \param[in]      device_address: the address of the I2C device to write data to.
 *  \param[in]      register_address: the address of the I2C device register.
 *  \param[in]      data: the data to be written.
 *  \retval         #`$INSTANCE_NAME`_I2C_OK if no error occurred.
 *  \retval         #`$INSTANCE_NAME`_I2C_DEV_NOT_FOUND if device was not found.
 */
uint8_t `$INSTANCE_NAME`_I2C_WriteRegister(uint8_t device_address,
                                        uint8_t register_address,
                                        uint8_t data)
{
    // Send start condition
    uint8_t error = `$I2C_Master`_MasterSendStart(device_address, `$I2C_Master`_WRITE_XFER_MODE);
    if (error == `$I2C_Master`_MSTR_NO_ERROR)
    {
        // Write register address
        error = `$I2C_Master`_MasterWriteByte(register_address);
        if (error == `$I2C_Master`_MSTR_NO_ERROR)
        {
            // Write byte of interest
            error = `$I2C_Master`_MasterWriteByte(data);
            if (error == `$I2C_Master`_MSTR_NO_ERROR)
            {
                // Send stop condition
                `$I2C_Master`_MasterSendStop();
                // Return with no error
                return `$INSTANCE_NAME`_I2C_OK;
            }
        }
    }
    // Send stop condition 
    `$I2C_Master`_MasterSendStop();
    // Return error code
    return `$INSTANCE_NAME`_I2C_DEV_NOT_FOUND;
}
/* [] END OF FILE */
