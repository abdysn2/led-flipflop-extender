// A constant array of lows to use to set all pins of the flipflop to zero.
int flipFlopZeroStates[FLIPFLOP_PINS_NUMBER];

// An array to hold the binary values of the flipflop data.
int flipFlopsStates[FLIPFLOP_PINS_NUMBER];

/*
 * FlipFlopInit(): Initialize the pins of the flipflop by setting the pins mode
 * to OUTPUT and setting their states to LOWs.
*/
void FlipFlopInit(){
  for(int i=0; i < FLIPFLOP_PINS_NUMBER; i++){
    flipFlopZeroStates[i] = LOW;
  }

  BulkPinMode(FLIPFLOP_PINS_NUMBER, FLIPFLOP_DATA_PINS, OUTPUT);

  for(int i = 0; i < NUMBER_OF_FLIP_FLOP_ICS; i++){
    FlipFlopWrite(0, i);
  }

  BulkDigitalWrite(FLIPFLOP_PINS_NUMBER, FLIPFLOP_DATA_PINS, flipFlopZeroStates);
}

/*
 * FlipFlopWrite(ledsMap, decoderIndex): a function to set the flipFlop states to match the binary
 * value of ledsMap. The decoder index is used to specify the flipFlop to rite to.
*/
bool FlipFlopWrite(byte ledsMap, int decoderIndex){
  PORTD = ledsMap;

  return decoderWrite(decoderIndex);
}
