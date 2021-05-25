/**
  *  \file           `$INSTANCE_NAME`.c
  *  \brief          Source file of `$INSTANCE_NAME` interface.
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

/*******************************************************
 *       `$INSTANCE_NAME` DIE TEMPERATURE FUNCTIONS
 ******************************************************/

/**
 *   \brief         Read Die Temperature in float format.
 *
 *   This functions reads the die temperature data from the MAX30101
 *   and returns its value in float format. The temperature value
 *   can be used to calibrate the SpO2 readings.
 *
 *   \param[out]    temperature: float value of die temperature
 *   \retval        \ref `$INSTANCE_NAME`_OK if no error occurred.
 *   \retval        \ref `$INSTANCE_NAME`_DEV_NOT_FOUND if device is not present on the I2C bus. 
 */
uint8_t `$INSTANCE_NAME`_ReadTemperature(float* temperature);

/* [] END OF FILE */
