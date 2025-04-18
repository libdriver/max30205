[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX30205

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max30205/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MAX30205 temperature sensor accurately measures temperature and provide an over temperature alarm/interrupt/shutdown output. This device converts the temperature measurements to digital form using a high resolution, sigma-delta, analog-to-digital converter (ADC).Accuracy meets clinical thermometry specification of the ASTM E1112 when soldered on the final PCB. Communication is through an I2C-compatible, 2-wire serial interface. The I2C serial interface accepts standard write byte, read byte, send byte, and receive byte commands to read the temperature data and configure the behavior of the open drain over temperature shutdown output. The MAX30205 features three address select lines with a total of 32 available addresses. The sensor has a 2.7V to 3.3V supply voltage range, low 600μA supply current, and a lockup-protected I2C-compatible interface that make it ideal for wearable fitness and medical applications. This device is available in an 8-pin TDFN package and operates over the 0NC to +50NC temperature range. MAX30205 is used in fitness and medical treatment.

LibDriver MAX30205 is a full-featured driver of MAX30205 launched by LibDriver. It provides continuous temperature reading, single temperature reading and temperature interrupt functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MAX30205 source files.

/interface includes LibDriver MAX30205 IIC platform independent template.

/test includes LibDriver MAX30205 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MAX30205 sample code.

/doc includes LibDriver MAX30205 offline document.

/datasheet includes MAX30205 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_max30205_basic.h"

uint8_t res;
uint8_t i;
float s;

res = max30205_basic_init(MAX30205_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    max30205_interface_delay_ms(1000);
    res = max30205_basic_read((float *)&s);
    if (res != 0)
    {
        (void)max30205_basic_deinit();

        return 1;
    }
    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
    
    ...
    
}

...

(void)max30205_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_max30205_shot.h"

uint8_t res;
uint8_t i;
float s;

res = max30205_shot_init(MAX30205_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    max30205_interface_delay_ms(1000);
    res = max30205_shot_read((float *)&s);
    if (res != 0)
    {
        (void)max30205_shot_deinit();

        return 1;
    }
    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);
    
    ...
    
}

...

(void)max30205_shot_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_max30205_interrupt.h"

uint8_t res;
uint8_t i;
float s;
uint8_t g_flag;   

res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}
res = max30205_interrupt_init(MAX30205_ADDRESS_0, MAX30205_INTERRUPT_MODE_INTERRUPT, 35.5f, 37.6f);
if (res != 0)
{
    (void)gpio_interrupt_deinit();

    return 1;
}

...

g_flag = 0;
for (i = 0; i < 3; i++)
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

        ...
        
        break;
    }
    max30205_interface_debug_print("max30205: temperature is %0.3fC.\n", s);

    ...
    
}

...

(void)gpio_interrupt_deinit();
(void)max30205_interrupt_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/max30205/index.html](https://www.libdriver.com/docs/max30205/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.