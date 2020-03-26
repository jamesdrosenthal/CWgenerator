/*
ADF4360-0 CONTROLLER V6
 7-5-2019 
*/

// include the SPI library:
#include <SPI.h>

//parameters to initialize the ADF4360-0 (2.4 GHz CW Generator)
int r1=0x04;
int r2=0x00;
int r3=0x81;
int c1=0x00; //use 0x06 for ICP=1.25 mA, 0x0F for 2.5 mA
int c2=0x29; //use 0xF9 for max power, 0xF1 for max power and no mute, 0xC9 for lower power, 0x39 for full power and Icp = 0.31 mA
int c3=0x24;
int n1=0x02;
int n2=0x5B; //use 0x59 for 2.4065 GHz and 0x5B for 2.4145 GHz
int n3=0x16;
int flagIter = 0;

void setup() {
//  * LE - to digital pin 10  (SS pin) 
//  * DATA - to digital pin 11 (MOSI pin)
//  * CLK - to digital pin 13 (SCK pin)
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  
  digitalWrite(SS, LOW);

  // initialize SPI:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setDataMode(SPI_MODE3);
  digitalWrite(SS, LOW);
}

void loop() {
  delay(1000);
  if(flagIter<2){
  sendSPI(r1,r2,r3);  //send R counter latch
  sendSPI(c1,c2,c3);  //send control latch
  delay(7);
  sendSPI(n1,n2,n3);  //send N counter latch
  delay(1000);
  flagIter = flagIter + 1;
  }
}

int sendSPI( int v1,int v2,int v3) {
  SPI.transfer(v1);
  SPI.transfer(v2);
  SPI.transfer(v3);
  // take the SS pin high to de-select the chip:
  digitalWrite(SS,HIGH);
  digitalWrite(SS, LOW);
}





