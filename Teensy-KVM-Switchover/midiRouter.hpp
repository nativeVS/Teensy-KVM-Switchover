#ifndef MIDIROUTER_HPP_SEEN
#define MIDIROUTER_HPP_SEEN

#define OUTDATED

#include "midiRouter.h"

#ifndef OUTDATED

MidiRouterNew newRouter;

#endif

#include <array>
#include <algorithm>
#include <iterator>

/*
The setupMidiRouting() function is called in the setup() function

It initialises MIDI ports and populates the routing matrix with the (compile time) settings. Routing Matrix also gets used by Buttons.
Should just required switching to EEPROM reads to make it recallable.
*/

void setupMidiRouting(){

  midi_1.begin(MIDI_CHANNEL_OMNI);
  midi_2.begin(MIDI_CHANNEL_OMNI);
  midi_3.begin(MIDI_CHANNEL_OMNI);
  midi_4.begin(MIDI_CHANNEL_OMNI);
  midi_5.begin(MIDI_CHANNEL_OMNI);
  midi_6.begin(MIDI_CHANNEL_OMNI);
  midi_7.begin(MIDI_CHANNEL_OMNI);
  #ifdef ARDUINO_TEENSY41
  midi_8.begin(MIDI_CHANNEL_OMNI);
  #endif

  midi_1.turnThruOff();
  midi_2.turnThruOff();
  midi_3.turnThruOff();
  midi_4.turnThruOff();
  midi_5.turnThruOff();
  midi_6.turnThruOff();
  midi_7.turnThruOff();
  #ifdef ARDUINO_TEENSY41
  midi_8.turnThruOff();
  #endif
  

  midiRoute[0][1] = midiSwitch_Echo;
  midiRoute[0][2] = midiSwitch_Echo;
  midiRoute[0][3] = midiSwitch_3;
  midiRoute[0][4] = midiSwitch_4;
  midiRoute[0][5] = midiSwitch_5;
  midiRoute[1][1] = midiSwitch_Echo;
  midiRoute[1][2] = midiSwitch_Echo;
  midiRoute[1][3] = midiSwitch_3;
  midiRoute[1][4] = midiSwitch_4;
  midiRoute[1][5] = midiSwitch_5;
  midiRoute[2][1] = midiSwitch_Echo;
  midiRoute[2][2] = midiSwitch_Echo;
  midiRoute[2][3] = midiSwitch_3;
  midiRoute[2][4] = midiSwitch_4;
  midiRoute[2][5] = midiSwitch_5;
  midiRoute[3][1] = midiRoute_3_12;
  midiRoute[3][2] = midiRoute_3_12;
  midiRoute[3][3] = midiRoute_3_3;
  midiRoute[3][4] = midiRoute_3_4;
  midiRoute[3][5] = midiRoute_3_5;
  midiRoute[4][1] = midiRoute_4_12;
  midiRoute[4][2] = midiRoute_4_12;
  midiRoute[4][3] = midiRoute_4_3;
  midiRoute[4][4] = midiRoute_4_4;
  midiRoute[4][5] = midiRoute_4_5;
  midiRoute[5][1] = midiRoute_5_12;
  midiRoute[5][2] = midiRoute_5_12;
  midiRoute[5][3] = midiRoute_5_3;
  midiRoute[5][4] = midiRoute_5_4;
  midiRoute[5][5] = midiRoute_5_5;
  midiRoute[9][1] = 1;
  midiRoute[9][2] = 1;
  for (int i = 3; i < 9; i++){
    midiRoute[9][i] = midiButtonsAllOutputs;
  }
  for (int i = 6; i < 9; i++){
    midiRoute[1][i] = 1;
    midiRoute[2][i] = 1;
    midiRoute[3][i] = 1;
  }
}


