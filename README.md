# Teensy-KVM-Switchover
A simple way of swiching between two KVM sources on receipt of a contact closure input. Uses a Teensy to send key commands via USB to a connected KVM switcher / extender / matrix that allows use of hotkeys. Currently supports standard Adder and Startech hotkeys.

## Overview
This project started out by the lack of switchover solution I had on a show I was operating last year. After re-visiting some work I did for the NT, where we used this method to remotely switch inputs on XDIPS, I decided to add the default commands for the Startech KVM that was used on that job and a way to interface it with the Yamaha DM7 GPIO to switch A & B inputs on an external button press, as well as sending a console button out via GPIO to have it available as a user defined key.

Subsequently I have reworked it entirely with a lot of feature creep and have decided to release this simple solution before I get round to finish the more fully fleshed out version (including MIDI and Button Controller inputs; maybe even rtpMIDI and OSC if I decide to delve into the Teensy 4.1).
See updates below for additions and changes.


### Links
[Teensy Loader](https://www.pjrc.com/teensy/loader.html)
Allows you to quickly upload the following hex files, compiled with all the default settings and pinouts as can be found in the source sketch (or below).

[Teensy 4.0 Adder](https://github.com/nativeVS/Teensy-KVM-Switchover/releases/download/rel1/Teensy4.0_Adder.hex)
Use this hex file if you are using a Teensy 4.0 to connect to any Adder KVM switch that supports hot keys (such as XDIP) (```Ctrl``` + ```Alt``` + ```{num}```)

[Teensy 4.1 Adder](https://github.com/nativeVS/Teensy-KVM-Switchover/releases/download/rel1/Teensy4.1_Adder.hex)
As above but for Teensy 4.1

[Teensy 4.0 Startech](https://github.com/nativeVS/Teensy-KVM-Switchover/releases/download/rel1/Teensy4.0_Startech.hex)
Use this hex file if you are using a Teensy 4.0 to connect to any Startech KVM switch that supports hot keys (```Ctrl``` ```Ctrl``` ```{num}```)

[Teensy 4.1 Startech](https://github.com/nativeVS/Teensy-KVM-Switchover/releases/download/rel1/Teensy4.1_Startech.hex)
As above but for Teensy 4.1

## Quick Getting Started
Included in repo are default hex files for Teensy 4.0 with Startech and Adder commands (respectively), so that if you just want a quick solution that works almost out of the box.
Just download the required file and the Teensy loader (see links above), drag and drop the file onto the Teensy loader, connect your teensy and press the white button.

## Updates

### Version 1.1

#### Additions
* MIDI Switching and Routing functionality (up to 5 inputs and outputs with Teensy 4.0, up to 8 with Teensy 4.1)
* MIDI Button Controller with up to 8 buttons; choice of Note or Program Change Messages
* Remote control of Switchover state via MIDI Program Changes

#### Changes
* Complete reformatting of source code to make future additions easier
* Rewrite of KVM Keyboard triggers to be interrupt based (using interval timer)
* Default Pin assignment changed to fit added features more conveniently (see [notes](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/Teensy-KVM-Switchover/notes.md))

## todo
Need to compile a list of which Startech KVMs work.

Also need to do a speed check, whether key strokes are always registered by the Startechs in time (it worked for me, but I didn't check it extensively back in time).
Triple Check behaviour with DM7.

Check behaviour with available Audio switchover devices.

Write better documentation with everything centralised in one spot - for now use this, the [notes](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/Teensy-KVM-Switchover/notes.md) file, and the [userSettings h file](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/Teensy-KVM-Switchover/userSettings.h).

## Example Applications
This assumes adhearing to the default pinout in userSettings.h file

When connecting to external devices, beware this will share the GND between those and the connected KVM. If there are grounding problems, or other devices are not properly isolated, it might be necessary to isolate this device properly using optocouplers (or relays). It might be beneficial to include a smallish (<<1k) series resistor when connecting straight to TTL or open collector GPIOs. I've never had any issues, however in most cases the other devices tend to be more forgiving than the poor little Teensy.
Just make sure you do not connect to anything above 3.3V that could source (or sink) a reasonable current.

### Simple Remote
For a nice simple remote button one could use a Red/Green bi-colour LED button. Wire the button to pin 18 and Gnd, wire one side of the LED to pin 30, the other through series resistor (around 390R) to pin 31.

### Button Controller
Wire pins 2 through 6 to buttons 1 to 4 and pins 9 through 12 to buttons 5 to 8; connect the other side of all the buttons together and to a GND terminal on the Teensy.

### MIDI Connections
See [this handy page (with diagram)](https://www.pjrc.com/teensy/td_libs_MIDI.html) for wiring. Also this [document from the MMA](https://mitxela.com/other/ca33.pdf) regarding the MIDI electrical specifications for 3.3V. It sems 6N138 are generally the industry preferred optocouplers for MIDI with 3.3V and what I tested with.

### DM7 Notes
#### GPI Input
Set desired GPI pin to Unlatch, choose the action (i.e. Input A/B of first channel - this does require having all the inputs channel you need to swap linked of course) and select Active Low (see image below for example of GPI In 1 and linked channels starting with CH37).
![alt text](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/images/dm7_0.JPG)
![alt text](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/images/dm7_1.JPG)
#### GPI Output
Set desired User Defined Key to: GPI Out - {GPI Port Number} - Unlatch.
![alt text](https://github.com/nativeVS/Teensy-KVM-Switchover/blob/main/images/dm7_2.JPG)


## Build Notes

Using the Arduino IDE with Teensyduino installed no external libraries should be required as the Midi & Bounce2 libraries are included with the Teensyduino install.
Set the USB Type to "Keyboard".

In the current official release of the Arduino MIDI Library (5.0.1) System Common & Tune Request messages do not get passed along with the default send function. See [issue 371](https://github.com/FortySevenEffects/arduino_midi_library/issues/371) for a quick and simple patch to the MIDI.hpp file in the MIDI Library.


nativeVS - 2026
