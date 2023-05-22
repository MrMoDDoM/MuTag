#include <Wire.h>

#define YELLOW_LED A0
#define GREEN_LED A1
#define BLUE_LED A2
#define RED_LED A3

#define TAG_I2C_ADDR 83
#define POS_TIMES 212
#define HELLO_POS 224

void setup() {
  
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Wire.begin();
  hello_muhack();
  Wire.end();
}

void loop() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  delay(50);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(50);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  delay(50);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(50);
}

/* 
* This function writes "Hello MuHack!" to the EEPROM 
* only if finds that the first byte is 1.
* Otherwise, it ereases that portion of EEPROM
*/
void hello_muhack() {
  char buf[13] = {0};
  if (readEEPROM(TAG_I2C_ADDR, HELLO_POS) == 1){
    strcpy(buf,"Hello MuHack!");
  } 

  for(int i = 0; i < 13; i++){
    writeEEPROM(TAG_I2C_ADDR, HELLO_POS+i, buf[i]);
  }

}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}