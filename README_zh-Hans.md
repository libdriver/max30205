[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX30205

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max30205/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX30205温度传感器可高精度测量温度，提供过热报警/中断/关断输出。器件利用高分辨率、Σ-Δ、模/数转换器(ADC)将温度测量值转换为数字形式。焊接到最终PCB上时，精度满足ASTM E1112的临床测温仪技术规范。通过I2C兼容2线串行接口进行通信。I2C串行接口支持标准写字节、读字节、发送字节和接收字节命令，以读取温度数据以及配置开漏过热关断输出模式。MAX30205具有三条地址选择线，提供总共32个可用地址。传感器采用2.7V至3.3V供电电压范围、600µA低供电电流、锁定保护I2C兼容接口，使其可理想用于可穿戴健身和医疗应用。器件采用8引脚TDFN封装，工作在0°C至+50°C温度范围。MAX30205被用于健身和医疗等。

LibDriver MAX30205是LibDriver推出的MAX30205的全功能驱动，该驱动提供连续温度读取、单次温度读取和温度中断等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MAX30205的源文件。

/interface目录包含了LibDriver MAX30205与平台无关的IIC总线模板。

/test目录包含了LibDriver MAX30205驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MAX30205编程范例。

/doc目录包含了LibDriver MAX30205离线文档。

/datasheet目录包含了MAX30205数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/max30205/index.html](https://www.libdriver.com/docs/max30205/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。