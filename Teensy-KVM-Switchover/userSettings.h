#ifndef USERSETTINGS_H_SEEN
#define USERSETTINGS_H_SEEN

#include "definitions.h"


//Set input pins for switchover button (or connect one to GPO from console, or Tally output on other switchover device)
constexpr int pin_switchover1{ 18 };                //external contact closure button (short to gnd)
constexpr int pin_switchover2{ 19 };                //second switchover input, can be configured below

//Enable Second switchover input
constexpr ContactType switchoverType_2{ CONTACT_CLOSURE };
//Following types are possible:
//DISABLE
//VOLTAGE         - pulled low, requires high to trigger
//VOLTAGE_FLOAT   - floating, requires high to trigger
//CONTACT_CLOSURE - pulled high in off state, short to ground to trigger (same mode as first Switchover Input)
//CONTACT_HIGH    - pulled high in off state, requires rising edge to trigger (i.e triggers on release of button shorted to gnd)
//VOLTAGE_INV     - floating, requires low to trigger

//Set input pins to force to either Main or Backup (both contact closure)
constexpr int pin_switchoverSet1{ 26 };
constexpr int pin_switchoverSet2{ 27 };

//LED Pins (maximum current on Teensy 4.x is 4mA; combined with this being 3.3V don't expect to run Blue or White LEDs with any serious brightness)
constexpr int pin_LED{ 13 };   //13 for internal    //On when on backup, off on main; can be used via an inverter buffer to drive devices that require an always on signal to select main
constexpr int pin_set1LED{ 30 };                    //On when Main selected
constexpr int pin_set2LED{ 31 };                    //On when Backup selected - it's possible to connect a bi-colour LED across these two pins (via series resistor of course)

//Set Trigger Outputs
constexpr int pin_momentaryExternal{ 22 };          //external output
constexpr int pin_momentaryExternal_2{ 23 };        //second external output
constexpr int momentaryTime{ 10 };                  //sets time (in milliseoncds) that this signal is active for when a switchover state gets triggered, also used as time for keystrokes
constexpr ContactType externalType{ CONTACT_CLOSURE };
constexpr ContactType externalType_2{ VOLTAGE };
//Following types are possible:
//VOLTAGE         - low, goes high when triggerd (i.e. ACTIVE_HIGH)
//CONTACT_CLOSURE - floating, goes to ground when triggered (useful when connecting to devices with unknown pullup resistance), same as first output
//CONTACT_HIGH    - floating, goes positive when triggerd
//VOLTAGE_INV     - high in off state, goes low when triggerd (i.e. ACTIVE_LOW)


//Set KVM Type - current options: ADDER or STARTECH; can be left blank if no kvm switching required
constexpr int kvmType{ STARTECH };
constexpr int switchoverInterval{ 10 };             //Time of and between Keystrokes sent to KVMs; 10ms is the default and seems to work happily.


constexpr bool recallPowerUpState{ ENABLE };        //If enabled switchover will set KVM to state at last power up; if disabled it will reset to Main whenever turned on; useful in case of powerloss on USB
constexpr bool powerUpTriggerExternal{ DISABLE };   //If enabled momentary external outputs get triggered on powerup

constexpr uint16_t debounceTime{ 10 };              //Default Debounce Time of 10 for all switching
constexpr uint16_t debounceTwo{ 10 };               //seperate debounce time for second switchover Input



                ///MIDI Switchover Settings


constexpr bool midiSwitchoverEnable{ ENABLE };     //Enables switchover toggle by MIDI (only from input port 3)
constexpr bool midiSwitchoverSet{ ENABLE };         //Enables switchover set by MIDI (only from input port 3)
constexpr bool midiSwitchoverFilter{ DISABLE };     //If Enabled messages used to trigger switchover will not get passed along through routing matrix below

constexpr int midiSwitchoverChannel{ 16 };          //Input MIDI Channel
constexpr int midiSwitchoverMessage{ 1 };           //Program Change Message to toggle switchover
constexpr int midiSwitchoverMain{ 2 };              //Program Change Message to set to Main Machine
constexpr int midiSwitchoverBackup{ 3 };            //Program Change Message to set to Backup Machine


