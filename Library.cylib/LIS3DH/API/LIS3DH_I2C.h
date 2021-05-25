/**
  *  \file           LIS3DH_I2C.h
  *  \brief          Header file for LIS3DH I2C interface.
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

#ifndef __`$INSTANCE_NAME`_I2C_H__
    #define __`$INSTANCE_NAME`_I2C_H__
    
    #ifdef __cpluscplus 
        extern "C" {
    #endif
    
    #include "cytypes.h"
    #include "cyfitter.h"
        
    /***********************************
    *           API Constants          *
    ************************************/
    
    /**
     *  \brief          No error occurred during I2C transaction.
     */
    #define `$INSTANCE_NAME`_I2C_OK                 0
    
    /**
     *  \brief          I2C device was not found on bus.
     */
    #define `$INSTANCE_NAME`_I2C_DEV_NOT_FOUND      1
    
    
    /***********************************
    *       Generic Functions          *
    ************************************/
    void `$INSTANCE_NAME`_I2C_Start(void);
    void `$INSTANCE_NAME`_I2C_Stop(void);
    
    /************************************
    *       I2C Read Functions          *
    *************************************/
    uint8_t `$INSTANCE_NAME`_I2C_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    
    uint8_t `$INSTANCE_NAME`_I2C_ReadMultiRegister(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data);
    
    /************************************
    *       I2C Write Functions         *
    *************************************/
    uint8_t `$INSTANCE_NAME`_I2C_WriteRegister(uint8_t device_address,
                                        uint8_t register_address,
                                        uint8_t data);
    
    #ifdef __cpluscplus
        }
    #endif
    
#endif

/* [] END OF FILE */
