#include <SoftwareSerial.h>

int debugLevel = 1;
SoftwareSerial logSerial(14, 15);

void setup() {
  // put your setup code here, to run once:
  logSerial.begin(9600);
  FlipFlopInit();
  DecoderInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  FlipFlopWrite(1, 2);
  delay(1);
  FlipFlopWrite(0, 2);
  delay(7);
}
