/**
  *  \file           ICM20948_RegMap.h
  *  \brief          Register Map ICM20948 interface.
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

#ifndef __ICM20948_REG_MAP_H__
    #define __ICM20948_REG_MAP_H__
    
    /**
     *  \brief          WHO AM I Register Address.
     */
    #define ICM20948_WHO_AM_I_REGISTER          0x00
    #define ICM20948_USER_CTRL_REGISTER         0x03
    #define ICM20948_LP_CONFIG_REGISTER         0x05
    #define ICM20948_PWR_MGMT_1_REGISTER        0x06
    #define ICM20948_PWR_MGMT_2_REGISTER        0x07
    #define ICM20948_INT_PIN_CFG_REGISTER       0x0F
    #define ICM20948_INT_ENABLE_REGISTER        0x10
    #define ICM20948_INT_ENABLE_1_REGISTER      0x11
    #define ICM20948_INT_ENABLE_2_REGISTER      0x12
    #define ICM20948_INT_ENABLE_3_REGISTER      0x13
    #define ICM20948_I2C_MST_STATUS_REGISTER    0x17
    #define ICM20948_INT_STATUS_REGISTER        0x19
    #define ICM20948_INT_STATUS_1_REGISTER      0x1A
    #define ICM20948_INT_STATUS_2_REGISTER      0x1B
    #define ICM20948_INT_STATUS_3_REGISTER      0x1C
    #define ICM20948_DELAY_TIMEH_REGISTER       0x28
    #define ICM20948_DELAY_TIMEL_REGISTER       0x29
    #define ICM20948_ACCEL_XOUT_H_REGISTER      0x2D
    #define ICM20948_ACCEL_XOUT_L_REGISTER      0x2E
    #define ICM20948_ACCEL_YOUT_H_REGISTER      0x2F
    #define ICM20948_ACCEL_YOUT_L_REGISTER      0x30
    #define ICM20948_ACCEL_ZOUT_H_REGISTER      0x31
    #define ICM20948_ACCEL_ZOUT_L_REGISTER      0x32
    #define ICM20948_GYRO_XOUT_H_REGISTER       0x33
    #define ICM20948_GYRO_XOUT_L_REGISTER       0x34
    #define ICM20948_GYRO_YOUT_H_REGISTER       0x35
    #define ICM20948_GYRO_YOUT_L_REGISTER       0x36
    #define ICM20948_GYRO_ZOUT_H_REGISTER       0x37
    #define ICM20948_GYRO_ZOUT_L_REGISTER       0x38
    #define ICM20948_TEMP_OUT_H_REGISTER        0x39
    #define ICM20948_TEMP_OUT_L_REGISTER        0x3A
    
#endif
    
/* [] END OF FILE */
