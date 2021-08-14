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
