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
 * @file      driver_max30205_read_test.c
 * @brief     driver max30205 read test source file
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

#include "driver_max30205_read_test.h"

static max30205_handle_t gs_handle;        /**< max30205 handle */

/**
 * @brief     read test
 * @param[in] addr is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t max30205_read_test(max30205_address_t addr, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    int16_t low_threshold, high_threshold;
    int16_t raw;
    float s;
    max30205_info_t info;
    
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
    
    /* start read test */
    max30205_interface_debug_print("max30205: start read test.\n");
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
    
    /* set interrupt comparator mode */
    res = max30205_set_interrupt_mode(&gs_handle, MAX30205_INTERRUPT_MODE_COMPARATOR);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set set fault queue 1 */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_FAULT_QUEUE_1);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue 1 failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set pin low activity */
    res = max30205_set_pin_polarity(&gs_handle, MAX30205_PIN_POLARITY_LOW);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable bus timeout */
    res = max30205_set_bus_timeout(&gs_handle, MAX30205_BUS_TIMEOUT_DISABLE);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert low threshold 35.0 */
    res = max30205_convert_to_register(&gs_handle, 35.0f, (int16_t *)&low_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set low threshold */
    res = max30205_set_interrupt_low_threshold(&gs_handle, low_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set low threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert high threshold 39.0 */
    res = max30205_convert_to_register(&gs_handle, 39.0f, (int16_t *)&high_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set high threshold */
    res = max30205_set_interrupt_high_threshold(&gs_handle, high_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set high threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* normal read mode test */
    max30205_interface_debug_print("max30205: normal read mode test.\n");
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_NORMAL);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        /* read data */
        res = max30205_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            max30205_interface_debug_print("max30205: read failed.\n");
            (void)max30205_deinit(&gs_handle);
            
            return 1;
        }
        max30205_interface_debug_print("max30205: temperature: %.01fC.\n", s);
        max30205_interface_delay_ms(1000);
    }
    
    /* set extended format */
    max30205_interface_debug_print("max30205: extended read mode test.\n");
    res = max30205_set_data_format(&gs_handle, MAX30205_DATA_FORMAT_EXTENDED);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        /* read data */
        res = max30205_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            max30205_interface_debug_print("max30205: read failed.\n");
            (void)max30205_deinit(&gs_handle);
            
            return 1;
        }
        max30205_interface_debug_print("max30205: temperature: %.01fC.\n", s);
        max30205_interface_delay_ms(1000);
    }
    
    /* single read test */
    max30205_interface_debug_print("max30205: single read test.\n");
    for (i = 0; i < times; i++)
    {
        /* read data */
        res = max30205_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            max30205_interface_debug_print("max30205: read failed.\n");
            (void)max30205_deinit(&gs_handle);
            
            return 1;
        }
        max30205_interface_debug_print("max30205: temperature: %.01fC.\n", s);
        max30205_interface_delay_ms(1000);
    }
    
    /* continuous read test */
    max30205_interface_debug_print("max30205: continuous read test.\n");
    res = max30205_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: start continuous read failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    max30205_interface_delay_ms(1000);
    for (i = 0; i < times; i++)
    {
        /* read data */
        res = max30205_continuous_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            max30205_interface_debug_print("max30205: read failed.\n");
            (void)max30205_deinit(&gs_handle);
            
            return 1;
        }
        max30205_interface_debug_print("max30205: temperature: %.01fC.\n", s);
        max30205_interface_delay_ms(1000);
    }
    res = max30205_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: stop continuous read failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finished read test */
    max30205_interface_debug_print("max30205: finished read test.\n");
    (void)max30205_deinit(&gs_handle);
    
    return 0;
}
