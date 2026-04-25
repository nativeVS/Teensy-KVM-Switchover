#ifndef MIDIROUTER_H_SEEN
#define MIDIROUTER_H_SEEN


constexpr int numberOfInputs{ 10 };                                 // should be 1 higher than actual number to allow for 0
constexpr int numberOfOutputs{ 10 };                                // should be 1 higher than actual number to allow for 0
bool midiRoute[numberOfInputs][numberOfOutputs] = { 0 };            //[Source][Dest]: 0 Switch, 1 - 5 Din, 6 - 8 rtp 1 - 3, 9 Buttons



void setupMidiRouting();
void midiRouter(midi::MidiType type, byte channel, byte data1, byte data2, int source);
const byte* sysExSource(int source);
void midiRouting();

#endif
