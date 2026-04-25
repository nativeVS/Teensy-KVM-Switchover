#ifndef SETUP_H_SEEN
#define SETUP_H_SEEN

#include "definitions.h"
#include "userSettings.h"

///MIDI Setttings Override

struct MidiSettings : public midi::DefaultSettings
{
    static const unsigned SysExMaxSize = maximumSysExMessageBytes; // Accept SysEx messages up to 1024 bytes long.
    //static const bool UseRunningStatus = true;  //some hardware might not like it
};

///DIN MIDI

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial1, midi_1, MidiSettings);  //Main Switched Input
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, midi_2, MidiSettings);  //Backup Switched Input
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial3, midi_3, MidiSettings);
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial4, midi_4, MidiSettings);
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial5, midi_5, MidiSettings);
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial6, midi_6, MidiSettings);
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial7, midi_7, MidiSettings);
#ifdef ARDUINO_TEENSY41
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial8, midi_8, MidiSettings);
#endif

///Switchover Inputs

Bounce2::Button switchoverInput1 = Bounce2::Button();
Bounce2::Button switchoverInput2 = Bounce2::Button();
Bounce2::Button switchoverSet1 = Bounce2::Button();
Bounce2::Button switchoverSet2 = Bounce2::Button();


///MIDI Butttons

Bounce2::Button midiButton1 = Bounce2::Button();
Bounce2::Button midiButton2 = Bounce2::Button();
Bounce2::Button midiButton3 = Bounce2::Button();
Bounce2::Button midiButton4 = Bounce2::Button();
Bounce2::Button midiButton5 = Bounce2::Button();
Bounce2::Button midiButton6 = Bounce2::Button();
Bounce2::Button midiButton7 = Bounce2::Button();
Bounce2::Button midiButton8 = Bounce2::Button();


///Interrupt Handling

IntervalTimer switchoverTimer;            //triggered by switchover state

void interruptSwitchover();



#endif