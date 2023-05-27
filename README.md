# MuTag v2.1
Repository for PCB and source file of the MuHack NFC Tag keychain.

This is a custom printed circuit board featuring an ATTiny44a microcontroller and an ST25 NFC ISO15 tag. 

From the MCU is it possible to access the NFC tag using I2C, to modify the tag's configuration and read/write data.

![MuTag](images/mutag_v2_1.jpg?raw=true "MuTag")

## Features
- ATTiny44a MCU
- ST25 NFC ISO15 tag with 4Kbit memory
- Energy harvesting
- Fast transfer memory, 256bytes of _Mailbox_
- 4 LEDs of different colors
- I2C and UART (TBD) interfaces 
- Small form factor: only 20x60mm

# Getting Started

In the Hardware folder you can find the PCB design files and the schematics. 

```
#define YELLOW_LED 0
#define GREEN_LED 1
#define BLUE_LED 2
#define RED_LED 3
```

The LEDs are connected to:
- Yellow led on pin 0 (Port PA0)
- Green led on pin 1 (Port PA1)
- Blue led on pin 2 (Port PA2)
- Red led on pin 3 (Port PA3)

The NFC tag is connected to the ATTiny's I2C bus:
- SDA on pin 6 (Port PA6)
- SCL on pin 4 (Port PA4)

The NFC GPO is also connected to the ATTiny's INT0 interrupt port (Port PB2).

## Activating Energy Harvesting Mode with the ST25 Android App

By default, the ST25 NFC tag is set to "on demand" energy harvesting mode.
To activate energy harvesting mode on the ST25 NFC IC, you will need to use the ST25 Android app (future implementation of the software will automatically activate this through the I2C communication).

Follow these steps:

1. Download the ST25 Android app from the Google Play Store (https://play.google.com/store/apps/details?id=com.st.st25nfc)

2. Scan the tag with the ST25 Android app and from the left menu go to "Register Management"

3. Re-scan the tag to update the tag's configuration. You will see a register called ``EH_MODE``. By default, this register is set to ``0x01``, which means that energy harvesting mode is set "on demand". To enable energy harvesting mode, change the value of this register to ``0x00``

4. While maintaining the tag in the field, tap the "Save" button to write the new configuration to the tag (the default password is all zeros, just tap "OK" to continue)

## Programming the ATTiny44a MCU

Generally speaking, the ATTiny44a MCU must be programmed using an external ISP programmer. In this case, we will use an Arduino Uno as an ISP programmer (you can use any other Arduino board that can be used as an ISP). 

1. Flash the ```ArduinoISP``` sketch (found in the File -> Example menu) to an Arduino (or any other Arduino board that can be used as an ISP)

2. Add the following line to "Additional Boards Manager URLs" in the Arduino IDE preferences:

```http://drazzy.com/package_drazzy.com_index.json```

3. Install the ```ATTinyCore``` by __Spence Konde__ board definition (found in the Tool -> Board -> Board Manager menu) and select the following settings:

| Setting | Value |
|---------|-------|
| Board | ATTiny24/44/84 (noBootloader) |
| Chip | ATTiny44(a) (*Note: for v2.0 select 24*)|
| Clock | 1 MHz internal |
| BOD | Disabled |
| LTO | Enabled |
| EEPROM | EEPROM retained |
| millis()/micros() | Enabled |
| Programmer | Arduino as ISP |

4. Connect the MuTag to the Arduino as follows:

| MuTag | Arduino |
|-------|---------|
| VDD   | 5V      |
| GND   | GND     |
| SCK   | 13      |
| MISO  | 12      |
| MOSI  | 11      |
| RST   | 10      |

~~*NOTE: The MuTag through hole ports are of 1.27mm diameter, enough to fit a common jumper wire. So with a little bit of patience you can push the pin rigth into the hole without soldering.*~~ 

*The holes dimension was changed to a standard 2.54mm in the v2.1*

5. Take another jump wire and connect it the ```RESET``` pin of the Arduino and leave the other end unconnected

6. Now the tricky part: to program the MuTag we need to send the Arduino in "reset mode" for a short period of time. To do this, we need to connect the ```RESET``` pin of the Arduino to ground (i.e. by touching the USB ground shield with the unconnected end the ```RESET``` wire) rigth before we press the "Upload" button in the Arduino IDE. Wait about 2/3 seconds and then release the RESET wire. You should see the Arduino IDE uploading the sketch to the MuTag.

*NOTE: Depending on your Arduino IDE version, you might need to use the "Upload using Programmer" option in the Sketch menu instead of the "Upload" button.*

## Accessing the NFC Tag with the I2C Interface
The internal memory of the ST25 NFC tag can be accessed through the I2C bus as a standard EEPROM memory. The I2C address of the tag is ```0x53```.

The "Hello_MuHack.ino" sketch is a simple example of how to read and write data to the tag.

## TODOS:
- [ ] Add a 3D model of the PCB
- [ ] Find a good bootloader to enable UART programming 
- [x] Evaluate the possibility of removing the diodes
- [x] Evaluate to move and make bigger pads for programming
- [x] Evaluate to change the MCU to an ATTiny44/84 to have more memory
- [x] Evaluate to remove the ```RESET``` pad

## Notes on the Bootloader
The bootloader is a small piece of code that is stored in the MCU's memory and that allows to program via UART. This is very useful because it avoid the need of an external SPI programmer.

The [Optiboot version compiled by Spence Konde](https://github.com/SpenceKonde/ATTinyCore/blob/v2.0.0-devThis-is-the-head-submit-PRs-against-this/avr/extras/ATtiny_x4.md#optiboot-bootloader) uses the pins ```AIN0``` and ```AIN1```, currently connected to the LEDs. This leaves us with two options:
- Remove the LEDs and use the pins for programming via UART
- Recompiling the bootloader to use different pins

Since this project is intended to be used as a keychain, which means that is to be programmed only once, I decided to not invest time in the bootloader and leave the LEDs as they are.

## License
Copyright (c) 2023 MrMoDDoM

This project is licensed under the GNU AFFERO GENERAL PUBLIC License - see the [LICENSE.md](LICENSE.md) file for details
