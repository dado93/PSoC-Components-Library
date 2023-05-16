/**
*   \file       `$INSTANCE_NAME`_Defs.h
*   
*   \brief      Defines for `$INSTANCE_NAME`.
*   \author     Davide Marzorati
*/

#ifndef __`$INSTANCE_NAME`_DEFS_H__
    #define __`$INSTANCE_NAME`_DEFS_H__
    
    #include "cytypes.h"
    
    //==============================================
    //              `$INSTANCE_NAME` ERRORS
    //==============================================
    /**
    *   \brief I2C Address of `$INSTANCE_NAME`.
    */
    #define `$INSTANCE_NAME`_I2C_ADDRESS 0x57
    
    /**
    *   \brief Error condition triggered when device is not found on I2C bus.
    */
    #define `$INSTANCE_NAME`_DEV_NOT_FOUND 1
    
    /**
    *   \brief No error generated.
    */
    #define `$INSTANCE_NAME`_OK 0
    
    /**
    *   \brief Generic error condition related to `$INSTANCE_NAME`.
    */
    #define `$INSTANCE_NAME`_ERROR 2
    
    //==============================================
    //  `$INSTANCE_NAME` MACROS FOR REGISTERS CONFIGURATION
    //==============================================
    
    /**
    *   \brief `$INSTANCE_NAME` Heart Rate mode.
    */
    #define `$INSTANCE_NAME`_HR_MODE 0x02
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 mode.
    */
    #define `$INSTANCE_NAME`_SPO2_MODE 0x03

    /**
    *   \brief `$INSTANCE_NAME` Multi LED mode.
    */
    #define `$INSTANCE_NAME`_MULTI_MODE 0x07
    
    /**
    *   \brief `$INSTANCE_NAME` LED channel 1 (RED).
    */
    #define `$INSTANCE_NAME`_LED_1 0x00
    
    /**
    *   \brief `$INSTANCE_NAME` LED channel 2 (IR).
    */
    #define `$INSTANCE_NAME`_LED_2 0x01
    
    /**
    *   \brief `$INSTANCE_NAME` LED channel 3 (GREEN).
    */
    #define `$INSTANCE_NAME`_LED_3 0x02
    
    /**
    *   \brief `$INSTANCE_NAME` LED channel 4 (GREEN).
    */
    #define `$INSTANCE_NAME`_LED_4 0x03
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_1 0x00
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_2 0x20
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_4 0x40
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_8 0x60
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_16 0x80
    
    /**
    *   \brief `$INSTANCE_NAME` no average in FIFO.
    */
    #define `$INSTANCE_NAME`_SAMPLE_AVG_32 0xA0
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 range set to 2048 nA.
    */
    #define `$INSTANCE_NAME`_ADC_RANGE_2048  0x00
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 range set to 4096 nA.
    */
    #define `$INSTANCE_NAME`_ADC_RANGE_4096  0x20
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 range set to 8192 nA.
    */
    #define `$INSTANCE_NAME`_ADC_RANGE_8192  0x40
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 range set to 16384 nA.
    */
    #define `$INSTANCE_NAME`_ADC_RANGE_16384 0x60
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set to 50 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_50 0x00
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set to 100 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_100 0x04
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 200 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_200 0x08
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 400 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_400 0x0C
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 800 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_800 0x10
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 1000 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_1000 0x14
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 1600 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_1600 0x18
    
    /**
    *   \brief `$INSTANCE_NAME` SpO2 sample rate set tot 3200 samples.
    */
    #define `$INSTANCE_NAME`_SAMPLE_RATE_3200 0x1C
    
    /**
    *   \brief `$INSTANCE_NAME` Pulse Width set to 69.
    */
    #define `$INSTANCE_NAME`_PULSEWIDTH_69	    0x00
    
    /**
    *   \brief `$INSTANCE_NAME` Pulse Width set to 118.
    */
    #define `$INSTANCE_NAME`_PULSEWIDTH_118  	0x01
    
    /**
    *   \brief `$INSTANCE_NAME` Pulse Width set to 215.
    */
    #define `$INSTANCE_NAME`_PULSEWIDTH_215  	0x02
    
    /**
    *   \brief `$INSTANCE_NAME` Pulse Width set to 411.
    */
    #define `$INSTANCE_NAME`_PULSEWIDTH_411  	0x03
    
    /**
    *   \brief `$INSTANCE_NAME` Slot RED enabled.
    */
    #define `$INSTANCE_NAME`_SLOT_RED   0x01
    
    /**
    *   \brief `$INSTANCE_NAME` Slot IR enabled.
    */
    #define `$INSTANCE_NAME`_SLOT_IR    0x02
    
    /**
    *   \brief `$INSTANCE_NAME` Slot GREEN enabled.
    */
    #define `$INSTANCE_NAME`_SLOT_GREEN 0x03
    
    /**
    *   \brief `$INSTANCE_NAME` No Slot enabled.
    */
    #define `$INSTANCE_NAME`_SLOT_NONE  0x00

/* [] END OF FILE */
