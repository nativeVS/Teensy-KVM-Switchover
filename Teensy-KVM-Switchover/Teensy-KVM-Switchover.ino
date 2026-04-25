//Version 1.1

#include "definitions.h"
#include "setup.h"

#include "switchover.hpp"
#include "midiRouter.hpp"
#include "midiButtons.hpp"




void setup() {

  hardwarePinSetup();

  setupMidiRouting();

  midiButtonsSetup();
  

  if (recallPowerUpState){
    if (EEPROM.read(0) == (1 || 0)){    //ignores garbage data in EEPROM from previous projects...
      currentState = !(EEPROM.read(0));
    }
  }


  
  digitalWrite(pin_LED,1);
  delay(1000);
  digitalWrite(pin_LED,0);
  delay(10);

  if (!powerUpTriggerExternal) inhibitOutputs = 1;

  switchover();
}



void loop() {
  noInterrupts();
  inhibitSwitchover = !!switchoverTimerCount;
  interrupts();

  switchoverLoop();

  midiRouting();

  midiButtons();


}

void interruptSwitchover(){
  switch (switchoverTimerCount){
    case 0:
      if (!inhibitOutputs){
        momentaryOutput_interval1(pin_momentaryExternal, externalType);
        momentaryOutput_interval1(pin_momentaryExternal_2, externalType_2);
      }
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    case 1:
      if (!inhibitOutputs){
        momentaryOutput_interval2(pin_momentaryExternal, externalType);
        momentaryOutput_interval2(pin_momentaryExternal_2, externalType_2);
      }
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    case 2:
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    case 3:
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    case 4:
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    case 5:
      switchoverTimerCount = kvmInterrupt(switchoverTimerCount);
      break;
    default:
      switchoverTimerCount = 0;
      switchoverTimer.end();
      inhibitOutputs = 0;
      break;
  }

}


