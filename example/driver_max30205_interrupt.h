/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_max30205_interrupt.h
 * @brief     driver max30205 interrupt header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/13  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/25  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_MAX30205_INTERRUPT_H
#define DRIVER_MAX30205_INTERRUPT_H

#include "driver_max30205_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup max30205_example_driver
 * @{
 */

/**
 * @brief max30205 interrupt example default definition
 */
#define MAX30205_INTERRUPT_DEFAULT_DATA_FORMAT                MAX30205_DATA_FORMAT_NORMAL               /**< normal data format */
#define MAX30205_INTERRUPT_DEFAULT_FAULT_QUEUE                MAX30205_FAULT_QUEUE_2                    /**< fault queue 2 */
#define MAX30205_INTERRUPT_DEFAULT_PIN_POLARITY               MAX30205_PIN_POLARITY_LOW                 /**< polarity low */
#define MAX30205_INTERRUPT_DEFAULT_BUS_TIMEOUT                MAX30205_BUS_TIMEOUT_DISABLE              /**< disable bus timeout */

/**
 * @brief     interrupt example init
 * @param[in] addr_pin iic device address
 * @param[in] mode interrupt mode
 * @param[in] low interrupt low threshold
 * @param[in] high interrupt high threshold
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t max30205_interrupt_init(max30205_address_t addr_pin, max30205_interrupt_mode_t mode, float low, float high);

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max30205_interrupt_deinit(void);

/**
 * @brief      interrupt example read
 * @param[out] *s pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t max30205_interrupt_read(float *s);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
