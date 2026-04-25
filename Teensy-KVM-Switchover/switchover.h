#ifndef SWITCHOVER_H_SEEN
#define SWITCHOVER_H_SEEN

#include "setup.h"

bool currentState{ 1 };         //status of switchover

bool enableSwitchover2{ DISABLE };
int switchover2type{ INPUT_PULLUP };
bool switchover2pressedState{ LOW }; 

bool inhibitOutputs{ 0 };



volatile int switchoverTimerCount{ 0 };
bool inhibitSwitchover{ 0 };

void interruptSwitchover();

void hardwarePinSetup();
void switchover();
void momentaryOutput(int, uint16_t, int);
void switchoverSetMain();
void switchoverSetBackup();
void momentaryOutput_interval1(int pin, int type);
void momentaryOutput_interval2(int pin, int type);
int kvmInterrupt(int timerCount);
void switchoverLoop();

#endif
