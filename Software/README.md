# Software
This directory contains sketches and libraries for the MuTag project.

## Board Definition

```
#define YELLOW_LED 0
#define GREEN_LED 1
#define BLUE_LED 2
#define RED_LED 3

#define INT_PIN 8 // INT0

#define TAG_I2C_ADDR 83
```

## Rainbow
This sketch is used to test the LEDs on the MuTag board. It will cycle through all LEDs present on the board.

## Hello MuHack
This sketch is used to test the I2C communication with the NFC tag on the MuTag board. It will check if the 224th bytes of the tag's memory is equal to ```0x01```. If it is, it will write "Hello MuHack!", otherwise it will erease said memory.