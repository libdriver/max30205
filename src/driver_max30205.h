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
 * @file      driver_max30205.h
 * @brief     driver max30205 header file
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

#ifndef DRIVER_MAX30205_H
#define DRIVER_MAX30205_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup max30205_driver max30205 driver function
 * @brief    max30205 driver modules
 * @{
 */

/**
 * @addtogroup max30205_base_driver
 * @{
 */

/**
 * @brief max30205 address enumeration definition
 */
typedef enum 
{
    MAX30205_ADDRESS_0  = (uint8_t)(0x90),        /**< A2 = GND, A1 = GND, A0 = GND */
    MAX30205_ADDRESS_1  = (uint8_t)(0x92),        /**< A2 = GND, A1 = GND, A0 = VDD */
    MAX30205_ADDRESS_2  = (uint8_t)(0x82),        /**< A2 = GND, A1 = GND, A0 = SCL */
    MAX30205_ADDRESS_3  = (uint8_t)(0x80),        /**< A2 = GND, A1 = GND, A0 = SDA */
    MAX30205_ADDRESS_4  = (uint8_t)(0x94),        /**< A2 = GND, A1 = VDD, A0 = GND */
    MAX30205_ADDRESS_5  = (uint8_t)(0x96),        /**< A2 = GND, A1 = VDD, A0 = VDD */
    MAX30205_ADDRESS_6  = (uint8_t)(0x86),        /**< A2 = GND, A1 = VDD, A0 = SCL */
    MAX30205_ADDRESS_7  = (uint8_t)(0x84),        /**< A2 = GND, A1 = VDD, A0 = SDA */
    MAX30205_ADDRESS_8  = (uint8_t)(0xB4),        /**< A2 = GND, A1 = SCL, A0 = GND */
    MAX30205_ADDRESS_9  = (uint8_t)(0xB6),        /**< A2 = GND, A1 = SCL, A0 = VDD */
    MAX30205_ADDRESS_A  = (uint8_t)(0xA6),        /**< A2 = GND, A1 = SCL, A0 = SCL */
    MAX30205_ADDRESS_B  = (uint8_t)(0xA4),        /**< A2 = GND, A1 = SCL, A0 = SDA */
    MAX30205_ADDRESS_C  = (uint8_t)(0xB0),        /**< A2 = GND, A1 = SDA, A0 = GND */
    MAX30205_ADDRESS_D  = (uint8_t)(0xB2),        /**< A2 = GND, A1 = SDA, A0 = VDD */
    MAX30205_ADDRESS_E  = (uint8_t)(0xA2),        /**< A2 = GND, A1 = SDA, A0 = SCL */
    MAX30205_ADDRESS_F  = (uint8_t)(0xA0),        /**< A2 = GND, A1 = SDA, A0 = SDA */
    MAX30205_ADDRESS_10 = (uint8_t)(0x98),        /**< A2 = VDD, A1 = GND, A0 = GND */
    MAX30205_ADDRESS_11 = (uint8_t)(0x9A),        /**< A2 = VDD, A1 = GND, A0 = VDD */
    MAX30205_ADDRESS_12 = (uint8_t)(0x8A),        /**< A2 = VDD, A1 = GND, A0 = SCL */
    MAX30205_ADDRESS_13 = (uint8_t)(0x88),        /**< A2 = VDD, A1 = GND, A0 = SDA */
    MAX30205_ADDRESS_14 = (uint8_t)(0x9C),        /**< A2 = VDD, A1 = VDD, A0 = GND */
    MAX30205_ADDRESS_15 = (uint8_t)(0x9E),        /**< A2 = VDD, A1 = VDD, A0 = VDD */
    MAX30205_ADDRESS_16 = (uint8_t)(0x8E),        /**< A2 = VDD, A1 = VDD, A0 = SCL */
    MAX30205_ADDRESS_17 = (uint8_t)(0x8C),        /**< A2 = VDD, A1 = GND, A0 = SDA */
    MAX30205_ADDRESS_18 = (uint8_t)(0xBC),        /**< A2 = VDD, A1 = SCL, A0 = GND */
    MAX30205_ADDRESS_19 = (uint8_t)(0xBE),        /**< A2 = VDD, A1 = SCL, A0 = VDD */
    MAX30205_ADDRESS_1A = (uint8_t)(0xAE),        /**< A2 = VDD, A1 = SCL, A0 = SCL */
    MAX30205_ADDRESS_1B = (uint8_t)(0xAC),        /**< A2 = VDD, A1 = SCL, A0 = SDA */
    MAX30205_ADDRESS_1C = (uint8_t)(0xB8),        /**< A2 = VDD, A1 = SDA, A0 = GND */
    MAX30205_ADDRESS_1D = (uint8_t)(0xBA),        /**< A2 = VDD, A1 = SDA, A0 = VDD */
    MAX30205_ADDRESS_1E = (uint8_t)(0xAA),        /**< A2 = VDD, A1 = SDA, A0 = SCL */
    MAX30205_ADDRESS_1F = (uint8_t)(0xA8),        /**< A2 = VDD, A1 = SDA, A0 = SDA */
} max30205_address_t;

/**
 * @brief max30205 data format enumeration definition
 */
typedef enum
{
    MAX30205_DATA_FORMAT_NORMAL   = 0x00,        /**< normal format */
    MAX30205_DATA_FORMAT_EXTENDED = 0x01,        /**< extended format */
} max30205_data_format_t;

/**
 * @brief max30205 bus timeout enumeration definition
 */
typedef enum
{
    MAX30205_BUS_TIMEOUT_ENABLE  = 0x00,        /**< enable bus timeout */
    MAX30205_BUS_TIMEOUT_DISABLE = 0x01,        /**< disable bus timeout */
} max30205_bus_timeout_t;

/**
 * @}
 */

/**
 * @addtogroup max30205_interrupt_driver
 * @{
 */

/**
 * @brief max30205 interrupt mode enumeration definition
 */
typedef enum
{
    MAX30205_INTERRUPT_MODE_COMPARATOR = 0x00,        /**< comparator mode */
    MAX30205_INTERRUPT_MODE_INTERRUPT  = 0x01,        /**< interrupt mode */
} max30205_interrupt_mode_t;

/**
 * @brief max30205 fault queue enumeration definition
 */
typedef enum
{
    MAX30205_FAULT_QUEUE_1 = 0x00,        /**< fault queue 1 */
    MAX30205_FAULT_QUEUE_2 = 0x01,        /**< fault queue 2 */
    MAX30205_FAULT_QUEUE_4 = 0x02,        /**< fault queue 4 */
    MAX30205_FAULT_QUEUE_6 = 0x03,        /**< fault queue 6 */
} max30205_fault_queue_t;

/**
 * @brief max30205 pin enumeration definition
 */
typedef enum
{
    MAX30205_PIN_POLARITY_LOW  = 0x00,        /**< polarity low */
    MAX30205_PIN_POLARITY_HIGH = 0x01,        /**< polarity high */
} max30205_pin_polarity_t;

/**
 * @}
 */

/**
 * @addtogroup max30205_base_driver
 * @{
 */

/**
 * @brief max30205 handle structure definition
 */
typedef struct max30205_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t reg;                                                                        /**< register */
} max30205_handle_t;

