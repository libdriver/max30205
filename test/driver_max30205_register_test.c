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
 * @file      driver_max30205_register_test.c
 * @brief     driver max30205 register test source file
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

#include "driver_max30205_register_test.h"
#include <math.h>

static max30205_handle_t gs_handle;        /**< max30205 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t max30205_register_test(max30205_address_t addr)
{
    uint8_t res;
    int16_t reg;
    int16_t threshold;
    float s;
    max30205_info_t info;
    max30205_address_t addr_pin;
    max30205_data_format_t format;
    max30205_interrupt_mode_t mode;
    max30205_fault_queue_t fault_queue;
    max30205_pin_polarity_t polarity;
    max30205_bus_timeout_t bus_timeout;
    
    /* link interface function */
    DRIVER_MAX30205_LINK_INIT(&gs_handle, max30205_handle_t);
    DRIVER_MAX30205_LINK_IIC_INIT(&gs_handle, max30205_interface_iic_init);
    DRIVER_MAX30205_LINK_IIC_DEINIT(&gs_handle, max30205_interface_iic_deinit);
    DRIVER_MAX30205_LINK_IIC_READ(&gs_handle, max30205_interface_iic_read);
    DRIVER_MAX30205_LINK_IIC_WRITE(&gs_handle, max30205_interface_iic_write);
    DRIVER_MAX30205_LINK_DELAY_MS(&gs_handle, max30205_interface_delay_ms);
    DRIVER_MAX30205_LINK_DEBUG_PRINT(&gs_handle, max30205_interface_debug_print);
    
    /* get information */
    res = max30205_info(&info);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        max30205_interface_debug_print("max30205: chip is %s.\n", info.chip_name);
        max30205_interface_debug_print("max30205: manufacturer is %s.\n", info.manufacturer_name);
        max30205_interface_debug_print("max30205: interface is %s.\n", info.interface);
        max30205_interface_debug_print("max30205: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max30205_interface_debug_print("max30205: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max30205_interface_debug_print("max30205: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max30205_interface_debug_print("max30205: max current is %0.2fmA.\n", info.max_current_ma);
        max30205_interface_debug_print("max30205: max temperature is %0.1fC.\n", info.temperature_max);
        max30205_interface_debug_print("max30205: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    max30205_interface_debug_print("max30205: start register test.\n");
    max30205_interface_debug_print("max30205: max30205_set_addr_pin/max30205_get_addr_pin test.\n");
    
    /* set ADDRESS_0 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_0);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_0.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_0?"ok":"error");
    
    /* set ADDRESS_1 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1?"ok":"error");
    
    /* set ADDRESS_2 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_2);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_2.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_2?"ok":"error");
    
    /* set ADDRESS_3 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_3);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_3.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_3?"ok":"error");
    
    /* set ADDRESS_4 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_4);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_4.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_4?"ok":"error");
    
    /* set ADDRESS_5 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_5);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_5.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_5?"ok":"error");
    
    /* set ADDRESS_6 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_6);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_6.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_6?"ok":"error");
    
    /* set ADDRESS_7 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_7);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_7.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_7?"ok":"error");
    
    /* set ADDRESS_8 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_8);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_8.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_8?"ok":"error");
    
    /* set ADDRESS_9 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_9);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_9.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_9?"ok":"error");
    
    /* set ADDRESS_A */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_A);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_A.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_A?"ok":"error");
    
    /* set ADDRESS_B */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_B);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_B.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_B?"ok":"error");
    
    /* set ADDRESS_C */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_C);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_C.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_C?"ok":"error");
    
    /*set ADDRESS_D */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_D);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_D.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_D?"ok":"error");
    
    /* set ADDRESS_E */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_E);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_E.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_E?"ok":"error");
    
    /* set ADDRESS_F */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_F);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_F.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_F?"ok":"error");
    
    /* set ADDRESS_10 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_10);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_10.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_10?"ok":"error");
    
    /* set ADDRESS_11 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_11);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_11.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_11?"ok":"error");
    
    /* set ADDRESS_12 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_12);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_12.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_12?"ok":"error");
    
    /* set ADDRESS_13 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_13);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_13.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_13?"ok":"error");
    
    /* set ADDRESS_14 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_14);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_14.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_14?"ok":"error");
    
    /* set ADDRESS_15 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_15);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_15.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_15?"ok":"error");
    
    /* set ADDRESS_16 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_16);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_16.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_16?"ok":"error");
    
    /* set ADDRESS_17 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_17);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_17.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_17?"ok":"error");
    
    /* set ADDRESS_18 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_18);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_18.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_18?"ok":"error");
    
    /* set ADDRESS_19 */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_19);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_19.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_19?"ok":"error");
    
    /* set ADDRESS_1A */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1A);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1A.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1A?"ok":"error");
    
    /* set ADDRESS_1B */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1B);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1B.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1B?"ok":"error");
    
    /* set ADDRESS_1C */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1C);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1C.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1C?"ok":"error");
    
    /* set ADDRESS_1D */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1D);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1D.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1D?"ok":"error");
    
    /* set ADDRESS_1E */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1E);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1E.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1E?"ok":"error");
    
    /* set ADDRESS_1F */
    res = max30205_set_addr_pin(&gs_handle, MAX30205_ADDRESS_1F);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set addr pin ADDRESS_1F.\n");
    res = max30205_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get addr pin failed.\n");
       
        return 1;
    }
    max30205_interface_debug_print("max30205: check addr pin %s.\n", addr_pin==MAX30205_ADDRESS_1F?"ok":"error");
    res = max30205_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    
    /* set iic address */
    res = max30205_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set addr pin failed.\n");
       
        return 1;
    }
    
    /* max30205 init */
    res = max30205_init(&gs_handle);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: init failed.\n");
       
        return 1;
    }
    
    /* max30205_set_data_format/max30205_get_data_format test */
    max30205_interface_debug_print("max30205: max30205_set_data_format/max30205_get_data_format test.\n");
    
    /* set NORMAL */
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_NORMAL);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set data format normal.\n");
    res = max30205_get_data_format(&gs_handle, &format);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check data format %s.\n", format==MAX30205_DATA_FORMAT_NORMAL?"ok":"error");
    
    /* set EXTENDED */
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_EXTENDED);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set data format extended.\n");
    res = max30205_get_data_format(&gs_handle, &format);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check data format %s.\n", format==MAX30205_DATA_FORMAT_EXTENDED?"ok":"error");
    
    /* max30205_set_interrupt_mode/max30205_get_interrupt_mode */
    max30205_interface_debug_print("max30205: max30205_set_interrupt_mode/max30205_get_interrupt_mode test.\n");
    
    /* set COMPARATOR */
    res = max30205_set_interrupt_mode(&gs_handle, MAX30205_INTERRUPT_MODE_COMPARATOR);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set interrupt mode comparator.\n");
    res = max30205_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check interrupt mode %s.\n", mode==MAX30205_INTERRUPT_MODE_COMPARATOR?"ok":"error");
    
    /* set INTERRUPT */
    res = max30205_set_interrupt_mode(&gs_handle, MAX30205_INTERRUPT_MODE_INTERRUPT);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set interrupt mode interrupt.\n");
    res = max30205_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check interrupt mode %s.\n", mode==MAX30205_INTERRUPT_MODE_INTERRUPT?"ok":"error");
    
    /* max30205_set_fault_queue/max30205_get_fault_queue test */
    max30205_interface_debug_print("max30205: max30205_set_fault_queue/max30205_get_fault_queue test.\n");
    
    /* set FAULT_QUEUE_1 */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_FAULT_QUEUE_1);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set fault queue 1.\n");
    res = max30205_get_fault_queue(&gs_handle, &fault_queue);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check fault queue %s.\n", fault_queue==MAX30205_FAULT_QUEUE_1?"ok":"error");
    
    /* set FAULT_QUEUE_2 */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_FAULT_QUEUE_2);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set fault queue 2.\n");
    res = max30205_get_fault_queue(&gs_handle, &fault_queue);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check fault queue %s.\n", fault_queue==MAX30205_FAULT_QUEUE_2?"ok":"error");
    
    /* set FAULT_QUEUE_4 */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_FAULT_QUEUE_4);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set fault queue 4.\n");
    res = max30205_get_fault_queue(&gs_handle, &fault_queue);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check fault queue %s.\n", fault_queue==MAX30205_FAULT_QUEUE_4?"ok":"error");
    
    /* set FAULT_QUEUE_6 */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_FAULT_QUEUE_6);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set fault queue 6.\n");
    res = max30205_get_fault_queue(&gs_handle, &fault_queue);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check fault queue %s.\n", fault_queue==MAX30205_FAULT_QUEUE_6?"ok":"error");
    
    /* max30205_set_pin_polarity/max30205_get_pin_polarity */
    max30205_interface_debug_print("max30205: max30205_set_pin_polarity/max30205_get_pin_polarity test.\n");
    
    /* set POLARITY_LOW */
    res = max30205_set_pin_polarity(&gs_handle, MAX30205_PIN_POLARITY_LOW);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set pin polarity low.\n");
    res = max30205_get_pin_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check pin polarity %s.\n", polarity==MAX30205_PIN_POLARITY_LOW?"ok":"error");
    
    /* set POLARITY_HIGH */
    res = max30205_set_pin_polarity(&gs_handle, MAX30205_PIN_POLARITY_HIGH);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set pin polarity high.\n");
    res = max30205_get_pin_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check pin polarity %s.\n", polarity==MAX30205_PIN_POLARITY_HIGH?"ok":"error");
    max30205_interface_debug_print("max30205: max30205_set_bus_timeout/max30205_get_bus_timeout test.\n");
    
    /* set BUS_TIMEOUT_ENABLE */
    res = max30205_set_bus_timeout(&gs_handle, MAX30205_BUS_TIMEOUT_ENABLE);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set bus timeout enable.\n");
    res = max30205_get_bus_timeout(&gs_handle, &bus_timeout);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check bus timeout %s.\n", bus_timeout==MAX30205_BUS_TIMEOUT_ENABLE?"ok":"error");
    
    /* set BUS_TIMEOUT_DISABLE */
    res = max30205_set_bus_timeout(&gs_handle, MAX30205_BUS_TIMEOUT_DISABLE);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set bus timeout disable.\n");
    res = max30205_get_bus_timeout(&gs_handle, &bus_timeout);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check bus timeout %s.\n", bus_timeout==MAX30205_BUS_TIMEOUT_DISABLE?"ok":"error");
    
    /* set NORMAL CONVERT TEST */
    max30205_interface_debug_print("max30205: max30205_convert_to_register/max30205_convert_to_data test.\n");
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_NORMAL);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_convert_to_register(&gs_handle, 20.0f, (int16_t *)&reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_convert_to_data(&gs_handle, (int16_t)reg, (float *)&s);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to data failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check normal mode convert %s.\n", fabsf(s - 20.f) < 0.000001f?"ok":"error");
    
    /* set EXTENDED CONVERT TEST */
    max30205_interface_debug_print("max30205: max30205_convert_to_register/max30205_convert_to_data test.\n");
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_EXTENDED);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_convert_to_register(&gs_handle, 25.0f, (int16_t *)&reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_convert_to_data(&gs_handle, (int16_t)reg, (float *)&s);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to data failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check extended mode convert %s.\n", fabsf(s - 25.f) < 0.000001f?"ok":"error");
    max30205_interface_debug_print("max30205: max30205_set_interrupt_low_threshold/max30205_get_interrupt_low_threshold test.\n");
    
    /* set INTERRUPT_LOW_THRESHOLD */
    res = max30205_convert_to_register(&gs_handle, 35.0f, (int16_t *)&reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_set_interrupt_low_threshold(&gs_handle, (int16_t)reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt low threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set interrupt low threshold 35.0.\n");
    res = max30205_get_interrupt_low_threshold(&gs_handle, (int16_t *)&threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get interrupt low threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check low threshold %s.\n", threshold==reg?"ok":"error");
    
    /* max30205_set_interrupt_low_threshold/max30205_get_interrupt_low_threshold */
    max30205_interface_debug_print("max30205: max30205_set_interrupt_low_threshold/max30205_get_interrupt_low_threshold test.\n");
    
    /* set INTERRUPT_HIGH_THRESHOLD */
    res = max30205_convert_to_register(&gs_handle, 38.0f, (int16_t *)&reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    res = max30205_set_interrupt_high_threshold(&gs_handle, (int16_t)reg);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt high threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: set interrupt high threshold 38.0.\n");
    res = max30205_get_interrupt_high_threshold(&gs_handle, (int16_t *)&threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: get interrupt high threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_debug_print("max30205: check high threshold %s.\n", threshold==reg?"ok":"error");
    max30205_interface_debug_print("max30205: max30205_power_down test.\n");
    res = max30205_power_down(&gs_handle);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: power down failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish register test */
    max30205_interface_debug_print("max30205: finish register test.\n");
    (void)max30205_deinit(&gs_handle);
    
    return 0;
}
