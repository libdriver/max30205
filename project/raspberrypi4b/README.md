### 1. chip

#### 1.1 chip info

chip name : Raspberry Pi 4B

iic pin: SCL/SDA GPIO3/GPIO2

gpio pin: INT GPIO17.

### 2. install

#### 2.1 install info

```shell
sudo apt-get install libgpiod-dev

make
```

### 3. max30205

#### 3.1 command Instruction

​          max30205 is a basic command which can test all max30205 driver function:

​           -i        show max30205 chip and driver information.

​           -h       show max30205 help.

​           -p       show max30205 pin connections of the current board.

​           -t (reg -a <address>| read <times> -a <address> | int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>)

​           -t reg -a <address>        run max30205 register test. address means iic address and it can be "00"-"1F".

​           -t read <times> -a <address>        run max30205 read test. times means test times. address means iic address and it can be "00"-"1F".

​           -t  int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>        run max30205 interrupt test. times means test times. address means iic address and it can be "00"-"1F". lowthreshold means interrupt low threshold. highthreshold means interrupt high threshold.

​           -c (read <times> -a <address> | shot <times> -a <address> | int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>)

​           -c read <times> -a <address>         run max30205 read function. times means read times. address means iic address and it can be "00"-"1F".

​           -c shot <times> -a <address>         run max30205 shot function. times means read times. address means iic address and it can be "00"-"1F".

​           -c int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>         run max30205 interrupt function. times means read times. address means iic address and it can be "00"-"1F". lowthreshold means interrupt low threshold. highthreshold means interrupt high threshold.

#### 3.2 command example

```shell
./max30205 -i

max30205: chip is Maxim Integrated MAX30205.
max30205: manufacturer is Maxim Integrated.
max30205: interface is IIC.
max30205: driver version is 2.0.
max30205: min supply voltage is 2.7V.
max30205: max supply voltage is 3.3V.
max30205: max current is 20.00mA.
max30205: max temperature is 50.0C.
max30205: min temperature is 0.0C.
```

```shell
./max30205 -p

max30205: SCL connected to GPIO3(BCM).
max30205: SDA connected to GPIO2(BCM).
max30205: OS connected to GPIO17(BCM).
```

```shell
./max30205 -t reg -a 00

max30205: chip is Maxim Integrated MAX30205.
max30205: manufacturer is Maxim Integrated.
max30205: interface is IIC.
max30205: driver version is 2.0.
max30205: min supply voltage is 2.7V.
max30205: max supply voltage is 3.3V.
max30205: max current is 20.00mA.
max30205: max temperature is 50.0C.
max30205: min temperature is 0.0C.
max30205: start register test.
max30205: max30205_set_addr_pin/max30205_get_addr_pin test.
max30205: set addr pin ADDRESS_0.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_2.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_3.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_4.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_5.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_6.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_7.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_8.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_9.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_A.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_B.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_C.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_D.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_E.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_F.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_10.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_11.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_12.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_13.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_14.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_15.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_16.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_17.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_18.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_19.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1A.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1B.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1C.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1D.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1E.
max30205: check addr pin ok.
max30205: set addr pin ADDRESS_1F.
max30205: check addr pin ok.
max30205: max30205_set_data_format/max30205_get_data_format test.
max30205: set data format normal.
max30205: check data format ok.
max30205: set data format extended.
max30205: check data format ok.
max30205: max30205_set_interrupt_mode/max30205_get_interrupt_mode test.
max30205: set interrupt mode comparator.
max30205: check interrupt mode ok.
max30205: set interrupt mode interrupt.
max30205: check interrupt mode ok.
max30205: max30205_set_fault_queue/max30205_get_fault_queue test.
max30205: set fault queue 1.
max30205: check fault queue ok.
max30205: set fault queue 2.
max30205: check fault queue ok.
max30205: set fault queue 4.
max30205: check fault queue ok.
max30205: set fault queue 6.
max30205: check fault queue ok.
max30205: max30205_set_pin_polarity/max30205_get_pin_polarity test.
max30205: set pin polarity low.
max30205: check pin polarity ok.
max30205: set pin polarity high.
max30205: check pin polarity ok.
max30205: max30205_set_bus_timeout/max30205_get_bus_timeout test.
max30205: set bus timeout enable.
max30205: check bus timeout ok.
max30205: set bus timeout disable.
max30205: check bus timeout ok.
max30205: max30205_convert_to_register/max30205_convert_to_data test.
max30205: check normal mode convert ok.
max30205: max30205_convert_to_register/max30205_convert_to_data test.
max30205: check extended mode convert ok.
max30205: max30205_set_interrupt_low_threshold/max30205_get_interrupt_low_threshold test.
max30205: set interrupt low threshold 35.0.
max30205: check low threshold ok.
max30205: max30205_set_interrupt_low_threshold/max30205_get_interrupt_low_threshold test.
max30205: set interrupt high threshold 38.0.
max30205: check high threshold ok.
max30205: max30205_power_down test.
max30205: finish register test.
```

