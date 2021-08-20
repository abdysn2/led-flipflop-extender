#include <SoftwareSerial.h>

// The number of the decoder input pins.
const int D_PINS_NUMBER = 3;

// The number of flipFlop chips
const int NUMBER_OF_FLIP_FLOP_ICS = pow(2, D_PINS_NUMBER);

// The decoder input pins on the board.
const int DECODER_INPUT_PINS[D_PINS_NUMBER] = {8, 9, 10};

// The decoder enable pin on the board.
const int DECODER_ENABLE_PIN = 11;

// Enable pin low state
const int DECODER_ENABLE_PIN_LOW_STATE = LOW;

// Enable pin high state
const int DECODER_ENABLE_PIN_HIGH_STATE = HIGH;

// The number of data pins of the flipflop IC.
const int FLIPFLOP_PINS_NUMBER = 8;

// The numbers of the flipflop data pins on the board.
const int FLIPFLOP_DATA_PINS[FLIPFLOP_PINS_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7};

int debugLevel = 1;
SoftwareSerial logSerial(14, 15);

struct FlipFlopsStates {
  int ledsStates[NUMBER_OF_FLIP_FLOP_ICS];
  int period;
};

struct Sequence {
  FlipFlopsStates *sequence;
  int sequenceLength;
  int statesCurrentIndex;
  unsigned long statesNextEventTime;
};

int numberOfStates = 8;

FlipFlopsStates *sequence1FlipFlopStates = new FlipFlopsStates[numberOfStates] {
    {{1, 0, 1, 0, 1, 0, 1, 0}, 1000},
    {{0, 1, 0, 1, 0, 1, 0, 1}, 1000},
    {{1, 0, 1, 0, 1, 0, 1, 0}, 500},
    {{0, 1, 0, 1, 0, 1, 0, 1}, 500},
    {{1, 0, 1, 0, 1, 0, 1, 0}, 200},
    {{0, 1, 0, 1, 0, 1, 0, 1}, 200},
    {{1, 0, 1, 0, 1, 0, 1, 0}, 100},
    {{0, 1, 0, 1, 0, 1, 0, 1}, 100}
};

Sequence sequence1 = {
  sequence1FlipFlopStates,
  numberOfStates,
  0,
  0
};

Sequence StaticStatesUpdate(Sequence sequence, int lastState = -1);

void setup() {
  // put your setup code here, to run once:
  logSerial.begin(9600);
  FlipFlopInit();
  DecoderInit();
}

void loop() {
  sequence1 = StaticStatesUpdate(sequence1);
}

bool WriteState(int *states){
  return WriteState(states, 0, NUMBER_OF_FLIP_FLOP_ICS);
}

bool WriteState(int *states, int numberOfICs){
    return WriteState(states, 0, numberOfICs);
}

bool WriteState(int *states, int start, int numberOfICs){
  for(int i = start; i < (start + numberOfICs); i++){
    if (!FlipFlopWrite(states[i], i))
      return false;
  }
}

Sequence StaticStatesUpdate(Sequence sequence, int lastState = -1){
  if(lastState < 0 || lastState >= sequence.sequenceLength){
    lastState = sequence.sequenceLength - 1; 
  }

  unsigned long currentTime = millis();

  if(currentTime >= sequence.statesNextEventTime){
    WriteState(sequence.sequence[sequence.statesCurrentIndex].ledsStates);

    sequence.statesNextEventTime = currentTime + sequence.sequence[sequence.statesCurrentIndex].period;

    sequence.statesCurrentIndex++;
    if(sequence.statesCurrentIndex > lastState){
      sequence.statesCurrentIndex = 0;
    }
  }

  return sequence;
}
