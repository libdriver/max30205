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
 * @file      driver_max30205.c
 * @brief     driver max30205 source file
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

#include "driver_max30205.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Maxim Integrated MAX30205"        /**< chip name */
#define MANUFACTURER_NAME         "Maxim Integrated"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.3f                               /**< chip max supply voltage */
#define MAX_CURRENT               20.0f                              /**< chip max current */
#define TEMPERATURE_MIN           0.0f                               /**< chip min operating temperature */
#define TEMPERATURE_MAX           50.0f                              /**< chip max operating temperature */
#define DRIVER_VERSION            2000                               /**< driver version */

/**
 * @brief chip register definition
 */
#define MAX30205_REG_TEMP         0x00        /**< temperature register */
#define MAX30205_REG_CONF         0x01        /**< configure register */
#define MAX30205_REG_THYST        0x02        /**< thyst register */
#define MAX30205_REG_TOS          0x03        /**< tos register */

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
uint8_t max30205_init(max30205_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->iic_init == NULL)                                      /* check iic_init */
    {
        handle->debug_print("max30205: iic_init is null.\n");          /* iic_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_deinit == NULL)                                    /* check iic_deinit */
    {
        handle->debug_print("max30205: iic_deinit is null.\n");        /* iic_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_read == NULL)                                      /* check iic_read */
    {
        handle->debug_print("max30205: iic_read is null.\n");          /* iic_read is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_write == NULL)                                     /* check iic_write */
    {
        handle->debug_print("max30205: iic_write is null.\n");         /* iic_write is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("max30205: delay_ms is null.\n");          /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }

    if (handle->iic_init() != 0)                                       /* init iic */
    {
        handle->debug_print("max30205: iic init failed.\n");           /* iic init failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 1;                                                /* flag finish initialization */
    handle->reg = 0;                                                   /* initialize register */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t max30205_deinit(max30205_handle_t *handle)
{
    uint8_t reg;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    reg = handle->reg | 0x01;                                                              /* power down */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_CONF, (uint8_t *)&reg, 1) != 0)   /* write to conf register */
    {
        handle->debug_print("max30205: power down failed.\n");                             /* power down failed */
        
        return 1;                                                                          /* return error */
    }
    if (handle->iic_deinit() != 0)                                                         /* iic deinit */
    {
        handle->debug_print("max30205: iic deinit failed.\n");                             /* iic deinit failed */
        
        return 1;                                                                          /* return error */
    }   
    handle->inited = 0;                                                                    /* flag close */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to a max30205 handle structure
 * @param[in] addr_pin is the chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t max30205_set_addr_pin(max30205_handle_t *handle, max30205_address_t addr_pin)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }

    handle->iic_addr = (uint8_t)addr_pin;        /* set iic address */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to a max30205 handle structure
 * @param[out] *addr_pin points to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t max30205_get_addr_pin(max30205_handle_t *handle, max30205_address_t *addr_pin)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }

    *addr_pin = (max30205_address_t)handle->iic_addr;        /* get iic address */
    
    return 0;                                                /* success return 0 */
}

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
uint8_t max30205_set_data_format(max30205_handle_t *handle, max30205_data_format_t format)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    if (handle->inited != 1)                          /* check handle initialization */
    {
        return 3;                                     /* return error */
    }

    if (format != 0)                                  /* if extended format */
    {
        handle->reg = handle->reg | (1 << 5);         /* set extended format */
    }
    else
    {
        handle->reg = handle->reg & (~(1 << 5));      /* set normal format */
    }
    
    return 0;                                         /* success return 0 */
}

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
uint8_t max30205_get_data_format(max30205_handle_t *handle, max30205_data_format_t *format)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }

    if ((handle->reg & (1 << 5)) != 0)                  /* get format */
    {
        *format = MAX30205_DATA_FORMAT_EXTENDED;        /* get format extended */
    }
    else
    {
        *format = MAX30205_DATA_FORMAT_NORMAL;          /* get format normal */
    }
 
    return 0;                                           /* success return 0 */
}

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
uint8_t max30205_set_interrupt_mode(max30205_handle_t *handle, max30205_interrupt_mode_t mode)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    if (handle->inited != 1)                          /* check handle initialization */
    {
        return 3;                                     /* return error */
    }

    if (mode != 0)                                    /* check the mode */
    {
        handle->reg = handle->reg | (1 << 1);         /* set interrupt mode */
    }
    else
    {
        handle->reg = handle->reg & (~(1 << 1));      /* set comparator mode */
    }
    
    return 0;                                         /* success return 0 */
}

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
uint8_t max30205_get_interrupt_mode(max30205_handle_t *handle, max30205_interrupt_mode_t *mode)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }
    
    if ((handle->reg & (1 << 1)) != 0)                     /* get interrupt mode */
    {
        *mode = MAX30205_INTERRUPT_MODE_INTERRUPT;         /* interrupt mode */
    }
    else
    {
        *mode = MAX30205_INTERRUPT_MODE_COMPARATOR;        /* comparator mode */
    }
    
    return 0;                                              /* success return 0 */
}

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
uint8_t max30205_set_fault_queue(max30205_handle_t *handle, max30205_fault_queue_t fault_queue)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }
    
    handle->reg = handle->reg & (~(3 << 3));               /* clear fault queue */
    handle->reg = (uint8_t)(handle->reg | 
                  (fault_queue << 3));                     /* set fault queue */
    
    return 0;                                              /* success return 0 */
}

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
uint8_t max30205_get_fault_queue(max30205_handle_t *handle, max30205_fault_queue_t *fault_queue)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    *fault_queue = (max30205_fault_queue_t)((handle->reg >> 3) & 0x03);        /* get fault queue */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t max30205_set_pin_polarity(max30205_handle_t *handle, max30205_pin_polarity_t polarity)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    if (handle->inited != 1)                          /* check handle initialization */
    {
        return 3;                                     /* return error */
    }
    
    if (polarity != 0)                                /* check the polarity */
    {
        handle->reg = handle->reg | (1 << 2);         /* set active high */
    }
    else
    {
        handle->reg = handle->reg & (~(1 << 2));      /* set active low */
    }
    
    return 0;                                         /* success return 0 */
}

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
uint8_t max30205_get_pin_polarity(max30205_handle_t *handle, max30205_pin_polarity_t *polarity)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    if ((handle->reg & (1 << 2)) != 0)                 /* active high */
    {
        *polarity = MAX30205_PIN_POLARITY_HIGH;        /* high polarity */
    }
    else                                               /* active low */
    {
        *polarity = MAX30205_PIN_POLARITY_LOW;         /* low polarity */
    }
    
    return 0;                                          /* success return 0 */
}

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
uint8_t max30205_set_bus_timeout(max30205_handle_t *handle, max30205_bus_timeout_t bus_timeout)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    if (handle->inited != 1)                          /* check handle initialization */
    {
        return 3;                                     /* return error */
    }
    
    if (bus_timeout != 0)                             /* check the bus timeout */
    {
        handle->reg = handle->reg | (1 << 6);         /* disable bus timeout */
    }
    else
    {
        handle->reg = handle->reg & (~(1 << 6));      /* enable bus timeout */
    }
    
    return 0;                                         /* success return 0 */
}

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
uint8_t max30205_get_bus_timeout(max30205_handle_t *handle, max30205_bus_timeout_t *bus_timeout)
{
    if (handle == NULL)                                     /* check handle */
    {
        return 2;                                           /* return error */
    }
    if (handle->inited != 1)                                /* check handle initialization */
    {
        return 3;                                           /* return error */
    }
    
    if ((handle->reg & (1 << 6)) != 0)                      /* disable bus timeout */
    {
        *bus_timeout = MAX30205_BUS_TIMEOUT_DISABLE;        /* bus timeout disable */
    }
    else                                                    /* enable bus timeout */
    {
        *bus_timeout = MAX30205_BUS_TIMEOUT_ENABLE;         /* bus timeout enable */
    }
    
    return 0;                                               /* success return 0 */
}

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
uint8_t max30205_start_continuous_read(max30205_handle_t *handle)
{
    uint8_t reg;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    reg = handle->reg & (~(1 << 0));                                                          /* exit shutdown mode */
    reg = reg & (~(1 << 7));                                                                  /* set continuous read bit */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_CONF, (uint8_t *)&reg, 1) != 0)      /* write conf register */
    {
        handle->debug_print("max30205: start continuous read failed.\n");                     /* start continuous read failed */
        
        return 1;                                                                             /* return error */
    }
    else
    {
        return 0;                                                                             /* success return 0 */
    }
}

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
uint8_t max30205_stop_continuous_read(max30205_handle_t *handle)
{
    uint8_t reg;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    reg = handle->reg | (1 << 0);                                                             /* enter shutdown mode */
    reg = reg | (1 << 7);                                                                     /* set continuous read bit */
    
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_CONF, (uint8_t *)&reg, 1) != 0)      /* write conf register */
    {
        handle->debug_print("max30205: stop continuous read failed.\n");                      /* stop continuous read failed */
        
        return 1;                                                                             /* return error */
    }
    else
    {
        return 0;                                                                             /* success return 0 */
    }
}

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
uint8_t max30205_continuous_read(max30205_handle_t *handle, int16_t *raw, float *s)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                 /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, MAX30205_REG_TEMP, (uint8_t *)buf, 2) != 0)   /* read two bytes */
    {
        handle->debug_print("max30205: read failed.\n");                                 /* read temp failed */
        
        return 1;                                                                        /* return error */
    }
    if ((handle->reg & (1 << 5)) != 0)                                                   /* extended format */
    {
        *raw = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                              /* get raw data */
        *s = (float)(*raw) * 0.00390625f + 64.0f;                                        /* convert raw data to real data */
    }
    else                                                                                 /* normal format */
    {
        *raw = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                              /* get raw data */
        *s = (float)(*raw) * 0.00390625f;                                                /* convert raw data to real data */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t max30205_single_read(max30205_handle_t *handle, int16_t *raw, float *s)
{
    uint8_t buf[2];
    uint8_t reg;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    reg = handle->reg | (1 << 0);                                                          /* enter shutdown mode */
    reg = reg | (1 << 7);                                                                  /* set single read bit */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_CONF, (uint8_t *)&reg, 1) != 0)   /* write conf */
    {
        handle->debug_print("max30205: write failed.\n");                                  /* write failed */
       
        return 1;                                                                          /* return error */
    }
    handle->delay_ms(50);                                                                  /* delay 50 ms */
    memset(buf, 0, sizeof(uint8_t) * 2);                                                   /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, MAX30205_REG_TEMP, (uint8_t *)buf, 2) != 0)     /* read two bytes */
    {
        handle->debug_print("max30205: read failed.\n");                                   /* read failed */
       
        return 1;                                                                          /* return error */
    }
    if ((handle->reg & (1 << 5)) != 0)                                                     /* extended format */
    {
        *raw = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                                /* get raw data */
        *s = (float)(*raw) * 0.00390625f + 64.0f;                                          /* convert raw data to real data */
    }
    else                                                                                   /* normal format */
    {
        *raw = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                                /* get raw data */
        *s = (float)(*raw) * 0.00390625f;                                                  /* convert raw data to real data */
    }
    
    return 0;                                                                              /* success return 0 */
}

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
uint8_t max30205_set_interrupt_low_threshold(max30205_handle_t *handle, int16_t threshold)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    buf[0] = (threshold >> 8) & 0xFF;                                                         /* MSB */
    buf[1] = threshold & 0xFF;                                                                /* LSB */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_THYST, (uint8_t *)buf, 2) != 0)      /* write to register */
    {
        handle->debug_print("max30205: set interrupt low threshold failed.\n");               /* set interrupt low threshold failed */
        
        return 1;                                                                             /* return error */
    }
    else
    {
        return 0;                                                                             /* success return 0 */
    }
}

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
uint8_t max30205_get_interrupt_low_threshold(max30205_handle_t *handle, int16_t *threshold)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                  /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, MAX30205_REG_THYST, (uint8_t *)buf, 2) != 0)   /* read 2 bytes */
    {
        handle->debug_print("max30205: read failed.\n");                                  /* read thyst failed */
        
        return 1;                                                                         /* return error */
    }
    *threshold = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                             /* get raw data */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t max30205_set_interrupt_high_threshold(max30205_handle_t *handle, int16_t threshold)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    buf[0] = (threshold >> 8) & 0xFF;                                                       /* MSB */
    buf[1] = threshold & 0xFF;                                                              /* LSB */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_TOS, (uint8_t *)buf, 2) != 0)      /* write to register */
    {
        handle->debug_print("max30205: set interrupt high threshold failed.\n");            /* set interrupt high threshold failed */
        
        return 1;                                                                           /* return error */
    }
    else
    {
        return 0;                                                                           /* success return 0 */
    }
}

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
uint8_t max30205_get_interrupt_high_threshold(max30205_handle_t *handle, int16_t *threshold)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, MAX30205_REG_TOS, (uint8_t *)buf, 2) != 0)   /* read 2 bytes */
    {
        handle->debug_print("max30205: read failed.\n");                                /* read tos failed */
        
        return 1;                                                                       /* return error */
    }
    *threshold = (int16_t)(((uint16_t)buf[0]) << 8 | buf[1]);                           /* get raw data */
    
    return 0;                                                                           /* success return 0 */
}

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
uint8_t max30205_convert_to_register(max30205_handle_t *handle, float s, int16_t *reg)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    if ((handle->reg & (1 << 5)) != 0)                    /* extended format */
    {
        *reg = (int16_t)((s - 64.0f) / 0.00390625f);      /* convert real data to register data */
    }
    else                                                  /* normal format */
    {
        *reg = (int16_t)(s / 0.00390625f);                /* convert real data to register data */
    }
    
    return 0;                                             /* success return 0 */
}

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
uint8_t max30205_convert_to_data(max30205_handle_t *handle, int16_t reg, float *s)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    if ((handle->reg & (1 << 5)) != 0)                  /* extended format */
    {
        *s = (float)(reg) * 0.00390625f + 64.0f;        /* convert raw data to real data */
    }
    else                                                /* normal format */
    {
        *s = (float)(reg) * 0.00390625f;                /* convert raw data to real data */
    }
    
    return 0;                                           /* success return 0 */
}

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
uint8_t max30205_power_down(max30205_handle_t *handle)
{
    uint8_t reg;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    reg = handle->reg | 0x01;                                                                 /* set shutdown bit */
    if (handle->iic_write(handle->iic_addr, MAX30205_REG_CONF, (uint8_t *)&reg, 1) != 0)      /* write to conf register */
    {
        handle->debug_print("max30205: power down failed.\n");                                /* power down failed */
        
        return 1;                                                                             /* return error */
    }
    else
    {
        return 0;                                                                             /* success return 0 */
    }
}

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
uint8_t max30205_set_reg(max30205_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (handle->iic_write(handle->iic_addr, reg, buf, len) != 0)      /* write data */
    {
        handle->debug_print("max30205: write failed.\n");             /* write failed */
        
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

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
uint8_t max30205_get_reg(max30205_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
   if (handle->iic_read(handle->iic_addr, reg, buf, len) != 0)       /* read data */
    {
        handle->debug_print("max30205: read failed.\n");             /* read failed */
        
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a max30205 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max30205_info(max30205_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(max30205_info_t));                       /* initialize max30205 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
