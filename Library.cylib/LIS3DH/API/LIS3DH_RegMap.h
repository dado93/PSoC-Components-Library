/**
  *  \file           `$INSTANCE_NAME`_RegMap.h
  *  \brief          Map of `$INSTANCE_NAME` I2C registers.
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


#ifndef __`$INSTANCE_NAME`_REGMAP_H__
    #define __`$INSTANCE_NAME`_REGMAP_H__
    
    #ifdef __cpluscplus 
        extern "C" {
    #endif

    /**
     *  \brief          Status register aux address.
     */
    #define `$INSTANCE_NAME`_STATUS_REG_AUX_REGISTER    0x07

    /**
     *  \brief          Out ADC1 low byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_1_L_REGISTER       0x08

    /**
     *  \brief          Out ADC1 high byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_1_H_REGISTER       0x09

    /**
     *  \brief          Out ADC2 low byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_2_L_REGISTER       0x0A

    /**
     *  \brief          Out ADC2 high byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_2_H_REGISTER       0x0B

    /**
     *  \brief          Out ADC3 low byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_3_L_REGISTER       0x0C

    /**
     *  \brief          Out ADC3 high byte register aux address.
     */
    #define `$INSTANCE_NAME`_OUT_ADC_3_H_REGISTER       0x0D

    /**
     *  \brief          WHO AM I register address.
     */
    #define `$INSTANCE_NAME`_WHO_AM_I_REGISTER          0x0F

    /**
     *  \brief          Control register 0 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG0_REGISTER         0x1E

    /**
     *  \brief          Temperature configuration register address.
     */
    #define `$INSTANCE_NAME`_TEMP_CFG_REGISTER      0x1F

    /**
     *  \brief          Control register 1 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG1_REGISTER         0x20

    /**
     *  \brief          Control register 2 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG2_REGISTER         0x21

    /**
     *  \brief          Control register 3 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG3_REGISTER         0x22

    /**
     *  \brief          Control register 4 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG4_REGISTER         0x23
    
    /**
     *  \brief          Control register 5 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG5_REGISTER         0x24
    
    /**
     *  \brief          Control register 6 register address.
     */
    #define `$INSTANCE_NAME`_CTRL_REG6_REGISTER         0x25
    
    /**
     *  \brief          Control register 6 register address.
     */
    #define `$INSTANCE_NAME`_REFERENCE_REGISTER         0x26
    
    /**
     *  \brief          Status register address.
     */
    #define `$INSTANCE_NAME`_STATUS_REGISTER            0x27
    
    /**
     *  \brief          Out X low register address.
     */
    #define `$INSTANCE_NAME`_OUT_X_L_REGISTER           0x28
    
    /**
     *  \brief          Out X high register address.
     */
    #define `$INSTANCE_NAME`_OUT_X_H_REGISTER           0x29
    
    /**
     *  \brief          Out Y low register address.
     */
    #define `$INSTANCE_NAME`_OUT_Y_L_REGISTER           0x2A
    
    /**
     *  \brief          Out Y high register address.
     */
    #define `$INSTANCE_NAME`_OUT_Y_H_REGISTER           0x2B
    
    /**
     *  \brief          Out Z low register address.
     */
    #define `$INSTANCE_NAME`_OUT_Z_L_REGISTER           0x2C
    
    /**
     *  \brief          Out Z high register address.
     */
    #define `$INSTANCE_NAME`_OUT_Z_H_REGISTER           0x2D
    
    /**
     *  \brief          FIFO control register address.
     */
    #define `$INSTANCE_NAME`_FIFO_CTRL_REGISTER         0x2E
    
    /**
     *  \brief          FIFO SRC register address.
     */
    #define `$INSTANCE_NAME`_FIFO_SRC_REGISTER          0x2F
    
    /**
     *  \brief          Interrupt 1 configuration register address.
     */
    #define `$INSTANCE_NAME`_INT1_CFG_REGISTER          0x30
    
    /**
     *  \brief          Interrupt 1 source register address.
     */
    #define `$INSTANCE_NAME`_INT1_SRC_REGISTER          0x31
    
    /**
     *  \brief          Interrupt 1 threshold register address.
     */
    #define `$INSTANCE_NAME`_INT1_THS_REGISTER          0x32
    
    /**
     *  \brief          Interrupt 1 duration register address.
     */
    #define `$INSTANCE_NAME`_INT1_DURATION_REGISTER     0x33
    
    /**
     *  \brief          Interrupt 2 configuration register address.
     */
    #define `$INSTANCE_NAME`_INT2_CFG_REGISTER          0x34
    
    /**
     *  \brief          Interrupt 2 source register address.
     */
    #define `$INSTANCE_NAME`_INT2_SRC_REGISTER          0x35
    
    /**
     *  \brief          Interrupt 2 threshold register address.
     */
    #define `$INSTANCE_NAME`_INT2_THS_REGISTER          0x36
    
    /**
     *  \brief          Interrupt 2 duration register address.
     */
    #define `$INSTANCE_NAME`_INT2_DURATION_REGISTER     0x37
    
    /**
     *  \brief          Click configuration register address.
     */
    #define `$INSTANCE_NAME`_CLICK_CFG_REGISTER         0x38
    
    /**
     *  \brief          Click source register address.
     */
    #define `$INSTANCE_NAME`_CLICK_SRC_REGISTER         0x39
    
    /**
     *  \brief          Click threshold register address.
     */
    #define `$INSTANCE_NAME`_CLICK_THS_REGISTER         0x3A
    
    /**
     *  \brief          Time limit register address.
     */
    #define `$INSTANCE_NAME`_TIME_LIMIT_REGISTER        0x3B
    
    /**
     *  \brief          Time latency register address.
     */
    #define `$INSTANCE_NAME`_TIME_LATENCY_REGISTER      0x3C
    
    /**
     *  \brief          Time window register address.
     */
    #define `$INSTANCE_NAME`_TIME_WINDOW_REGISTER       0x3D
    
    /**
     *  \brief          Active threshold register address.
     */
    #define `$INSTANCE_NAME`_ACT_THS_REGISTER           0x3E
    
    /**
     *  \brief          Active duration register address.
     */
    #define `$INSTANCE_NAME`_ACT_DUR_REGISTER           0x3F

    #ifdef __cpluscplus
        }
    #endif
    
#endif
/* [] END OF FILE */
