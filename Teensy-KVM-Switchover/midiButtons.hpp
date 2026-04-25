#ifndef MIDIBUTTONS_HPP_SEEN
#define MIDIBUTTONS_HPP_SEEN

#include "midiButtons.h"

void midiButtonsSetup(){
    midiButton1.attach( pin_midiButton1, INPUT_PULLUP);
    midiButton1.interval( debounceButtons );
    midiButton1.setPressedState( LOW );

    midiButton2.attach( pin_midiButton2, INPUT_PULLUP);
    midiButton2.interval( debounceButtons );
    midiButton2.setPressedState( LOW );

    midiButton3.attach( pin_midiButton3, INPUT_PULLUP);
    midiButton3.interval( debounceButtons );
    midiButton3.setPressedState( LOW );

    midiButton4.attach( pin_midiButton4, INPUT_PULLUP);
    midiButton4.interval( debounceButtons );
    midiButton4.setPressedState( LOW );

    midiButton5.attach( pin_midiButton5, INPUT_PULLUP);
    midiButton5.interval( debounceButtons );
    midiButton5.setPressedState( LOW );

    midiButton6.attach( pin_midiButton6, INPUT_PULLUP);
    midiButton6.interval( debounceButtons );
    midiButton6.setPressedState( LOW );

    midiButton7.attach( pin_midiButton7, INPUT_PULLUP);
    midiButton7.interval( debounceButtons );
    midiButton7.setPressedState( LOW );

    midiButton8.attach( pin_midiButton8, INPUT_PULLUP);
    midiButton8.interval( debounceButtons );
    midiButton8.setPressedState( LOW );
}

void midiButtons(){
  midiButton1.update();
  midiButton2.update();
  midiButton3.update();
  midiButton4.update();
  midiButton5.update();
  midiButton6.update();
  midiButton7.update();
  midiButton8.update();

  switch (midiButtonsType){
    case NOTE_MSG:
      if (midiButton1.pressed()){
        midiButtonsNoteOn(midiButton1_msg);
      }
      if (midiButton2.pressed()){
        midiButtonsNoteOn(midiButton2_msg);
      }
      if (midiButton3.pressed()){
        midiButtonsNoteOn(midiButton3_msg);
      }
      if (midiButton4.pressed()){
        midiButtonsNoteOn(midiButton4_msg);
      }
      if (midiButton5.pressed()){
        midiButtonsNoteOn(midiButton5_msg);
      }
      if (midiButton6.pressed()){
        midiButtonsNoteOn(midiButton6_msg);
      }
      if (midiButton7.pressed()){
        midiButtonsNoteOn(midiButton7_msg);
      }
      if (midiButton8.pressed()){
        midiButtonsNoteOn(midiButton8_msg);
      }

      if (midiButton1.released()){
        midiButtonsNoteOff(midiButton1_msg);
      }
      if (midiButton2.released()){
        midiButtonsNoteOff(midiButton2_msg);
      }
      if (midiButton3.released()){
        midiButtonsNoteOff(midiButton3_msg);
      }
      if (midiButton4.released()){
        midiButtonsNoteOff(midiButton4_msg);
      }
      if (midiButton5.released()){
        midiButtonsNoteOff(midiButton5_msg);
      }
      if (midiButton6.released()){
        midiButtonsNoteOff(midiButton6_msg);
      }
      if (midiButton7.released()){
        midiButtonsNoteOff(midiButton7_msg);
      }
      if (midiButton8.released()){
        midiButtonsNoteOff(midiButton8_msg);
      }
      break;
    case PGM_CHANGE:
      if (midiButton1.pressed()){
        midiButtonsPgmChange(midiButton1_msg);
      }
      if (midiButton2.pressed()){
        midiButtonsPgmChange(midiButton2_msg);
      }
      if (midiButton3.pressed()){
        midiButtonsPgmChange(midiButton3_msg);
      }
      if (midiButton4.pressed()){
        midiButtonsPgmChange(midiButton4_msg);
      }
      if (midiButton5.pressed()){
        midiButtonsPgmChange(midiButton5_msg);
      }
      if (midiButton6.pressed()){
        midiButtonsPgmChange(midiButton6_msg);
      }
      if (midiButton7.pressed()){
        midiButtonsPgmChange(midiButton7_msg);
      }
      if (midiButton8.pressed()){
        midiButtonsPgmChange(midiButton8_msg);
      }
      break;
  }
}

void midiButtonsPgmChange(int msg, int channel, bool route[numberOfInputs][numberOfOutputs]){
    if (route[9][1]) midi_1.sendProgramChange(msg, channel);
    if (route[9][2]) midi_2.sendProgramChange(msg, channel);
    if (route[9][3]) midi_3.sendProgramChange(msg, channel);
    if (route[9][4]) midi_4.sendProgramChange(msg, channel);
    if (route[9][5]) midi_5.sendProgramChange(msg, channel);
    if (route[9][6]) midi_6.sendProgramChange(msg, channel);
    if (route[9][7]) midi_7.sendProgramChange(msg, channel);
    #ifdef ARDUINO_TEENSY41
    if (route[9][8]) midi_8.sendProgramChange(msg, channel);
    #endif
}

void midiButtonsNoteOn(int msg, int vel, int channel, bool route[numberOfInputs][numberOfOutputs]){
    if (route[9][1]) midi_1.sendNoteOn(msg, vel, channel);
    if (route[9][2]) midi_2.sendNoteOn(msg, vel, channel);
    if (route[9][3]) midi_3.sendNoteOn(msg, vel, channel);
    if (route[9][4]) midi_4.sendNoteOn(msg, vel, channel);
    if (route[9][5]) midi_5.sendNoteOn(msg, vel, channel);
    if (route[9][5]) midi_6.sendNoteOn(msg, vel, channel);
    if (route[9][6]) midi_7.sendNoteOn(msg, vel, channel);
    #ifdef ARDUINO_TEENSY41
    if (route[9][6]) midi_8.sendNoteOn(msg, vel, channel);
    #endif
}

void midiButtonsNoteOff(int msg, int vel, int channel, bool route[numberOfInputs][numberOfOutputs]){
    if (route[9][1]) midi_1.sendNoteOff(msg, vel, channel);
    if (route[9][2]) midi_2.sendNoteOff(msg, vel, channel);
    if (route[9][3]) midi_3.sendNoteOff(msg, vel, channel);
    if (route[9][4]) midi_4.sendNoteOff(msg, vel, channel);
    if (route[9][5]) midi_5.sendNoteOff(msg, vel, channel);
    if (route[9][6]) midi_6.sendNoteOff(msg, vel, channel);
    if (route[9][7]) midi_7.sendNoteOff(msg, vel, channel);
    #ifdef ARDUINO_TEENSY41
    if (route[9][8]) midi_8.sendNoteOff(msg, vel, channel);
    #endif
}

#endif