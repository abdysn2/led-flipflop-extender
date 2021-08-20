#include <SoftwareSerial.h>
#include "src/Sequence/Sequence.h"

const int D_PINS_NUMBER = 3;
const int NUMBER_OF_FLIP_FLOP_ICS = pow(2, D_PINS_NUMBER);
const int DECODER_INPUT_PINS[D_PINS_NUMBER] = {8, 9, 10};
const int DECODER_ENABLE_PIN = 11;
const int DECODER_ENABLE_PIN_LOW_STATE = LOW;
const int DECODER_ENABLE_PIN_HIGH_STATE = HIGH;
const int FLIPFLOP_PINS_NUMBER = 8;
const int FLIPFLOP_DATA_PINS[FLIPFLOP_PINS_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7};

int debugLevel = 1;
SoftwareSerial logSerial(14, 15);

int numberOfStates = 8;

FlipFlopsStates<NUMBER_OF_FLIP_FLOP_ICS> *sequence1FlipFlopStates = new FlipFlopsStates<NUMBER_OF_FLIP_FLOP_ICS>[numberOfStates] {
    {1000, {1, 0, 1, 0, 1, 0, 1, 0}},
    {1000, {0, 1, 0, 1, 0, 1, 0, 1}},
    {500, {1, 0, 1, 0, 1, 0, 1, 0}},
    {500, {0, 1, 0, 1, 0, 1, 0, 1}},
    {200, {1, 0, 1, 0, 1, 0, 1, 0}},
    {200, {0, 1, 0, 1, 0, 1, 0, 1}},
    {100, {1, 0, 1, 0, 1, 0, 1, 0}},
    {100, {0, 1, 0, 1, 0, 1, 0, 1}}
};

StaticSequence<NUMBER_OF_FLIP_FLOP_ICS> sequence1 =  StaticSequence<NUMBER_OF_FLIP_FLOP_ICS>(sequence1FlipFlopStates, numberOfStates);

void StatesUpdate(Sequence<NUMBER_OF_FLIP_FLOP_ICS> &sequence, int lastState = -1);

void setup() {
  // put your setup code here, to run once:
  logSerial.begin(9600);
  FlipFlopInit();
  DecoderInit();
}

void loop() {
  StatesUpdate(sequence1);
}

void StatesUpdate(Sequence<NUMBER_OF_FLIP_FLOP_ICS> &sequence, int lastState = -1){
  unsigned long currentTime = millis();

  if(currentTime >= sequence.statesNextEventTime){
    WriteState(sequence.GetState().ledsStates);

    sequence.statesNextEventTime = currentTime + sequence.GetState().period;

    sequence.Next(lastState);
  }
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
