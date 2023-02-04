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
#include <getopt.h>
#include <stdlib.h>

volatile uint8_t g_flag;           /**< interrupt flag */

/**
 * @brief     max30205 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t max30205(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"high-threshold", required_argument, NULL, 2},
        {"low-threshold", required_argument, NULL, 3},
        {"mode", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    max30205_address_t addr = MAX30205_ADDRESS_0;
    max30205_interrupt_mode_t mode = MAX30205_INTERRUPT_MODE_COMPARATOR;
    float high_threshold = 39.0f;
    float low_threshold = 35.0f;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                uint8_t addr_pin;
                
                /* set the addr pin */
                if (strlen(optarg) < 2)
                {
                    return 5;
                }
                if ((optarg[0] <= '9') && (optarg[0] >= '0'))
                {
                    addr_pin = (optarg[0] - '0') * 16;
                }
                else
                {
                    addr_pin = (optarg[0] - 'A' + 10) * 16;
                }
                if ((optarg[1] <= '9') && (optarg[1] >= '0'))
                {
                    addr_pin += optarg[1] - '0';
                }
                else
                {
                    addr_pin += optarg[1] - 'A' + 10;
                }
                if (addr_pin == 0)
                {
                    addr = MAX30205_ADDRESS_0;
                }
                else if (addr_pin == 1)
                {
                    addr = MAX30205_ADDRESS_1;
                }
                else if (addr_pin == 2)
                {
                    addr = MAX30205_ADDRESS_2;
                }
                else if (addr_pin == 3)
                {
                    addr = MAX30205_ADDRESS_3;
                }
                else if (addr_pin == 4)
                {
                    addr = MAX30205_ADDRESS_4;
                }
                else if (addr_pin == 5)
                {
                    addr = MAX30205_ADDRESS_5;
                }
                else if (addr_pin == 6)
                {
                    addr = MAX30205_ADDRESS_6;
                }
                else if (addr_pin == 7)
                {
                    addr = MAX30205_ADDRESS_7;
                }
                else if (addr_pin == 8)
                {
                    addr = MAX30205_ADDRESS_8;
                }
                else if (addr_pin == 9)
                {
                    addr = MAX30205_ADDRESS_9;
                }
                else if (addr_pin == 10)
                {
                    addr = MAX30205_ADDRESS_A;
                }
                else if (addr_pin == 11)
                {
                    addr = MAX30205_ADDRESS_B;
                }
                else if (addr_pin == 12)
                {
                    addr = MAX30205_ADDRESS_C;
                }
                else if (addr_pin == 13)
                {
                    addr = MAX30205_ADDRESS_D;
                }
                else if (addr_pin == 14)
                {
                    addr = MAX30205_ADDRESS_E;
                }
                else if (addr_pin == 15)
                {
                    addr = MAX30205_ADDRESS_F;
                }
                else if (addr_pin == 16)
                {
                    addr = MAX30205_ADDRESS_10;
                }
                else if (addr_pin == 17)
                {
                    addr = MAX30205_ADDRESS_11;
                }
                else if (addr_pin == 18)
                {
                    addr = MAX30205_ADDRESS_12;
                }
                else if (addr_pin == 19)
                {
                    addr = MAX30205_ADDRESS_13;
                }
                else if (addr_pin == 20)
                {
                    addr = MAX30205_ADDRESS_14;
                }
                else if (addr_pin == 21)
                {
                    addr = MAX30205_ADDRESS_15;
                }
                else if (addr_pin == 22)
                {
                    addr = MAX30205_ADDRESS_16;
                }
                else if (addr_pin == 23)
                {
                    addr = MAX30205_ADDRESS_17;
                }
                else if (addr_pin == 24)
                {
                    addr = MAX30205_ADDRESS_18;
                }
                else if (addr_pin == 25)
                {
                    addr = MAX30205_ADDRESS_19;
                }
                else if (addr_pin == 26)
                {
                    addr = MAX30205_ADDRESS_1A;
                }
                else if (addr_pin == 27)
                {
                    addr = MAX30205_ADDRESS_1B;
                }
                else if (addr_pin == 28)
                {
                    addr = MAX30205_ADDRESS_1C;
                }
                else if (addr_pin == 29)
                {
                    addr = MAX30205_ADDRESS_1D;
                }
                else if (addr_pin == 30)
                {
                    addr = MAX30205_ADDRESS_1E;
                }
                else if (addr_pin == 31)
                {
                    addr = MAX30205_ADDRESS_1F;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threshold */
            case 2 :
            {
                high_threshold = atof(optarg);
                
                break;
            }
             
            /* low threshold */
            case 3 :
            {
                low_threshold = atof(optarg);
                
                break;
            }
            
            /* mode */
            case 4 :
            {
                /* set the mode */
                if (strcmp("CMP", optarg) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_COMPARATOR;
                }
                else if (strcmp("INT", optarg) == 0)
                {
                    mode = MAX30205_INTERRUPT_MODE_INTERRUPT;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (max30205_register_test(addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (max30205_read_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* run interrupt test */
        res = max30205_interrupt_test(addr, mode, low_threshold, high_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;

        /* basic init */
        res = max30205_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            max30205_interface_delay_ms(1000);
            
            /* read data */
            res = max30205_basic_read((float *)&s);
            if (res != 0)
            {
                (void)max30205_basic_deinit();
                
                return 1;
            }
            
            /* output */
            max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
        }
        
        /* basic deinit */
        (void)max30205_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;
        
        /* shot init */
        res = max30205_shot_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            max30205_interface_delay_ms(1000);
            
            /* read data */
            res = max30205_shot_read((float *)&s);
            if (res != 0)
            {
                (void)max30205_shot_deinit();
                
                return 1;
            }
            
            /* output */
            max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
        }
        
        /* shot deinit */
        (void)max30205_shot_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* interrupt init */
        res = max30205_interrupt_init(addr, mode, low_threshold, high_threshold);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* loop */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            max30205_interface_delay_ms(1000);
            
            /* read data */
            res = max30205_interrupt_read((float *)&s); 
            if (res != 0)
            {
                (void)gpio_interrupt_deinit();
                (void)max30205_interrupt_deinit();
                
                return 1;
            }
            
            /* check the flag */
            if (g_flag != 0)
            {
                max30205_interface_debug_print("max30205: find interrupt.\n");
                
                break;
            }
            
            /* output */
            max30205_interface_debug_print("max30205: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
        }
        
        /* deinit */
        (void)gpio_interrupt_deinit();
        (void)max30205_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        max30205_interface_debug_print("Usage:\n");
        max30205_interface_debug_print("  max30205 (-i | --information)\n");
        max30205_interface_debug_print("  max30205 (-h | --help)\n");
        max30205_interface_debug_print("  max30205 (-p | --port)\n");
        max30205_interface_debug_print("  max30205 (-t reg | --test=reg) [--addr=<address>]\n");
        max30205_interface_debug_print("  max30205 (-t read | --test=read) [--addr=<address>] [--times=<num>]\n");
        max30205_interface_debug_print("  max30205 (-t int | --test=int) [--addr=<address>] [--times=<num>]\n");
        max30205_interface_debug_print("           [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        max30205_interface_debug_print("  max30205 (-e read | --example=read) [--addr=<address>] [--times=<num>]\n");
        max30205_interface_debug_print("  max30205 (-e shot | --example=shot) [--addr=<address>] [--times=<num>]\n");
        max30205_interface_debug_print("  max30205 (-e int | --example=int) [--addr=<address>] [--times=<num>]\n");
        max30205_interface_debug_print("           [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        max30205_interface_debug_print("\n");
        max30205_interface_debug_print("Options:\n");
        max30205_interface_debug_print("      --addr=<address>           Set the addr pin and it can be \"00\" - \"1F\".([default: 00])\n");
        max30205_interface_debug_print("  -e <read | shot | int>, --example=<read | shot | int>\n");
        max30205_interface_debug_print("                                 Run the driver example.\n");
        max30205_interface_debug_print("  -h, --help                     Show the help.\n");
        max30205_interface_debug_print("      --high-threshold=<high>    Set the interrupt high threshold.([default: 39.0f])\n");
        max30205_interface_debug_print("  -i, --information              Show the chip information.\n");
        max30205_interface_debug_print("      --low-threshold=<low>      Set the interrupt low threshold.([default: 35.0f])\n");
        max30205_interface_debug_print("      --mode=<INT | CMP>         Set the interrupt mode.([default: CMP])\n");
        max30205_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        max30205_interface_debug_print("  -t <reg | read | int>, --test=<reg | read | int>\n");
        max30205_interface_debug_print("                                 Run the driver test.\n");
        max30205_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        max30205_info_t info;
        
        /* print max30205 info */
        max30205_info(&info);
        max30205_interface_debug_print("max30205: chip is %s.\n", info.chip_name);
        max30205_interface_debug_print("max30205: manufacturer is %s.\n", info.manufacturer_name);
        max30205_interface_debug_print("max30205: interface is %s.\n", info.interface);
        max30205_interface_debug_print("max30205: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max30205_interface_debug_print("max30205: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max30205_interface_debug_print("max30205: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max30205_interface_debug_print("max30205: max current is %0.2fmA.\n", info.max_current_ma);
        max30205_interface_debug_print("max30205: max temperature is %0.1fC.\n", info.temperature_max);
        max30205_interface_debug_print("max30205: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        max30205_interface_debug_print("max30205: SCL connected to GPIO3(BCM).\n");
        max30205_interface_debug_print("max30205: SDA connected to GPIO2(BCM).\n");
        max30205_interface_debug_print("max30205: OS connected to GPIO17(BCM).\n");
        
        return 0;
    }
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
        max30205_interface_debug_print("max30205: unknown status code.\n");
    }

    return 0;
}
