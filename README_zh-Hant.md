[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX30205

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max30205/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX30205溫度傳感器可高精度測量溫度，提供過熱報警/中斷/關斷輸出。器件利用高分辨率、Σ-Δ、模/數轉換器(ADC)將溫度測量值轉換為數字形式。焊接到最終PCB上時，精度滿足ASTM E1112的臨床測溫儀技術規範。通過I2C兼容2線串行接口進行通信。 I2C串行接口支持標準寫字節、讀字節、發送字節和接收字節命令，以讀取溫度數據以及配置開漏過熱關斷輸出模式。 MAX30205具有三條地址選擇線，提供總共32個可用地址。傳感器採用2.7V至3.3V供電電壓範圍、600µA低供電電流、鎖定保護I2C兼容接口，使其可理想用於可穿戴健身和醫療應用。器件採用8引腳TDFN封裝，工作在0°C至+50°C溫度範圍。 MAX30205被用於健身和醫療等。

LibDriver MAX30205是LibDriver推出的MAX30205的全功能驅動，該驅動提供連續溫度讀取、單次溫度讀取和溫度中斷等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver MAX30205的源文件。

/interface目錄包含了LibDriver MAX30205與平台無關的IIC總線模板。

/test目錄包含了LibDriver MAX30205驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver MAX30205編程範例。

/doc目錄包含了LibDriver MAX30205離線文檔。

/datasheet目錄包含了MAX30205數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/max30205/index.html](https://www.libdriver.com/docs/max30205/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。