# GR-MANGO_2JCIE-EV01-RP1_sample
It is a sample program for OMRON sensor evaluation kit **2JCIE-EV01-RP1** with **GR-MANGO** boards.

2JCIE-EV01 sensor evaluation boards are Open Platforms by OMRON corporation and
prototype your ideas with variety environmental information.

English : https://www.components.omron.com/sensor/evaluation-board/2jcie  
日本語 : https://www.omron.co.jp/ecb/sensor/evaluation-board/2jcie  


## Description
Sample programs for acquiring data from sensors on 2JCIE-EV01. there samples output the sensor data to console.  

|Sensor                                  |Part number|Mode         |Manufacturer      |Interface|
|:---------------------------------------|:----------|:------------|:-----------------|:--------|
|Temperature / humidity sensor           |U1         |SHT30-DIS-B  |Sensirion         |I2C      |
|Ambient light sensor                    |U2         |OPT3001DNP   |Texas Instruments |I2C      |
|MEMS digital barometric pressure sensor |U3         |2SMPB-02E    |OMRON             |I2C      |
|MEMS digital motion sensor              |U5         |LIS2DW12     |STMicroelectronics|SPI      |


Example of console display during program execution.  
```
GR-MANGO x Omron 2JCIE-EV01 Demoo

[SHT30-DIS-B] Temperature / humidity sensor
   temperature : 27.67 [degC]
   humidity    : 43.99 [%RH]

[OPT3001DNP] Ambient light sensor
   illuminance :  2.60 [lx]

[2SMPB-02E] MEMS digital barometric pressure sensor
   pressure    : 100262.6 [Pa] (00A13D1Ah)
   temperature : 27.48 [degC] (006975C5h)

[LIS2DW12] MEMS digital motion sensor
   x :    28 [mg]
   y :   -12 [mg]
   z :   981 [mg]
```

### Terminal setting
|             |         |
|:------------|:--------|
| Baud rate   | 115,200 |
| Data        | 8bit    |
| Parity      | none    |
| Stop        | 1bit    |
| Flow control| none    |


## Development environment (Mbed CLI)
Information of Mbed CLI that includes install&quick start guide is as the following.  
[Installation](https://github.com/ARMmbed/mbed-cli/blob/1.8.3/README.md#installation)  

How to import and build this sample  
```
$ cd <projects directory>
$ mbed import https://github.com/d-kato/GR-MANGO_2JCIE-EV01-RP1_sample
$ cd GR-MANGO_2JCIE-EV01-RP1_sample
$ mbed compile -m GR_MANGO -t GCC_ARM --profile debug
```

## About custom boot loaders
This sample uses ``custom bootloader`` ``revision 5``, and you can drag & drop the "xxxx_application.bin" file to write the program. Please see [here](https://github.com/d-kato/bootloader_d_n_d) for the detail.  
### How to write program
#### For GR-MANGO
When using ``DAPLink``, please use ``xxxx.bin`` as following.  
1. Connect the ``micro USB type B terminal`` to the PC using a USB cable.
2. You can find the ``MBED`` directory.
3. Drag & drop ``xxxx.bin`` to the ``MBED`` directory.  
4. When writing is completed, press the reset button.  

When using ``custom bootloader``, please use ``xxxx_application.bin`` as following.  
1. Connect the ``USB type C terminal`` to the PC using a USB cable.  
2. Hold down ``USB0`` and press the reset button.  
3. You can find the ``GR-MANG`` directory.  
4. Drag & drop ``xxxx_application.bin`` to the ``GR-MANGO`` directory.  
5. When writing is completed, press the reset button.  

**Attention!**  
For the first time only, you need to write a ``custom bootloader`` using ``DAPLink``.  
