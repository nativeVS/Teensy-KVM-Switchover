#ifndef MIDIBUTTONS_H_SEEN
#define MIDIBUTTONS_H_SEEN

#include "setup.h"
#include "midiRouter.h"

void midiButtonsSetup();
void midiButtons();
void midiButtonsPgmChange(int msg, int channel = midiButtonsChannel, bool route[numberOfInputs][numberOfOutputs] = midiRoute);
void midiButtonsNoteOn(int msg, int vel = midiButtonsVelocity, int channel = midiButtonsChannel, bool route[numberOfInputs][numberOfOutputs] = midiRoute);
void midiButtonsNoteOff(int msg, int vel = midiButtonsVelocity, int channel = midiButtonsChannel, bool route[numberOfInputs][numberOfOutputs] = midiRoute);

#endif