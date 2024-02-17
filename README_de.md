[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX30205

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max30205/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der Temperatursensor MAX30205 misst die Temperatur genau und liefert einen Übertemperatur-Alarm/Unterbrechung/Abschaltung-Ausgang. Dieses Gerät wandelt die Temperaturmessungen mithilfe eines hochauflösenden Sigma-Delta-Analog-Digital-Wandlers (ADC) in digitale Form um. Die Genauigkeit entspricht der klinischen Thermometriespezifikation von ASTM E1112, wenn es auf die endgültige Leiterplatte gelötet wird. Die Kommunikation erfolgt über eine I2C-kompatible serielle 2-Draht-Schnittstelle. Die serielle I2C-Schnittstelle akzeptiert standardmäßige Schreib-Byte-, Lese-Byte-, Sende-Byte- und Empfangs-Byte-Befehle, um die Temperaturdaten zu lesen und das Verhalten des Open-Drain-über-Temperatur-Abschaltausgangs zu konfigurieren. Der MAX30205 verfügt über drei Adressauswahlleitungen mit insgesamt 32 verfügbaren Adressen. Der Sensor verfügt über einen Versorgungsspannungsbereich von 2,7 V bis 3,3 V, einen niedrigen Versorgungsstrom von 600 μA und eine lockup-geschützte I2C-kompatible Schnittstelle, die ihn ideal für tragbare Fitness- und medizinische Anwendungen macht. Dieses Bauteil ist in einem 8-poligen TDFN-Gehäuse erhältlich und arbeitet über einen Temperaturbereich von 0 NC bis +50 NC. MAX30205 wird in der Fitness und medizinischen Behandlung eingesetzt.

LibDriver MAX30205 ist der Treiber mit vollem Funktionsumfang von MAX30205, der von LibDriver gestartet wurde. Es bietet kontinuierliche Temperaturmessung, Einzeltemperaturmessung und Temperaturunterbrechungsfunktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MAX30205-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MAX30205 IIC.

/test enthält den Testcode des LibDriver MAX30205-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MAX30205-Beispielcode.

/doc enthält das LibDriver MAX30205-Offlinedokument.

/Datenblatt enthält MAX30205-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/max30205/index.html](https://www.libdriver.com/docs/max30205/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.