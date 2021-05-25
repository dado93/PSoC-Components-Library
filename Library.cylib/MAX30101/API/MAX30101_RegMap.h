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
    *   \brief          FIFO Configuration register.
    *   
    *   This register allows to configure the FIFO behaviour.
    
    *   It is structured as follows:
        <table>
        <caption id="fifo_conf">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td colspan=3, style="text-align:center">SMP_AVG[2:0]<td> FIFO_ROL_LOVER_EN<td colspan=4, style="text-align:center">FIFO_A_FULL[3:0]
        </table>
    *
    *   **Bits 7:5: Sample Averaging (SMP_AVE)**
    *
    *   To reduce the amount of data throughput, adjacent samples (in each individual channel)
    *   can be averaged and decimated on the chip by setting this register.
    *
    *   | SMP_AVG[2:0] | NO. OF SAMPLES AVG PER SAMPLE |
    *   |:------------:|:-----------------------------:|
    *   |   000        |  1 (no averaging)             |
    *   |   001        |                 2             |
    *   |   010        |                 4             |
    *   |   011        |                 8             |
    *   |   100        |                16             |
    *   |   101        |                32             |
    *   |   110        |                32             |
    *   |   111        |                32             |
    *
    *   **Bit 4: FIFO Rolls on Full (FIFO_ROLLOVER_EN)**
    *
    *   This bit controls the behavior of the FIFO when the FIFO becomes
    *   completely filled with data. If FIFO_ROLLOVER_EN is set (1), 
    *   the FIFO Address rolls over to zero and the FIFO continues to fill 
    *   with new data. If the bit is not set (0), then the FIFO is not updated 
    *   until FIFO_DATA is read or the WRITE/READ pointer positions are changed.
    *   
    *   **Bits 3:0: FIFO Almost Full Value (FIFO_A_FULL)**
    *   
    *   This register sets the number of data samples (3 bytes/sample) remaining in the FIFO when the interrupt is issued. 
    *   For example, if this field is set to 0x0, the interrupt is issued when there is 0 data samples remaining in the 
    *   FIFO (all 32 FIFO words have unread data). Furthermore, if this field is set to 0xF, the interrupt is issued when
    *   15 data samples are remaining in the FIFO (17 FIFO data samples have unread data).
    *   <table>
        <caption id="fifo_a_full">MAX30101 FIFO Almost Full Settings</caption>
        <tr><th>FIFO_A_FULL[3:0]<th>EMPTY DATA SAMPLES WHEN<br\>INTERRUPT IS ISSUED       <th>UNREAD DATA SAMPLES IN FIFO<br\>WHEN INTERRUPT IS ISSUED
        <tr><td>0x0h<td>0<td>32
        <tr><td>0x1h<td>1<td>31
        <tr><td>0x2h<td>2<td>30
        <tr><td>0x3h<td>3<td>29
        <tr><td>..<td>..<td>..
        <tr><td>0xFh<td>15 <td> 17
        </table>
    */
    #define `$INSTANCE_NAME`_FIFO_CONF_REGISTER 0x08
    
    /**
    *   \brief          MAX30101 Mode configuration register.
    *
    *   This register is structured as follows:
    *
        <table>
        <caption id="fifo_conf">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>SHDN<td>RESET<td>-<td>-<td>-<td colspan=3, style="text-align:center">MODE[2:0]
        </table>
    *
    *   **Bit 7: Shutdown Control (SHDN)**
    *
    *   The part can be put into a power-save mode by setting this bit to one. 
    *   While in power-save mode, all registers retain their values, and write/read operations function as normal.
    *   All interrupts are cleared to zero in this mode.
    *
    *   **Bit 6: Reset Control (RESET)**
    *   
    *   When the RESET bit is set to one, all configuration, threshold, and data registers are reset
    *   to their power-on-state through a power-on reset. The RESET bit is cleared automatically back 
    *   to zero after the reset sequence is completed. 
    *   Note: Setting the RESET bit does not trigger a PWR_RDY interrupt event.
    *
    *   **Bits 2:0: Mode Control**
    *
    *   These bits set the operating state of the MAX30101. Changing modes does not change any other setting,
    *   nor does it erase any previously stored data inside the data registers.
    *
       <table>
        <caption id="mode_table">MAX30101 Mode settings</caption>
        <tr><th>MODE[2:0]                      <th>MODE       <th>ACTIVE LED CHANNELS
        <tr><td>000<td colspan=2, style="text-align:center">Do not use
        <tr><td>001<td colspan=2, style="text-align:center">Do not use
        <tr><td>010<td> Heart Rate mode <td> Red only
        <tr><td>011<td> SpO2 mode <td> Red and IR
        <tr><td>100-110<td colspan=2, style="text-align:center">Do not use
        <tr><td>111<td> Multi-LED mode <td> Green, RED, and/or IR
        </table>
    */
    #define `$INSTANCE_NAME`_MODE_CONF_REGISTER 0x09
    
    /**
    *   \brief          Sp02 Configuration register.
    *
    *   This register configures the sensor for SpO2 mode.
    *
    *   It is structured as follows:
        <table>
        <caption id="spo2_conf">MAX30101 SpO2 Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0                      
        <tr><td>-<td colspan=2, style="text-align:center">SPO2_ADC_RGE[1:0]<td colspan=3, style="text-align:center">SPO2_SR[2:0]<td colspan=2, style="text-align:center"> LED_PW[1:0]
        </table>
    *
    *   **Bits 6:5: SpO2 ADC Range Control**
    *   This register sets the SpO2 sensor ADC’s full-scale range:
        <table>
        <caption id="spo2_adc_rge">MAX30101 SPo2 ADC Range Settings</caption>
        <tr><th>SPO2_ADC_RGE[1:0]<th>LSB SIZE (pA)<th>FULL SCALE (nA)
        <tr><td>00<td>7.81<td>2048
        <tr><td>01<td>15.63<td>4096
        <tr><td>02<td>31.25<td>8192
        <tr><td>03<td>62.5<td>16384
        </table>
    *
    *   **Bits 4:2: SpO2 Sample Rate Control**
    *
    *   These bits define the effective sampling rate with one sample consisting
    *   of one IR pulse/conversion, one RED pulse/ conversion, and one GREEN 
    *   pulse/conversion. The sample rate and pulse-width are related in that 
    *   the sample rate sets an upper bound on the pulse-width time.
    *   If the user selects a sample rate that is too high for the selected 
    *   LED_PW setting, the highest possible sample rate is programmed instead into the register.
    *
        <table>
        <caption id="spo2_sr">MAX30101 SPo2 Sample Rate Settings</caption>
        <tr><th>SPO2_SR[2:0]<th>SAMPLES PER SECOND
        <tr><td>000<td>50
        <tr><td>001<td>100
        <tr><td>010<td>200
        <tr><td>011<td>400
        <tr><td>101<td>800
        <tr><td>110<td>1600
        <tr><td>111<td>3200
        </table>
    *
    *   **Bits 1:0: LED Pulse Width Control and ADC Resolution**
    *   These bits set the LED pulse width (the IR, Red, and Green have the same pulse width), 
    *   and, therefore, indirectly sets the integration time of the ADC in each sample. 
    *   The ADC resolution is directly related to the integration time.
    *
        <table>
        <caption id="led_pw">MAX30101 LED Pulse Width Settings</caption>
        <tr><th>LED_PW[1:0]<th>PULSE WIDTH (uS) <th> ADC RESOLUTION (bits)
        <tr><td>00<td>69 (68.95) <td>15
        <tr><td>01<td>118 (117.78) <td> 16
        <tr><td>10<td>215 (215.44) <td> 17
        <tr><td>11<td>411 (410.75) <td> 18
        </table>
    */
    #define `$INSTANCE_NAME`_SPO2_CONF_REGISTER 0x0A
    
    /**
    *   \brief          MAX30101 LED1 Pulse Amplitude register.
    *
    *   This register allows to configure the pulse amplitude for LED1.
    *   The register is structured as follows:
        <table>
        <caption id="led_pa">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td colspan=8, style="text-align:center">LED1_PA[7:0]
        </table>
    *
    *   The pulse amplitude is determined by the followint table:
    *
        <table>
        <caption id="led_pa">MAX30101 LED Pulse Amplitude Settings</caption>
        <tr><th>LEDx_PA[7:0]<th>TYPICAL LED CURRENT (mA)
        <tr><td>0x00h<td>0.0
        <tr><td>0x01h<td>0.2
        <tr><td>0x02h<td>0.4
        <tr><td>...<td>...
        <tr><td>0x0fh<td>3.0
        <tr><td>...<td>...
        <tr><td>0x1fh<td>6.2
        <tr><td>...<td>...
        <tr><td>0x3fh<td>12.6
        <tr><td>...<td>...
        <tr><td>0x7fh<td>25.4
        <tr><td>...<td>...
        <tr><td>0xFFh<td>51.0
        </table>
    */
    #define `$INSTANCE_NAME`_LED1_PA_REGISTER 0x0C
    
    
    /**
    *   \brief          MAX30101 LED2 Pulse Amplitude register.
    *
    *   Please refer to \ref led_pa for the 
    *   configuration of this register.
    */
    #define `$INSTANCE_NAME`_LED2_PA_REGISTER 0x0D
    
    /**
    *   \brief          MAX30101 LED3 Pulse Amplitude register.
    *   
    *   Please refer to \ref led_pa for the 
    *   configuration of this register.
    */
    #define `$INSTANCE_NAME`_LED3_PA_REGISTER 0x0E
    
    /**
    *   \brief          MAX30101 LED4 Pulse Amplitude register.
    *
    *   Please refer to \ref led_pa for the 
    *   configuration of this register.
    */
    #define `$INSTANCE_NAME`_LED4_PA_REGISTER 0x0F
    
    /**
    *   \brief          MAX30101 Multi-LED Mode Configuration register - 1.
    *
    *   In multi-LED mode, each sample is split into up to four time slots, 
    *   SLOT1 through SLOT4. #MAX30101_MULTI_LED_1 and #MAX30101_MULTI_LED_2
    *   control registers determine which LED is active in each time slot, 
    *   making for a very flexible configuration. Each slot generates a 3-byte
    *   output into the FIFO. One sample comprises all active slots, for example
    *   if SLOT1 and SLOT2 are non-zero, then one sample is 2 x 3 = 6 bytes. 
    *   If SLOT1 through SLOT3 are all non-zero, then one sample is 3 x 3 = 9 bytes.
    *   The slots should be enabled in order (i.e., SLOT1 should not be disabled if SLOT2 
    *   or SLOT3 are enabled). 
    *   Both LED3 and LED4 are wired to Green LED. Green LED sinks current out 
    *   of #MAX30101_LED3_PA and #MAX30101_LED4_PA configuration in Multi-LED Mode 
    *   and SLOTx[2:0] = 011.
    *
    *   The register is structured as follows:
    *
    *   <table>
        <caption id="multi_led_1">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td colspan=3, style='text-align:center'>SLOT2[2:0]<td>-<td colspan=3, style="text-align:center">SLOT1[2:0]
        </table>
    *
    *   The settings for #MAX30101_MULTI_LED_1 and #MAX30101_MULTI_LED_2 registers
    *   allows to setup the following Multi-LED modes:
        <table>
        <caption id="multi_mode">MAX30101 Multi-LED Mode Configuration</caption>
        <tr><th>SLOTx[2:0] Setting <th>WHICH LED IS ACTIVE <th>LED PULSE AMPLITUDE SETTING
        <tr><td>000<td>None (time slot is disabled) <td>N/A (Off)
        <tr><td>001<td>LED1 (RED) <td> #MAX30101_LED1_PA
        <tr><td>010<td>LED2 (IR) <td>#MAX30101_LED2_PA
        <tr><td rowspan=2>011*<td>LED3 (GREEN) <td>#MAX30101_LED3_PA[7:0]
        <tr><td>LED4 (GREEN) <td>#MAX30101_LED4_PA[7:0]
        <tr><td>100<td>None <td>N/A (Off)
        <tr><td>101<td>RESERVED<td>RESERVED
        <tr><td>110<td>RESERVED<td>RESERVED
        <tr><td>111<td>RESERVED<td>RESERVED
        </table>
    *
    */
    #define `$INSTANCE_NAME`_MULTI_LED_1_REGISTER 0x11
    
    /**
    *   \brief          MAX30101 Multi-LED Mode Configuration register - 2.
    *
    *   Please refer to #MAX30101_MULTI_LED_1 for the explanation of the register.
    *   The register is structured as follows:
    *
    *   <table>
        <caption id="multi_led_2">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td colspan=3, style='text-align:center'>SLOT2[2:0]<td>-<td colspan=3, style="text-align:center">SLOT1[2:0]
        </table>
    */
    #define `$INSTANCE_NAME`_MULTI_LED_2_REGISTER 0x12
    
    //==============================================
    //        MAX30101 TEMPERATURE REGISTERS
    //==============================================
    
    /**
    *   \brief          MAX30101 Temperature Integer register.
    *
    *   The on-board temperature ADC output is split into two registers, 
    *   one to store the integer temperature and one to store the fraction. *
    *   Both should be read when reading the temperature data, 
    *   and the equation below shows how to add the two registers together:
    *   \f$T_{measured} = T_{integer} + T_{fraction}\f$.
    *
    *   This register stores the integer temperature data in 2’s complement format, 
    *   where each bit corresponds to 1°C.
    *
    *   <table>
        <caption id="temp_int">MAX30101 Temperature Integer Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td colspan=8, style="text-align:center">TINT[7:0]
        </table>

    *
        <table>
        <caption id="temp_int">MAX30101 Temperature Values</caption>
        <tr><th>REGISTER VALUE (hex)<th> TEMPERATURE (°C)
        <tr><td>0x00<td>0
        <tr><td>0x01<td>+1
        <tr><td>...<td>...
        <tr><td>0x7e<td>+126
        <tr><td>0x7f<td>+127
        <tr><td>0x80<td>-128
        <tr><td>0x81<td>-127
        <tr><td>...<td>...
        <tr><td>0xFE<td>-2
        <tr><td>0xFF<td>-1
        </table>
    */
    #define `$INSTANCE_NAME`_TEMP_INT_REGISTER   0x1F
    
    /**
    *   \brief          MAX30101 Temperature Fraction register.
    *
    *   This register stores the fractional temperature data in increments of 0.0625°C.
    *   If this fractional temperature is paired with a negative integer,
    *   it still adds as a positive fractional value (e.g., -128°C + 0.5°C = -127.5°C).
    *   This register is structured as follows:
    *
        <table>
        <caption id="temp_fract">MAX30101 Temperature Fraction Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td>-<td>-<td>-<td colspan=4, style="text-align:center">TFRAC[3:0]
        </table>

    *
    */
    #define `$INSTANCE_NAME`_TEMP_FRACT_REGISTER 0x20
    
    /**
    *   \brief          MAX30101 Temperature Configuration register..
    *
    *   This register has only one bit which is used to trigger 
    *   temperature measurements. This is a self-clearing bit which, when set, 
    *   initiates a single temperature reading from the temperature sensor. 
    *   This bit clears automatically back to zero at the conclusion of the 
    *   temperature reading when the bit is set to one.
    *   This register is structured as follows:
    *
        <table>
        <caption id="temp_en">MAX30101 Temperature Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td>-<td>-<td>-<td>-<td>-<td>-<td>TEMP_EN
        </table>
    *
    */
    #define `$INSTANCE_NAME`_TEMP_CONF_REGISTER    0x21
    
    //==============================================
    //        MAX30101 PART ID REGISTERS
    //==============================================
    
    /**
    *   \brief          MAX30101 Revision ID register.
    *   
    *   This register holds the value for the revision ID number
    *   of the MAX30101.
    */
    #define `$INSTANCE_NAME`_REVISION_ID_REGISTER    0xfe
    
    /**
    *   \brief          MAX30101 Part ID Register.
    *   
    *   This register holds the value for the revision ID number
    *   of the MAX30101: the expected value to be read is 0x15.
    */
    #define `$INSTANCE_NAME`_PART_ID_REGISTER    0xff

    #ifdef __cpluscplus
        }
    #endif
    
#endif
/* [] END OF FILE */
