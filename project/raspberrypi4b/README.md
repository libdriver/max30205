### 1. Board

#### 1.1 Board Info

Chip Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(max30205 REQUIRED)
```


### 3. MAX30205

#### 3.1 Command Instruction

1. Show max30205 chip and driver information.

   ```shell
   max30205 (-i | --information)
   ```

2. Show max30205 help.

   ```shell
   max30205 (-h | --help)
   ```

3. Show max30205 pin connections of the current board.

   ```shell
   max30205 (-p | --port)
   ```

4. Run max30205 register test, address means iic address and it can be "00"-"1F".

   ```shell
   max30205 (-t reg | --test=reg) [--addr=<address>]
   ```

5. Run max30205 read test, num means test times, address means iic address and it can be "00"-"1F".

   ```shell
   max30205 (-t read | --test=read) [--addr=<address>] [--times=<num>]
   ```

6. Run max30205 interrupt test, num means test times, address means iic address and it can be "00"-"1F", low means interrupt low threshold, high means interrupt high threshold.

   ```shell
   max30205 (-t int | --test=int) [--addr=<address>] [--times=<num>] [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

7. Run max30205 read function, num means read times, address means iic address and it can be "00"-"1F".

   ```shell
   max30205 (-e read | --example=read) [--addr=<address>] [--times=<num>]
   ```

8. Run max30205 shot function, num means read times, address means iic address and it can be "00"-"1F".

   ```shell
   max30205 (-e shot | --example=shot) [--addr=<address>] [--times=<num>]
   ```

9. Run max30205 interrupt function, num means read times, address means iic address and it can be "00"-"1F", low means interrupt low threshold, high means interrupt high threshold.

   ```shell
   max30205 (-e int | --example=int) [--addr=<address>] [--times=<num>] [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

#### 3.2 Command Example

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
./max30205 -t reg --addr=00

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
./max30205 -t read --addr=00 --times=3

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
max30205: temperature: 28.0C.
max30205: temperature: 28.0C.
max30205: temperature: 27.9C.
max30205: extended read mode test.
max30205: temperature: 27.9C.
max30205: temperature: 27.9C.
max30205: temperature: 27.9C.
max30205: single read test.
max30205: temperature: 27.9C.
max30205: temperature: 27.8C.
max30205: temperature: 27.8C.
max30205: continuous read test.
max30205: temperature: 27.9C.
max30205: temperature: 27.9C.
max30205: temperature: 27.9C.
max30205: finished read test.
```

```shell
./max30205 -t int --addr=00 --times=3 --mode=CMP --low-threshold=35.0 --high-threshold=39.0

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
max30205: temperature: 27.7C.
max30205: 1 temperature is below low threshold, please see os pin.
max30205: temperature: 27.7C.
max30205: 2 temperature is below low threshold, please see os pin.
max30205: temperature: 27.7C.
max30205: 3 temperature is below low threshold, please see os pin.
max30205: finish interrupt test.
```

```shell
./max30205 -e read --addr=00 --times=3

max30205: 1/3.
max30205: temperature is 27.500C.
max30205: 2/3.
max30205: temperature is 27.512C.
max30205: 3/3.
max30205: temperature is 27.547C.
```

```shell
./max30205 -e shot --addr=00 --times=3

max30205: 1/3.
max30205: temperature is 27.387C.
max30205: 2/3.
max30205: temperature is 27.375C.
max30205: 3/3.
max30205: temperature is 27.387C.
```

```shell
./max30205 -e int --addr=00 --times=3 --mode=CMP --low-threshold=35.0 --high-threshold=39.0

max30205: 1/3.
max30205: temperature is 33.410C.
max30205: 2/3.
max30205: temperature is 33.602C.
max30205: 3/3.
max30205: temperature is 33.723C.
```

```shell
./max30205 -h

Usage:
  max30205 (-i | --information)
  max30205 (-h | --help)
  max30205 (-p | --port)
  max30205 (-t reg | --test=reg) [--addr=<address>]
  max30205 (-t read | --test=read) [--addr=<address>] [--times=<num>]
  max30205 (-t int | --test=int) [--addr=<address>] [--times=<num>]
           [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]
  max30205 (-e read | --example=read) [--addr=<address>] [--times=<num>]
  max30205 (-e shot | --example=shot) [--addr=<address>] [--times=<num>]
  max30205 (-e int | --example=int) [--addr=<address>] [--times=<num>]
           [--mode=<INT | CMP>] [--low-threshold=<low>] [--high-threshold=<high>]

Options:
      --addr=<address>           Set the addr pin and it can be "00" - "1F".([default: 00])
  -e <read | shot | int>, --example=<read | shot | int>
                                 Run the driver example.
  -h, --help                     Show the help.
      --high-threshold=<high>    Set the interrupt high threshold.([default: 39.0f])
  -i, --information              Show the chip information.
      --low-threshold=<low>      Set the interrupt low threshold.([default: 35.0f])
      --mode=<INT | CMP>         Set the interrupt mode.([default: CMP])
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read | int>, --test=<reg | read | int>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