```shell
./max30205 -t read 3 -a 00

max30205: chip is Maxim Integrated MAX30205.
max30205: manufacturer is Maxim Integrated.
max30205: interface is IIC.
max30205: driver version is 2.0.
max30205: min supply voltage is 2.7V.
max30205: max supply voltage is 3.3V.
max30205: max current is 20.00mA.
max30205: max temperature is 50.0C.
max30205: min temperature is 0.0C.
max30205: start read test.
max30205: normal read mode test.
max30205: temperature: 27.5C.
max30205: temperature: 27.5C.
max30205: temperature: 27.5C.
max30205: extended read mode test.
max30205: temperature: 27.5C.
max30205: temperature: 27.5C.
max30205: temperature: 27.5C.
max30205: single read test.
max30205: temperature: 27.6C.
max30205: temperature: 27.5C.
max30205: temperature: 27.6C.
max30205: continuous read test.
max30205: temperature: 27.6C.
max30205: temperature: 27.6C.
max30205: temperature: 27.6C.
max30205: finished read test.
```

```shell
./max30205 -t int 3 -a 00 -m CMP -th 35.0 39.0

max30205: chip is Maxim Integrated MAX30205.
max30205: manufacturer is Maxim Integrated.
max30205: interface is IIC.
max30205: driver version is 2.0.
max30205: min supply voltage is 2.7V.
max30205: max supply voltage is 3.3V.
max30205: max current is 20.00mA.
max30205: max temperature is 50.0C.
max30205: min temperature is 0.0C.
max30205: start interrupt test.
max30205: temperature: 28.3C.
max30205: 1 temperature is below low threshold, please see os pin.
max30205: temperature: 28.3C.
max30205: 2 temperature is below low threshold, please see os pin.
max30205: temperature: 28.3C.
max30205: 3 temperature is below low threshold, please see os pin.
max30205: finish interrupt test.
```

```shell
./max30205 -c read 3 -a 00

max30205: 1/3.
max30205: temperature is 27.535C.
max30205: 2/3.
max30205: temperature is 27.527C.
max30205: 3/3.
max30205: temperature is 27.555C.
```

```shell
./max30205 -c shot 3 -a 00

max30205: 1/3.
max30205: temperature is 27.785C.
max30205: 2/3.
max30205: temperature is 27.848C.
max30205: 3/3.
max30205: temperature is 27.852C.
```

```shell
./max30205 -c int 3 -a 00 -m CMP -th 35.0 39.0

max30205: 1/3.
max30205: temperature is 27.977C.
max30205: 2/3.
max30205: temperature is 27.988C.
max30205: 3/3.
max30205: temperature is 27.992C.
```

```shell
./max30205 -h

max30205 -i
	show max30205 chip and driver information.
max30205 -h
	show max30205 help.
max30205 -p
	show max30205 pin connections of the current board.
max30205 -t reg -a <address>
	run max30205 register test.address means iic address and it can be "00"-"1F".
max30205 -t read <times> -a <address>
	run max30205 read test.times means test times.address means iic address and it can be "00"-"1F".
max30205 -t int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>
	run max30205 interrupt test.times means test times.address means iic address and it can be "00"-"1F".lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.
max30205 -c read <times> -a <address>
	run max30205 read function.times means read times.address means iic address and it can be "00"-"1F".
max30205 -c shot <times> -a <address>
	run max30205 shot function.times means read times.address means iic address and it can be "00"-"1F".
max30205 -c int <times> -a <address> -m (INT | CMP) -th <lowthreshold> <highthreshold>
	run max30205 interrupt function.times means read times.address means iic address and it can be "00"-"1F".lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.
```

