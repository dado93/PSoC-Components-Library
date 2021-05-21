/**
  *  \file           `$INSTANCE_NAME`_RegMap.h
  *  \brief          Register Map `$INSTANCE_NAME` interface.
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

#ifndef __`$INSTANCE_NAME`_REG_MAP_H__
    #define __`$INSTANCE_NAME`_REG_MAP_H__
    
    
    #define `$INSTANCE_NAME`_WHO_AM_I_REGISTER          0x00
    #define `$INSTANCE_NAME`_USER_CTRL_REGISTER         0x03
    #define `$INSTANCE_NAME`_LP_CONFIG_REGISTER         0x05
    #define `$INSTANCE_NAME`_PWR_MGMT_1_REGISTER        0x06
    #define `$INSTANCE_NAME`_PWR_MGMT_2_REGISTER        0x07
    #define `$INSTANCE_NAME`_INT_PIN_CFG_REGISTER       0x0F
    #define `$INSTANCE_NAME`_INT_ENABLE_REGISTER        0x10
    #define `$INSTANCE_NAME`_INT_ENABLE_1_REGISTER      0x11
    #define `$INSTANCE_NAME`_INT_ENABLE_2_REGISTER      0x12
    #define `$INSTANCE_NAME`_INT_ENABLE_3_REGISTER      0x13
    #define `$INSTANCE_NAME`_I2C_MST_STATUS_REGISTER    0x17
    #define `$INSTANCE_NAME`_INT_STATUS_REGISTER        0x19
    #define `$INSTANCE_NAME`_INT_STATUS_1_REGISTER      0x1A
    #define `$INSTANCE_NAME`_INT_STATUS_2_REGISTER      0x1B
    #define `$INSTANCE_NAME`_INT_STATUS_3_REGISTER      0x1C
    #define `$INSTANCE_NAME`_DELAY_TIMEH_REGISTER       0x28
    #define `$INSTANCE_NAME`_DELAY_TIMEL_REGISTER       0x29
    #define `$INSTANCE_NAME`_ACCEL_XOUT_H_REGISTER      0x2D
    #define `$INSTANCE_NAME`_ACCEL_XOUT_L_REGISTER      0x2E
    #define `$INSTANCE_NAME`_ACCEL_YOUT_H_REGISTER      0x2F
    #define `$INSTANCE_NAME`_ACCEL_YOUT_L_REGISTER      0x30
    #define `$INSTANCE_NAME`_ACCEL_ZOUT_H_REGISTER      0x31
    #define `$INSTANCE_NAME`_ACCEL_ZOUT_L_REGISTER      0x32
    #define `$INSTANCE_NAME`_GYRO_XOUT_H_REGISTER       0x33
    #define `$INSTANCE_NAME`_GYRO_XOUT_L_REGISTER       0x34
    #define `$INSTANCE_NAME`_GYRO_YOUT_H_REGISTER       0x35
    #define `$INSTANCE_NAME`_GYRO_YOUT_L_REGISTER       0x36
    #define `$INSTANCE_NAME`_GYRO_ZOUT_H_REGISTER       0x37
    #define `$INSTANCE_NAME`_GYRO_ZOUT_L_REGISTER       0x38
    #define `$INSTANCE_NAME`_TEMP_OUT_H_REGISTER        0x39
    #define `$INSTANCE_NAME`_TEMP_OUT_L_REGISTER        0x3A
    
#endif
    
/* [] END OF FILE */
