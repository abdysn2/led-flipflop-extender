/*
 * A function used to set pins mode in bulk with a single value.
*/
void BulkPinMode(int numberOfPins, int pinsIndexes[], int value){
  for (int i =0; i < numberOfPins; i++){
    logToSerial("Setting pin " + (String)pinsIndexes[i] + " to " + (String)value, 2);
    pinMode(pinsIndexes[i], value);
  }
}

/*
 * A function to write pins states in bulk by providing it with the pins Indexes
 * and their values.
*/
void BulkDigitalWrite(int numberOfPins, int pinsIndexes[], int values[]){
  for (int i =0; i < numberOfPins; i++){
    logToSerial("Writing " + (String)values[i] + " to " + (String)pinsIndexes[i], 2);
    digitalWrite(pinsIndexes[i], values[i]);
  }
}

/*
 * A function to store the bits of a number into an array. e.g. number 3 will become {1, 1} or 
 * {1, 1, 0, 0} depending on the arrayLength field.
*/
void ConvertIntToPinStates(byte number, int arrayLength, int _array[]){
  for(int i=0; i < arrayLength; i++){
    _array[i] = number % 2;
    number /= 2;
  }
}

/*
 * A function to write logs to the serial monitor, it is provided with a debugLevel field which work with
 * the global debugLevel field to determine when to print the message.
*/
void logToSerial(String msg, int _debugLevel)
{
  if (debugLevel >= _debugLevel){
    logSerial.println(msg);
  }
}

/*
 * StatesUpdate(): A helper function to update the leds states based on the
 * Sequence class. The Sequence class must implement Two functions: Next, and
 * GetState. The next function is called to calculate the next state in the states
 * sequence, and the GetState is used to fetch the current state of the sequence.
 * The statesNextEventTime is used to determine whether or not it is time to update
 * the states.
*/
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

/*
 * WriteState(): is used to write states to the flipFlops, it accepts
 * an array of integers, each integer represent a flipFlop IC pin configuration.
 * to calculate the integer, convert it to binary, and the first eight digits are
 * going to be written to the flipFlop
*/

bool WriteState(int *states, int start, int numberOfICs){
  for(int i = start; i < (start + numberOfICs); i++){
    if (!FlipFlopWrite(states[i], i))
      return false;
  }
}
