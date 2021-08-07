int debugLevel = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FlipFlopInit();
  DecoderInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  FlipFlopWrite(1, 0);
  delay(1);
  FlipFlopWrite(0, 0);
  delay(16);
}
