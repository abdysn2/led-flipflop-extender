// The number of data pins of the flipflop IC.
const int FLIPFLOP_PINS_NUMBER = 8;

// The numbers of the flipflop data pins on the board.
const int FLIPFLOP_DATA_PINS[FLIPFLOP_PINS_NUMBER] = {2, 3, 4, 5, 6, 7, 8, 9};

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

  BulkDigitalWrite(FLIPFLOP_PINS_NUMBER, FLIPFLOP_DATA_PINS, flipFlopZeroStates);
}

/*
 * FlipFlopWrite(ledsMap, decoderIndex): a function to set the flipFlop states to match the binary
 * value of ledsMap. The decoder index is used to specify the flipFlop to rite to.
*/
bool FlipFlopWrite(byte ledsMap, int decoderIndex){
  ConvertIntToPinStates(ledsMap, FLIPFLOP_PINS_NUMBER, flipFlopsStates);

  BulkDigitalWrite(FLIPFLOP_PINS_NUMBER, FLIPFLOP_DATA_PINS, flipFlopsStates);

  return decoderWrite(decoderIndex);
}
