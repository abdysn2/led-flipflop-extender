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
