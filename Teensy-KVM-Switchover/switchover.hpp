#ifndef SWITCHOVER_HPP_SEEN
#define SWITCHOVER_HPP_SEEN

#include "switchover.h"

void hardwarePinSetup(){
  pinMode(pin_LED, OUTPUT);
  pinMode(pin_set1LED, OUTPUT);
  pinMode(pin_set2LED, OUTPUT);

  switch (switchoverType_2){
    case CONTACT_CLOSURE:
      enableSwitchover2 = ENABLE;
      switchover2type = INPUT_PULLUP;
      switchover2pressedState = LOW;
      break;
    case CONTACT_HIGH:
      enableSwitchover2 = ENABLE;
      switchover2type = INPUT_PULLUP;
      switchover2pressedState = HIGH;
      break;
    case VOLTAGE_FLOAT:
      enableSwitchover2 = ENABLE;
      switchover2type = INPUT;
      switchover2pressedState = HIGH;
      break;
    case VOLTAGE_INV:
      enableSwitchover2 = ENABLE;
      switchover2type = INPUT;
      switchover2pressedState = LOW;
      break;
    case VOLTAGE:
      enableSwitchover2 = ENABLE;
      switchover2type = INPUT_PULLDOWN;
      switchover2pressedState = HIGH;
      break;
    default:
      enableSwitchover2 = DISABLE;
  }

  switch (externalType){
    case VOLTAGE:
      pinMode(pin_momentaryExternal, OUTPUT);
      break;
    case CONTACT_CLOSURE:
      pinMode(pin_momentaryExternal, INPUT_DISABLE);
      break;
    case CONTACT_HIGH:
      pinMode(pin_momentaryExternal, INPUT_DISABLE);
      break;
    case VOLTAGE_INV:
      pinMode(pin_momentaryExternal, OUTPUT);
      digitalWrite(pin_momentaryExternal, 1);
      break;
    default:
      pinMode(pin_momentaryExternal, INPUT_DISABLE);
  }

  switch (externalType_2){
    case VOLTAGE:
      pinMode(pin_momentaryExternal_2, OUTPUT);
      break;
    case CONTACT_CLOSURE:
      pinMode(pin_momentaryExternal_2, INPUT_DISABLE);
      break;
    case CONTACT_HIGH:
      pinMode(pin_momentaryExternal_2, INPUT_DISABLE);
      break;
    case VOLTAGE_INV:
      pinMode(pin_momentaryExternal_2, OUTPUT);
      digitalWrite(pin_momentaryExternal_2, 1);
      break;
    default:
      pinMode(pin_momentaryExternal, INPUT_DISABLE);
  }

  switchoverInput1.attach( pin_switchover1, INPUT_PULLUP);
  switchoverInput1.interval( debounceTime );
  switchoverInput1.setPressedState( LOW );

  if (enableSwitchover2){
    switchoverInput2.attach( pin_switchover2, switchover2type);
    switchoverInput2.interval( debounceTwo );
    switchoverInput2.setPressedState( switchover2pressedState );
  }

  switchoverSet1.attach( pin_switchoverSet1, INPUT_PULLUP);
  switchoverSet1.interval( debounceTime );
  switchoverSet1.setPressedState( LOW );

  switchoverSet2.attach( pin_switchoverSet2, INPUT_PULLUP);
  switchoverSet2.interval( debounceTime );
  switchoverSet2.setPressedState( LOW );

}

void switchover(){
  if (currentState){
    switchoverSetMain();
  }
  else {
    switchoverSetBackup();
  }
}

void switchoverSetMain(){
  currentState = 0;
  switchoverTimer.begin(interruptSwitchover, switchoverInterval * 1000);
  digitalWrite(pin_LED,0);
  if(recallPowerUpState) EEPROM.write(0,currentState);
  digitalWrite(pin_set1LED, 1);
  digitalWrite(pin_set2LED, 0);
}

