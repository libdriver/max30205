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
 * @file      driver_max30205_shot.c
 * @brief     driver max30205 shot source file
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

#include "driver_max30205_shot.h"

static max30205_handle_t gs_handle;        /**< max30205 handle */

/**
 * @brief     shot example init
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t max30205_shot_init(max30205_address_t addr_pin)
{
    uint8_t res;
    int16_t low_threshold;
    int16_t high_threshold;
    
    /* link interface function */
    DRIVER_MAX30205_LINK_INIT(&gs_handle, max30205_handle_t);
    DRIVER_MAX30205_LINK_IIC_INIT(&gs_handle, max30205_interface_iic_init);
    DRIVER_MAX30205_LINK_IIC_DEINIT(&gs_handle, max30205_interface_iic_deinit);
    DRIVER_MAX30205_LINK_IIC_READ(&gs_handle, max30205_interface_iic_read);
    DRIVER_MAX30205_LINK_IIC_WRITE(&gs_handle, max30205_interface_iic_write);
    DRIVER_MAX30205_LINK_DELAY_MS(&gs_handle, max30205_interface_delay_ms);
    DRIVER_MAX30205_LINK_DEBUG_PRINT(&gs_handle, max30205_interface_debug_print);
    
    /* set max30205 iic address */
    res = max30205_set_addr_pin(&gs_handle, addr_pin);
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
    
    /* set data format */
    res = max30205_set_data_format(&gs_handle, MAX30205_SHOT_DEFAULT_DATA_FORMAT);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set data format failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt mode */
    res = max30205_set_interrupt_mode(&gs_handle, MAX30205_SHOT_DEFAULT_INTERRUPT_MODE);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set interrupt mode failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set fault queue */
    res = max30205_set_fault_queue(&gs_handle, MAX30205_SHOT_DEFAULT_FAULT_QUEUE);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set fault queue failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set pin polarity */
    res = max30205_set_pin_polarity(&gs_handle, MAX30205_SHOT_DEFAULT_PIN_POLARITY);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set pin polarity failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set bus timeout */
    res = max30205_set_bus_timeout(&gs_handle, MAX30205_SHOT_DEFAULT_BUS_TIMEOUT);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set bus timeout failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res= max30205_convert_to_register(&gs_handle, MAX30205_SHOT_DEFAULT_INTERRUPT_LOW_THRESHOLD, (int16_t *)&low_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1; 
    }
    
    /* set interrupt low threshold */
    res = max30205_set_interrupt_low_threshold(&gs_handle, low_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set low threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = max30205_convert_to_register(&gs_handle, MAX30205_SHOT_DEFAULT_INTERRUPT_HIGH_THRESHOLD, (int16_t *)&high_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: convert to register failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt high threshold */
    res = max30205_set_interrupt_high_threshold(&gs_handle, high_threshold);
    if (res != 0)
    {
        max30205_interface_debug_print("max30205: set high threshold failed.\n");
        (void)max30205_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t max30205_shot_read(float *s)
{
    int16_t raw;
    
    /* single read */
    if (max30205_single_read(&gs_handle, (int16_t *)&raw, s) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max30205_shot_deinit(void)
{
    /* close max30205 */
    if (max30205_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
