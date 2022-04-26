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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_max30205_basic.h"
#include "driver_max30205_shot.h"
#include "driver_max30205_interrupt.h"
#include "driver_max30205_register_test.h"
#include "driver_max30205_read_test.h"
#include "driver_max30205_interrupt_test.h"
#include "gpio.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     max30205 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t max30205(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            max30205_info_t info;
            
            /* print max30205 info */
            max30205_info(&info);
            max30205_interface_debug_print("max30205: chip is %s.\n", info.chip_name);
            max30205_interface_debug_print("max30205: manufacturer is %s.\n", info.manufacturer_name);
            max30205_interface_debug_print("max30205: interface is %s.\n", info.interface);
            max30205_interface_debug_print("max30205: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            max30205_interface_debug_print("max30205: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            max30205_interface_debug_print("max30205: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            max30205_interface_debug_print("max30205: max current is %0.2fmA.\n", info.max_current_ma);
            max30205_interface_debug_print("max30205: max temperature is %0.1fC.\n", info.temperature_max);
            max30205_interface_debug_print("max30205: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            max30205_interface_debug_print("max30205: SCL connected to GPIO3(BCM).\n");
            max30205_interface_debug_print("max30205: SDA connected to GPIO2(BCM).\n");
            max30205_interface_debug_print("max30205: OS connected to GPIO17(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show max30205 help */
            
            help:
            
            max30205_interface_debug_print("max30205 -i\n\tshow max30205 chip and driver information.\n");
            max30205_interface_debug_print("max30205 -h\n\tshow max30205 help.\n");
            max30205_interface_debug_print("max30205 -p\n\tshow max30205 pin connections of the current board.\n");
            max30205_interface_debug_print("max30205 -t reg -a <address>\n\trun max30205 register test.address means iic address and it can be \"00\"-\"1F\".\n");
            max30205_interface_debug_print("max30205 -t read <times> -a <address>\n\trun max30205 read test.times means test times."
                                           "address means iic address and it can be \"00\"-\"1F\".\n");
            max30205_interface_debug_print("max30205 -t int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>\n\t"
                                           "run max30205 interrupt test.times means test times.address means iic address and it can be \"00\"-\"1F\".");
            max30205_interface_debug_print("lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.\n");
            max30205_interface_debug_print("max30205 -c read <times> -a <address>\n\trun max30205 read function.times means read times."
                                           "address means iic address and it can be \"00\"-\"1F\".\n");
            max30205_interface_debug_print("max30205 -c shot <times> -a <address>\n\trun max30205 shot function.times means read times."
                                           "address means iic address and it can be \"00\"-\"1F\".\n");
            max30205_interface_debug_print("max30205 -c int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>\n\t"
                                           "run max30205 interrupt function.times means read times.address means iic address and it can be \"00\"-\"1F\".");
            max30205_interface_debug_print("lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                uint8_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[4]) < 2)
                {
                    return 5;
                }
                if ((argv[4][0] <= '9') && (argv[4][0] >= '0'))
                {
                    addr = (argv[4][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[4][0] - 'A' + 10) * 16;
                }
                if ((argv[4][1] <= '9') && (argv[4][1] >= '0'))
                {
                    addr += argv[4][1] - '0';
                }
                else
                {
                    addr += argv[4][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                /* run reg test */
                if (max30205_register_test((max30205_address_t)(addr)) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[5]) < 2)
                {
                    return 5;
                }
                if ((argv[5][0] <= '9') && (argv[5][0] >= '0'))
                {
                    addr = (argv[5][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[5][0] - 'A' + 10) * 16;
                }
                if ((argv[5][1] <= '9') && (argv[5][1] >= '0'))
                {
                    addr += argv[5][1] - '0';
                }
                else
                {
                    addr += argv[5][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                /* run read test */
                if (max30205_read_test((max30205_address_t)(addr), atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint32_t i;
                uint8_t addr;
                float s;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[5]) < 2)
                {
                    return 5;
                }
                if ((argv[5][0] <= '9') && (argv[5][0] >= '0'))
                {
                    addr = (argv[5][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[5][0] - 'A' + 10) * 16;
                }
                if ((argv[5][1] <= '9') && (argv[5][1] >= '0'))
                {
                    addr += argv[5][1] - '0';
                }
                else
                {
                    addr += argv[5][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                
                res = max30205_basic_init((max30205_address_t)(addr));
                if (res != 0)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i = 0; i < times; i++)
                {
                    max30205_interface_delay_ms(1000);
                    res = max30205_basic_read((float *)&s);
                    if (res != 0)
                    {
                        (void)max30205_basic_deinit();
                        
                        return 1;
                    }
                    max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
                }
                (void)max30205_basic_deinit();
                
                return 0;
            }
            /* shot function */
            else if (strcmp("shot", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint32_t i;
                uint8_t addr;
                float s;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[5]) < 2)
                {
                    return 5;
                }
                if ((argv[5][0] <= '9') && (argv[5][0] >= '0'))
                {
                    addr = (argv[5][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[5][0] - 'A' + 10) * 16;
                }
                if ((argv[5][1] <= '9') && (argv[5][1] >= '0'))
                {
                    addr += argv[5][1] - '0';
                }
                else
                {
                    addr += argv[5][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                
                res = max30205_shot_init((max30205_address_t)(addr));
                if (res != 0)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i = 0; i < times; i++)
                {
                    max30205_interface_delay_ms(1000);
                    res = max30205_shot_read((float *)&s);
                    if (res != 0)
                    {
                        (void)max30205_shot_deinit();
                        
                        return 1;
                    }
                    max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
                }
                (void)max30205_shot_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 11)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* int test */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint8_t addr;
                max30205_interrupt_mode_t mode;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[5]) < 2)
                {
                    return 5;
                }
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("CMP", argv[7]) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_COMPARATOR;
                }
                else if (strcmp("INT", argv[7]) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_INTERRUPT;
                }
                else
                {
                    max30205_interface_debug_print("max30205: mode is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-th", argv[8]) != 0)
                {
                    return 5;
                }
                if ((argv[5][0] <= '9') && (argv[5][0] >= '0'))
                {
                    addr = (argv[5][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[5][0] - 'A' + 10) * 16;
                }
                if ((argv[5][1] <= '9') && (argv[5][1] >= '0'))
                {
                    addr += argv[5][1] - '0';
                }
                else
                {
                    addr += argv[5][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = gpio_interrupt_init();
                if (res != 0)
                {
                    return 1;
                }
                res = max30205_interrupt_test((max30205_address_t)(addr), mode, (float)atof(argv[9]),(float)atof(argv[10]), times);
                if (res != 0)
                {
                    (void)gpio_interrupt_deinit();
                    
                    return 1;
                }
                (void)gpio_interrupt_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* int function */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                uint32_t i;
                uint8_t addr;
                float s;
                max30205_interrupt_mode_t mode;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strlen(argv[5]) < 2)
                {
                    return 5;
                }
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("CMP", argv[7]) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_COMPARATOR;
                }
                else if (strcmp("INT", argv[7]) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_INTERRUPT;
                }
                else
                {
                    max30205_interface_debug_print("max30205: mode is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-th", argv[8]) != 0)
                {
                    return 5;
                }
                if ((argv[5][0] <= '9') && (argv[5][0] >= '0'))
                {
                    addr = (argv[5][0] - '0') * 16;
                }
                else
                {
                    addr = (argv[5][0] - 'A' + 10) * 16;
                }
                if ((argv[5][1] <= '9') && (argv[5][1] >= '0'))
                {
                    addr += argv[5][1] - '0';
                }
                else
                {
                    addr += argv[5][1] - 'A' + 10;
                }
                if (addr == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = gpio_interrupt_init();
                if (res != 0)
                {
                    return 1;
                }
                res = max30205_interrupt_init((max30205_address_t)(addr), mode, (float)atof(argv[9]),(float)atof(argv[10]));
                if (res != 0)
                {
                    (void)gpio_interrupt_deinit();
                    
                    return 1;
                }
                g_flag = 0;
                for (i = 0; i < times; i++)
                {
                    max30205_interface_delay_ms(1000);
                    res = max30205_interrupt_read((float *)&s); 
                    if (res != 0)
                    {
                        (void)gpio_interrupt_deinit();
                        (void)max30205_interrupt_deinit();
                        
                        return 1;
                    }
                    if (g_flag != 0)
                    {
                        max30205_interface_debug_print("max30205: find interrupt.\n");
                        
                        break;
                    }
                    max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
                }
                (void)gpio_interrupt_deinit();
                (void)max30205_interrupt_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = max30205(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        max30205_interface_debug_print("max30205: run failed.\n");
    }
    else if (res == 5)
    {
        max30205_interface_debug_print("max30205: param is invalid.\n");
    }
    else
    {
        max30205_interface_debug_print("max30205: unknow status code.\n");
    }

    return 0;
}