void switchoverSetBackup(){
  currentState = 1;
  switchoverTimer.begin(interruptSwitchover, switchoverInterval * 1000);
  digitalWrite(pin_LED,1);
  if(recallPowerUpState) EEPROM.write(0,currentState);
  digitalWrite(pin_set1LED, 0);
  digitalWrite(pin_set2LED, 1);
}


void momentaryOutput_interval1(int pin, int type){
  switch (type){
    case VOLTAGE:
      digitalWrite(pin, 1);
      break;
    case CONTACT_CLOSURE:
      pinMode(pin, OUTPUT);
      digitalWrite(pin, 0);
      break;
    case CONTACT_HIGH:
      pinMode(pin, OUTPUT);
      digitalWrite(pin, 1);
      break;
    case VOLTAGE_INV:
      digitalWrite(pin, 0);
      break;
  }
}
void momentaryOutput_interval2(int pin, int type){
  switch (type){
    case VOLTAGE:
      digitalWrite(pin, 0);
      break;
    case CONTACT_CLOSURE:
      pinMode(pin, INPUT_DISABLE);
      break;
    case CONTACT_HIGH:
      pinMode(pin, INPUT_DISABLE);
      break;
    case VOLTAGE_INV:
      digitalWrite(pin, 1);
      break;
  }
}


int kvmInterrupt(int timerCount){
  if (!currentState){
    switch (timerCount){
      case 0:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(MODIFIERKEY_CTRL);
            break;
          case XDIP:
            Keyboard.press(MODIFIERKEY_CTRL);
            Keyboard.press(MODIFIERKEY_ALT);
            Keyboard.press(KEY_1);
            break;
        }
        return 1;
      case 1:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(MODIFIERKEY_CTRL);
            break;
          case XDIP:
            Keyboard.release(MODIFIERKEY_CTRL);
            Keyboard.release(MODIFIERKEY_ALT);
            Keyboard.release(KEY_1);
            return -1;
        }
        return 2;
      case 2:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(MODIFIERKEY_CTRL);
            break;
        }
        return 3;
      case 3:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(MODIFIERKEY_CTRL);
            break;
        }
        return 4;
      case 4:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(KEY_1);
            break;
        }
        return 5;
      case 5:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(KEY_1);
            return -1;
        }
        return -1;
      default:
        return -1;
    }
  }
  else {
    switch (timerCount){
      case 0:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(MODIFIERKEY_CTRL);
            break;
          case XDIP:
            Keyboard.press(MODIFIERKEY_CTRL);
            Keyboard.press(MODIFIERKEY_ALT);
            Keyboard.press(KEY_2);
            break;
        }
        return 1;
      case 1:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(MODIFIERKEY_CTRL);
            break;
          case XDIP:
            Keyboard.release(MODIFIERKEY_CTRL);
            Keyboard.release(MODIFIERKEY_ALT);
            Keyboard.release(KEY_2);
            return -1;
        }
        return 2;
      case 2:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(MODIFIERKEY_CTRL);
            break;
        }
        return 3;
      case 3:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(MODIFIERKEY_CTRL);
            break;
        }
        return 4;
      case 4:
        switch (kvmType){
          case STARTECH:
            Keyboard.press(KEY_2);
            break;
        }
        return 5;
      case 5:
        switch (kvmType){
          case STARTECH:
            Keyboard.release(KEY_2);
            return -1;
        }
        return -1;
      default:
        return -1;
    }
  }
}

void switchoverLoop(){
  switchoverInput1.update();

  if (switchoverInput1.pressed()){
    switchover();
  }


  if (enableSwitchover2){
    switchoverInput2.update();

    if (switchoverInput2.pressed()){
      switchover();
    }
  }

  switchoverSet1.update();
  if (switchoverSet1.pressed()){
    switchoverSetMain();
  }

  switchoverSet2.update();
  if (switchoverSet2.pressed()){
    switchoverSetBackup();
  }
}

#endif