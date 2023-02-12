# MuTag
Repository for PCB and source file of the MuHack NFC Tag keychain.

This is a custom printed circuit board that uses an STM8L microcontroller and an ST25 NFC ISO15 tag. 

The STM8l101f3 is a low-power, 8-bit MCU from STMicroelectronics that is ideal for a variety of applications. 

From the MCU is it possible to access the NFC tag using I2C, to modify the tag's configuration and read/write data.

![Alt text](images/collage.png?raw=true "MuTag")

## Features
- STM8L101F3 MCU
- ST25 NFC ISO15 tag with 4Kbit memory
- Energy harvesting
- Fast transfer memory, 256bytes of _Mailbox_
- 2 LEDs
- GPIOs from MCU and single GPO from NFC tag
- I2C and UART (TBD) interfaces 
- Small form factor: only 20x30mm

# Getting Started

In the Hardware folder you can find the PCB design files and the schematic. 

The leds are connected to:
 - Rigth led on pin 9 (Port D0)
 - Left led on pin 10 (Port B0)

The NFC tag is connected to the MCU's I2C bus:
 - SDA on pin 18 (Port C0)
 - SCL on pin 19 (Port C1)

The NFC GPO is also connected to the MCU's pin 20 (Port C2).

## Activating Energy Harvesting Mode with the ST25 Android App

By default, the ST25 NFC tag is set to "on demand" energy harvesting mode.
To activate energy harvesting mode on an ST25 NFC tag, you will need to use the ST25 Android app. The following steps outline the process for activating energy harvesting mode:

1. Scan the tag with the ST25 Android app and from the left menu go to "Register Management"

2. Re-scan the tag to update the tag's configuration. You will see a register called "EH_MODE". By default, this register is set to 0x01, which means that energy harvesting mode is set "on demand". To enable energy harvesting mode, change the value of this register to 0x00

3. While maintaining the tag in the field, tap the "Save" button to write the new configuration to the tag

## Programming the STM8L MCU
The PCB can be programmed using a STLink programmer. Connect the SWIM port by using SWIM/RESET/3v3/GND pins on the PCB. 
The PCB must be powered by an alternate power source, in parallel with the programmer, as the STLink does not provide 3v3 power (the pin is only for voltage reference).

To program the STM8L MCU on this PCB, you will need to use the stm8flash tool and an STLink programmer. The following steps outline the process for programming the MCU:

1. Install the stm8flash tool on your computer. This tool can be downloaded from the official stm8flash GitHub repository (https://github.com/vdudouyt/stm8flash) or from your packets manager.

2. Connect your STLink programmer to the PCB and to your computer. The SWIM/RESET/3v3/GND pins on the PCB must be connected to the SWIM/RESET/3v3/GND pins on the STLink programmer. The PCB must also be powered by an alternate power source, in parallel with the programmer, as the STLink does not provide 3v3 power (the pin is only for voltage reference).

3. Run the following command to flash the binary file to the MCU:

```bash
./stm8flash -c stlinkv2 -p stm8l101f3 -w path/to/binary
```

It's important to note that the above steps are a general outline and may vary slightly depending on the specific STLink programmer you are using and the binary file you are uploading. Before attempting to program your MCU, make sure to read the documentation for your STLink programmer and the stm8flash tool.

## TODOS:
- [ ] Round the corners of the PCB
- [ ] Move and make bigger pads for programming
- [ ] Add a 3D model of the PCB
- [ ] Find a good bootloader to enable UART programming
- [ ] Upload decent photos of the final product
- [ ] Evaluate the possibility of removing the 3v3 diode regulator