/**
 * @brief max30205 information structure definition
 */
typedef struct max30205_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} max30205_info_t;

/**
 * @}
 */

/**
 * @defgroup max30205_link_driver max30205 link driver function
 * @brief    max30205 link driver modules
 * @ingroup  max30205_driver
 * @{
 */

/**
 * @brief     initialize max30205_handle_t structure
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] STRUCTURE is max30205_handle_t
 * @note      none
 */
#define DRIVER_MAX30205_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a max30205 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_MAX30205_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup max30205_base_driver max30205 base driver function
 * @brief    max30205 base driver modules
 * @ingroup  max30205_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a max30205 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max30205_info(max30205_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] addr_pin is the chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t max30205_set_addr_pin(max30205_handle_t *handle, max30205_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *addr_pin points to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t max30205_get_addr_pin(max30205_handle_t *handle, max30205_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a max30205 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t max30205_init(max30205_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a max30205 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_deinit(max30205_handle_t *handle);

/**
 * @brief     start reading data
 * @param[in] *handle points to a max30205 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_start_continuous_read(max30205_handle_t *handle);

/**
 * @brief     stop reading data
 * @param[in] *handle points to a max30205 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_stop_continuous_read(max30205_handle_t *handle);

/**
 * @brief      read data continuously
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       this function can be used only after run max30205_start_continuous_read
 *             and can be stopped by max30205_stop_continuous_read
 */
uint8_t max30205_continuous_read(max30205_handle_t *handle, int16_t *raw, float *s);

/**
 * @brief      read data once
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_single_read(max30205_handle_t *handle, int16_t *raw, float *s);

/**
 * @brief     set the chip data format
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] format is the data format
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_data_format(max30205_handle_t *handle, max30205_data_format_t format);

/**
 * @brief      get the chip data format
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *format points to a data format buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_data_format(max30205_handle_t *handle, max30205_data_format_t *format);

/**
 * @brief     set the iic bus timeout
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] bus_timeout is the iic bus timeout
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_bus_timeout(max30205_handle_t *handle, max30205_bus_timeout_t bus_timeout);

/**
 * @brief      get the iic bus timeout
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] bus_timeout points to an iic bus timeout buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_bus_timeout(max30205_handle_t *handle, max30205_bus_timeout_t *bus_timeout);

/**
 * @brief     chip powers down
 * @param[in] *handle points to a max30205 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_power_down(max30205_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup max30205_interrupt_driver max30205 interrupt driver function
 * @brief    max30205 interrupt driver modules
 * @ingroup  max30205_driver
 * @{
 */

/**
 * @brief     set the chip interrupt mode
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] mode is the interrupt mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_interrupt_mode(max30205_handle_t *handle, max30205_interrupt_mode_t mode);

/**
 * @brief      get the chip interrupt mode
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *mode points to an interrupt mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_interrupt_mode(max30205_handle_t *handle, max30205_interrupt_mode_t *mode);

/**
 * @brief     set the chip fault queue
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] fault_queue is the fault queue
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_fault_queue(max30205_handle_t *handle, max30205_fault_queue_t fault_queue);

/**
 * @brief      get the chip fault queue
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *fault_queue points to a fault queue buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_fault_queue(max30205_handle_t *handle, max30205_fault_queue_t *fault_queue);

/**
 * @brief     set the interrupt pin polarity
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] polarity is the interrupt pin polarity
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_pin_polarity(max30205_handle_t *handle, max30205_pin_polarity_t polarity);

/**
 * @brief      get the interrupt pin polarity
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *polarity points to an interrupt pin polarity buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_pin_polarity(max30205_handle_t *handle, max30205_pin_polarity_t *polarity);

/**
 * @brief     set the chip interrupt low threshold
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] threshold is the interrupt low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_interrupt_low_threshold(max30205_handle_t *handle, int16_t threshold);

/**
 * @brief      get the chip interrupt low threshold
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *threshold points to an interrupt low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_interrupt_low_threshold(max30205_handle_t *handle, int16_t *threshold);

/**
 * @brief     set the chip interrupt high threshold
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] threshold is the interrupt high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_interrupt_high_threshold(max30205_handle_t *handle, int16_t threshold);

/**
 * @brief      get the chip interrupt high threshold
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *threshold points to an interrupt high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_interrupt_high_threshold(max30205_handle_t *handle, int16_t *threshold);

/**
 * @brief      convert a temperature value to a register raw data
 * @param[in]  *handle points to a max30205 handle structure
 * @param[in]  s is a converted temperature value
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_convert_to_register(max30205_handle_t *handle, float s, int16_t *reg);

/**
 * @brief      convert a register raw data to a converted temperature data
 * @param[in]  *handle points to a max30205 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *s points to a converted temperature value buffer
 * @return     status code
 *             - 0 success
 *             - 1 convert to data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_convert_to_data(max30205_handle_t *handle, int16_t reg, float *s);

/**
 * @}
 */

/**
 * @defgroup max30205_extend_driver max30205 extend driver function
 * @brief    max30205 extend driver modules
 * @ingroup  max30205_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max30205_set_reg(max30205_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a max30205 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max30205_get_reg(max30205_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
