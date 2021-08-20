#include "Arduino.h"

#ifndef Sequence_h
#define Sequence_h

template <int ArraySize>
struct FlipFlopsStates {
  int period;
  int ledsStates[ArraySize];
};

template <int ArraySize>
struct Sequence {
  unsigned long statesNextEventTime;

  virtual FlipFlopsStates<ArraySize> GetState();
  virtual void Next();
  virtual void Next(int lastState);
};

template <int ArraySize>
struct StaticSequence : Sequence<ArraySize> {
  FlipFlopsStates<ArraySize> *sequence;
  int sequenceLength;
  int statesCurrentIndex;
  
  StaticSequence(FlipFlopsStates<ArraySize> staticStates[], int _sequenceLength);

  FlipFlopsStates<ArraySize> GetState()override;

  void Next() override;

  void Next(int lastState) override;
};


// Note(Abdallah): for the constructors to compile correctly, the functions implementation must
// be in header file included in the program, and to not add more files, the implementation was
// put in the same header file it as defined at.

///////////////////// SRC //////////////////////////////
template <int ArraySize>
StaticSequence<ArraySize>::StaticSequence(FlipFlopsStates<ArraySize> staticStates[], int _sequenceLength) {
    this->sequence = staticStates;
    this->sequenceLength = _sequenceLength;
    this->statesCurrentIndex = 0;
    this->statesNextEventTime = 0;
}

template <int ArraySize>
FlipFlopsStates<ArraySize> StaticSequence<ArraySize>::GetState() {
    return sequence[statesCurrentIndex];
}

template <int ArraySize>
void StaticSequence<ArraySize>::Next() {
    Next(sequenceLength - 1);
}

template <int ArraySize>
void StaticSequence<ArraySize>::Next(int lastState) {
    if (lastState < 0 || lastState >= sequenceLength) {
        lastState = sequenceLength - 1;
    }
    this->statesCurrentIndex++;
    if (statesCurrentIndex > lastState) {
        this->statesCurrentIndex = 0;
    }
}

#endif