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
  //update_counter(POS_TIMES);
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

void hello_muhack(){
  char buf[13] = {0};
  if (readEEPROM(TAG_I2C_ADDR, HELLO_POS) == 1){
    strcpy(buf,"Hello MuHack!");
  } 

  for(int i = 0; i < 13; i++){
    writeEEPROM(TAG_I2C_ADDR, HELLO_POS+i, buf[i]);
  }

}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

// void update_counter(int pos){
//   byte buf[4];
//   int val = 0;  
//   int i = 0;
//   for( i = 0; i < 4; i++){
//     buf[i] = readEEPROM(TAG_I2C_ADDR, pos+i);
//   }

//   val += buf[0] << 24;
//   val += buf[1] << 16;
//   val += buf[2] << 8;
//   val += buf[3];

//   val ++;

//   for (size_t i = 0; i < 4; i++) {
//     size_t shift = 8 * (4 - 1 - i);
//     buf[i] = (val >> shift) & 0xff;
//   }

//   for(i = 0; i < 4; i++){
//       writeEEPROM(TAG_I2C_ADDR, pos+i, buf[i]);
//   }
// }

// void update_counter(int pos){
//   char buf[4];
//   byte i = 0;
//   for( i = 0; i < 4; i++){
//     buf[i] = readEEPROM(TAG_I2C_ADDR, pos+i);
//   }

//   int count = 0;
//   for (i = 0; buf[i] != '\0'; ++i)
//     count = count * 10 + buf[i] - '0';

//   count ++;

//   while (count != 0){
//     int rem = count % 10;
//     buf[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
//     count = count/10;
//   }

//   for(i = 0; i < 4; i++){
//       writeEEPROM(TAG_I2C_ADDR, POS_TIMES+i, buf[4-i-1]);
//   }
// }