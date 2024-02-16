[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX30205

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max30205/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX30205温度センサーは温度を正確に測定し、過熱アラーム/割り込み/シャットダウン出力を提供します。このデバイスは、高分解能、シグマデルタ、アナログ-デジタルコンバーター（ADC）を使用して、温度測定値をデジタル形式に変換します。精度は、最終PCBにはんだ付けされたときに、ASTME1112の臨床温度測定仕様に適合します。通信は、I2C互換の2線式シリアルインターフェースを介して行われます。 I2Cシリアルインターフェースは、標準の書き込みバイト、読み取りバイト、送信バイト、および受信バイトコマンドを受け入れて、温度データを読み取り、温度シャットダウン出力に対するオープンドレインの動作を構成します。 MAX30205は、合計32の使用可能なアドレスを持つ3つのアドレス選択ラインを備えています。センサーは、2.7V〜3.3Vの供給電圧範囲、600μAの低い供給電流、およびウェアラブルフィットネスや医療アプリケーションに最適なロックアップ保護されたI2C互換インターフェイスを備えています。このデバイスは8ピンTDFNパッケージで提供され、0NC〜+50NCの温度範囲で動作します。 MAX30205はフィットネスや医療で使用されています。

LibDriver MAX30205は、LibDriverによって起動されたMAX30205の全機能ドライバーです。連続的な温度読み取り、単一の温度読み取り、および温度割り込み機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MAX30205のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MAX30205用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MAX30205ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MAX30205プログラミング例が含まれています。

/ docディレクトリには、LibDriver MAX30205オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MAX30205データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/max30205/index.html](https://www.libdriver.com/docs/max30205/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。