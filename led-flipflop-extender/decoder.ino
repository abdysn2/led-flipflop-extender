// An array of lows to use to set all pins of the decoder to zero.
int decoderZeroStates[D_PINS_NUMBER];

// An array to hold the binary values of the decoder input. e.g. number 3 would be {1,1,0}
int decoderStates[D_PINS_NUMBER];

/*
 * DecoderInit(): Initialize the pins of the decoder by setting the pins mode
 * to OUTPUT and setting their states to LOWs.
*/
void DecoderInit(){
  for(int i=0; i < D_PINS_NUMBER; i++){
    decoderZeroStates[i] = LOW;
  }

  BulkPinMode(D_PINS_NUMBER, DECODER_INPUT_PINS, OUTPUT);
  pinMode(DECODER_ENABLE_PIN, OUTPUT);

  BulkDigitalWrite(D_PINS_NUMBER, DECODER_INPUT_PINS, decoderZeroStates);
  digitalWrite(DECODER_ENABLE_PIN, DECODER_ENABLE_PIN_LOW_STATE);
}

/*
 * decoderWrite(number): Take a number and convert it to binary then write
 * them to the decoder.
*/
bool decoderWrite(int number){
  int maxAllowedNumber = NUMBER_OF_FLIP_FLOP_ICS - 1;
  if (number > maxAllowedNumber){
    logToSerial("ERROR: number: " + (String)number + "is higher than " + (String)maxAllowedNumber + ".", 2);
    return false;
  }

  digitalWrite(DECODER_ENABLE_PIN, DECODER_ENABLE_PIN_LOW_STATE);

  PORTB = number;

  digitalWrite(DECODER_ENABLE_PIN, DECODER_ENABLE_PIN_HIGH_STATE);

  return true;
}
