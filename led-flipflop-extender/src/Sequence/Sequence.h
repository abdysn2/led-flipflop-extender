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

// Note(Abdallah): for the constructors to compile correctly, the functions implementation must
// be in header file included in the program, and to not add more files, the implementation was
// put in the same header file it as defined at.

///////////////////// SRC //////////////////////////////

//////////////////// StaticSequence ////////////////////

template <int ArraySize>
struct StaticSequence : Sequence<ArraySize> {
    FlipFlopsStates<ArraySize>* sequence;
    int sequenceLength;
    int statesCurrentIndex;

    StaticSequence(FlipFlopsStates<ArraySize> staticStates[], int _sequenceLength);

    FlipFlopsStates<ArraySize> GetState()override;

    void Next() override;

    void Next(int lastState) override;
};

template <int ArraySize>
StaticSequence<ArraySize>::StaticSequence(FlipFlopsStates<ArraySize> staticStates[], int _sequenceLength) {
    this->sequence = staticStates;
    this->sequenceLength = _sequenceLength;
    this->statesCurrentIndex = -1;
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

//////////////////// End of StaticSequence /////////////

//////////////////// RepetitiveSequence ////////////////////

template <int ArraySize>
struct RepetitiveSequence : Sequence<ArraySize> {
    FlipFlopsStates<ArraySize> currentState;
    int* sequence;
    int* sequenceDelays;

    int currentFlipFlopIndex;
    int currentSequenceIndex;
    int sequenceLength;

    RepetitiveSequence(int _sequence[], int _sequenceLength, int _delays[]);

    FlipFlopsStates<ArraySize> GetState()override;

    void Next() override;

    void Next(int lastState) override;
};

template <int ArraySize>
RepetitiveSequence<ArraySize>::RepetitiveSequence(int _sequence[], int _sequenceLength, int _delays[]) {
    this->sequence = _sequence;
    this->sequenceLength = _sequenceLength;
    this->sequenceDelays = _delays;
    this->currentFlipFlopIndex = 0;
    this->currentSequenceIndex = -1;
    this->statesNextEventTime = 0;

    this->currentState.ledsStates[currentFlipFlopIndex] = sequence[0];
    this->currentState.period = sequenceDelays[0];
}

template <int ArraySize>
FlipFlopsStates<ArraySize> RepetitiveSequence<ArraySize>::GetState() {
    return currentState;
}

template <int ArraySize>
void RepetitiveSequence<ArraySize>::Next() {
    Next(ArraySize - 1);
}

template <int ArraySize>
void RepetitiveSequence<ArraySize>::Next(int lastState) {
    if (lastState < 0 || lastState >= ArraySize) {
        lastState = ArraySize - 1;
    }

    currentSequenceIndex++;
    if (currentSequenceIndex >= sequenceLength) {
        currentState.ledsStates[currentFlipFlopIndex] = 0;
        currentSequenceIndex = 0;
        currentFlipFlopIndex++;
        if (currentFlipFlopIndex > lastState)
            currentFlipFlopIndex = 0;
    }

    currentState.ledsStates[currentFlipFlopIndex] = sequence[currentSequenceIndex];
    currentState.period = sequenceDelays[currentSequenceIndex];
}

//////////////////// RepetitiveSequence ////////////////////

#endif