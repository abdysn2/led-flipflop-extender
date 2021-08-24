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

const int NUMBER_OF_STATES = 4;
int unifiedDelay = 20;
int flipFlopRepetitiveStates[NUMBER_OF_STATES] = {0b00000001, 0b00000100, 0b00010000, 0b01000000};
int flipFlopRepetitiveDelays[NUMBER_OF_STATES] = {unifiedDelay, unifiedDelay, unifiedDelay, unifiedDelay};

RepetitiveSequence<NUMBER_OF_FLIP_FLOP_ICS> sequence2 = RepetitiveSequence<NUMBER_OF_FLIP_FLOP_ICS>(flipFlopRepetitiveStates, NUMBER_OF_STATES, flipFlopRepetitiveDelays);

void StatesUpdate(Sequence<NUMBER_OF_FLIP_FLOP_ICS> &sequence, int lastState = -1);

void setup() {
  // put your setup code here, to run once:
  logSerial.begin(9600);
  FlipFlopInit();
  DecoderInit();
}

void loop() {
  StatesUpdate(sequence1);
  //StatesUpdate(sequence2, 4);
}

void StatesUpdate(Sequence<NUMBER_OF_FLIP_FLOP_ICS> &sequence, int lastState = -1){
  unsigned long currentTime = millis();

  if(currentTime >= sequence.statesNextEventTime){
    sequence.Next(lastState);

    sequence.statesNextEventTime = currentTime + sequence.GetState().period;

    WriteState(sequence.GetState().ledsStates);
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