constexpr bool midiSwitch_Echo{ DISABLE };          //If enabled switched MIDI inputs 1 & 2 will send to outputs 1 & 2
constexpr bool midiSwitch_3{ ENABLE };              //If enabled switched MIDI inputs send to output 3
constexpr bool midiSwitch_4{ ENABLE };              //If enabled switched MIDI inputs send to output 4
constexpr bool midiSwitch_5{ ENABLE };              //If enabled switched MIDI inputs send to output 5
constexpr bool midiRoute_3_12{ ENABLE };            //If enabled routes MIDI input 3 to outputs 1 & 2
constexpr bool midiRoute_3_3{ ENABLE };             //If enabled routes MIDI input 3 to output 3
constexpr bool midiRoute_3_4{ ENABLE };             //If enabled routes MIDI input 3 to output 4
constexpr bool midiRoute_3_5{ DISABLE };            //If enabled routes MIDI input 3 to output 5
constexpr bool midiRoute_4_12{ ENABLE };            //If enabled routes MIDI input 4 to outputs 1 & 2
constexpr bool midiRoute_4_3{ ENABLE };             //If enabled routes MIDI input 4 to output 3
constexpr bool midiRoute_4_4{ ENABLE };             //If enabled routes MIDI input 4 to output 4
constexpr bool midiRoute_4_5{ DISABLE };            //If enabled routes MIDI input 4 to output 5
constexpr bool midiRoute_5_12{ ENABLE };            //If enabled routes MIDI input 5 to outputs 1 & 2
constexpr bool midiRoute_5_3{ ENABLE };             //If enabled routes MIDI input 5 to output 3
constexpr bool midiRoute_5_4{ ENABLE };             //If enabled routes MIDI input 5 to output 4
constexpr bool midiRoute_5_5{ DISABLE };            //If enabled routes MIDI input 5 to output 5
                                                    //MIDI Outputs 6 - 8 (8 only on Teensy 4.1) are by default set to a fixed routing from the switchover and Input 3 (as they were a late addition)
                                                    //MIDI Inputs 6 - 8 are disabled by default (and untested, however should probably be fine)


constexpr SysExSize maximumSysExMessageBytes{ NORMAL };
//Maximum number of Bytes for SysExMessages before it gets truncated; Beware that MIDI Show Control is just SysEx and tends to be more than 8 bytes
//    TINY            = 8,
//    SMALL           = 32,
//    NORMAL          = 128,
//    MEDIUM          = 256,
//    HIGHER          = 512,
//    MAXIMUM         = 1024


                //MIDI Button Settings

constexpr bool midiButtonsAllOutputs{ DISABLE };    //Enable to send Messages from Button Inputs to all 5 MIDI outs; if disabled they will only be sent to output 1 & 2
constexpr MessageType midiButtonsType{ PGM_CHANGE };       //Choice between PGM_CHANGE or NOTE_MSG for Button Inputs

constexpr int midiButtonsChannel{ 1 };              //Channel for Midi Buttons
constexpr int midiButton1_msg{ 1 };                 //Program Change Message (or Note On Number) for Midi Buttons
constexpr int midiButton2_msg{ 2 };
constexpr int midiButton3_msg{ 3 };
constexpr int midiButton4_msg{ 4 };
constexpr int midiButton5_msg{ 5 };
constexpr int midiButton6_msg{ 6 };
constexpr int midiButton7_msg{ 7 };
constexpr int midiButton8_msg{ 8 };
constexpr int midiButtonsVelocity{ 127 };           //Velocity for Note On messages when using Note instead of program change events (must be > 0)

constexpr uint16_t debounceButtons{ 10 };           //Debounce Time for Butons

constexpr int pin_midiButton1{ 2 };
constexpr int pin_midiButton2{ 3 };
constexpr int pin_midiButton3{ 4 };
constexpr int pin_midiButton4{ 5 };
constexpr int pin_midiButton5{ 9 };
constexpr int pin_midiButton6{ 10 };
constexpr int pin_midiButton7{ 11 };
constexpr int pin_midiButton8{ 12 };



#endif