void midiRouter(midi::MidiType type, byte channel, byte data1, byte data2, int source){
  if (type != midi::SystemExclusive){
    if (midiRoute[source][1]) midi_1.send(type, data1, data2, channel);
    if (midiRoute[source][2]) midi_2.send(type, data1, data2, channel);
    if (midiRoute[source][3]) midi_3.send(type, data1, data2, channel);
    if (midiRoute[source][4]) midi_4.send(type, data1, data2, channel);
    if (midiRoute[source][5]) midi_5.send(type, data1, data2, channel);
    if (midiRoute[source][6]) midi_6.send(type, data1, data2, channel);
    if (midiRoute[source][7]) midi_7.send(type, data1, data2, channel);
    #ifdef ARDUINO_TEENSY41
    if (midiRoute[source][8]) midi_8.send(type, data1, data2, channel);
    #endif
  }
  else{
    unsigned int SysExLength = data1 + data2 * 256;
    if (midiRoute[source][1]) midi_1.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][2]) midi_2.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][3]) midi_3.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][4]) midi_4.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][5]) midi_5.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][6]) midi_6.sendSysEx(SysExLength, sysExSource(source), true);
    if (midiRoute[source][7]) midi_7.sendSysEx(SysExLength, sysExSource(source), true);
    #ifdef ARDUINO_TEENSY41
    if (midiRoute[source][8]) midi_8.sendSysEx(SysExLength, sysExSource(source), true);
    #endif
  }
}

const byte* sysExSource(int source){
  switch (source){
    case 0:
      switch (currentState){
        case MAIN:
          return midi_1.getSysExArray();
        case BACKUP:
          return midi_2.getSysExArray();
      }
    case 1:
      return midi_1.getSysExArray();
    case 2:
      return midi_2.getSysExArray();
    case 3:
      return midi_3.getSysExArray();
    case 4:
      return midi_4.getSysExArray();
    case 5:
      return midi_5.getSysExArray();
    case 6:
      return midi_6.getSysExArray();
    case 7:
      return midi_7.getSysExArray();
    #ifdef ARDUINO_TEENSY41
    case 8:
      return midi_8.getSysExArray();
    #endif
    default:
      return {};
  }
}

/*
The midiRouting() function is called in the main loop().
It listens to all incoming Midi, reads (and clears the buffers) it and dispatches is with the help of the midiRouter() function above.
*/

void midiRouting(){
  if (midi_1.read()){
    if (currentState == MAIN) midiRouter(midi_1.getType(), midi_1.getChannel(), midi_1.getData1(), midi_1.getData2(), 1);
  }
  if (midi_2.read()){
    if (currentState == BACKUP) midiRouter(midi_2.getType(), midi_2.getChannel(), midi_2.getData1(), midi_2.getData2(), 2);
  }
  if (midi_3.read()){
    midi::MidiType type = midi_3.getType();
    byte channel = midi_3.getChannel();
    byte data1 = midi_3.getData1();
    bool midiSwitchoverMessageFilter{ 0 };
    if (midiSwitchoverEnable){
      if ((type == midi::ProgramChange) && (channel == midiSwitchoverChannel) && (data1 == midiSwitchoverMessage)){
        switchover();
        midiSwitchoverMessageFilter = 1;
      }
    }
    if (midiSwitchoverSet){
      if ((type == midi::ProgramChange) && (channel == midiSwitchoverChannel)){
        switch (data1){
          case midiSwitchoverMain:
            switchoverSetMain();
            midiSwitchoverMessageFilter = 1;
            break;
          case midiSwitchoverBackup:
            switchoverSetBackup();
            midiSwitchoverMessageFilter = 1;
            break;
        }
      }
    }
    if (!midiSwitchoverMessageFilter) midiRouter(type, channel, data1, midi_3.getData2(), 3);
  }
  if (midi_4.read()) midiRouter(midi_4.getType(), midi_4.getChannel(), midi_4.getData1(), midi_4.getData2(), 4);
  if (midi_5.read()) midiRouter(midi_5.getType(), midi_5.getChannel(), midi_5.getData1(), midi_5.getData2(), 5);
  //if (midi_6.read()) midiRouter(midi_6.getType(), midi_6.getChannel(), midi_6.getData1(), midi_6.getData2(), 6);
  //if (midi_7.read()) midiRouter(midi_7.getType(), midi_7.getChannel(), midi_7.getData1(), midi_7.getData2(), 7);
  #ifdef ARDUINO_TEENSY41
  //if (midi_8.read()) midiRouter(midi_8.getType(), midi_8.getChannel(), midi_8.getData1(), midi_8.getData2(), 8);
  #endif
}

#endif
