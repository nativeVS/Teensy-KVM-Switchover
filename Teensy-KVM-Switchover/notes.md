# Pinouts

## Teensy 4.0 Pins:
     0  - MIDI In 1 (Main Machine)
     1  - MIDI Out 1
     2  - (Button 1 - Go)
     3  - (Button 2 - Stop)
     4  - (Button 3 - Prev)
     5  - (Button 4 - Next)
     6  - 
     7  - MIDI In 2 (Backup Machine)
     8  - MIDI Out 2
     9  - (Button 5)
    10  - (Button 6)
    11  - (Button 7)
    12  - (Button 8)
    13  - LED
    14  - MIDI Out 3
    15  - MIDI In 3 (Switchover Control)
    16  - MIDI In 4
    17  - MIDI Out 4
    18  - (Switchover In 1 - Button)
    19  - (Switchover In 2 - from XDANTE or Console)
    20  - MIDI Out 5
    21  - MIDI In 5
    22  - (Momentary External 1 - Contact Closure)
    23  - (Momentary External 2 - Voltage)
    24  - 
    25  - 
    26  - (Set Main)
    27  - (Set Backup)
    28  - 
    29  - 
    30  - (LED Main)
    31  - (LED Backup)
    32  - 
    33  - 
Default pin assignment is in parantheses; note that MIDI ports are fixed to their corresponding pins and cannot be remapped.

Pins 24-32 are SMT pads below.

MIDI Outputs should be wired with 33R resistor to V+ and 10R resistor to output pin to adhere to MIDI current loop spec.
However 47R for both resistors tends to work with most recievers and keeps the current on Teensy outputs lower.

MIDI Inputs require optocouplers as per MIDI spec. 6N138 with 220R series resistor and parallel reverse diode as per MIDI spec recommended.

***

## Teensy 4.1 Pins:
     0  - MIDI In 1 (Main Machine)
     1  - MIDI Out 1
     2  - (Button 1 - Go)
     3  - (Button 2 - Stop)
     4  - (Button 3 - Prev)
     5  - (Button 4 - Next)
     6  - 
     7  - MIDI In 2 (Backup Machine)
     8  - MIDI Out 2
     9  - (Button 5)
    10  - (Button 6)
    11  - (Button 7)
    12  - (Button 8)
    13  - LED
    14  - MIDI Out 3
    15  - MIDI In 3 (Switchover Control)
    16  - MIDI In 4
    17  - MIDI Out 4
    18  - (Switchover In 1 - Button)
    19  - (Switchover In 2 - from XDANTE or Console)
    20  - MIDI Out 5
    21  - MIDI In 5
    22  - (to Console)
    23  - (to XDANTE)
    24  - 
    25  - 
    26  - (Set Main)
    27  - (Set Backup)
    28  - 
    29  - 
    30  - (LED Main)
    31  - (LED Backup) 
    32  - 
    33  - 
    34  - 
    35  - 
    36  - 
    37  - 
    38  - 
    39  - 
    40  - 
    41  - 
Default pin assignment in parantheses (same as with Teensy 4.0).

Pins 42-52 are SMT pads.


***

## Teensy LC Pins:
     0  - MIDI In 1 (Main Machine)
     1  - MIDI Out 1
     2  - (Button 1 - Go)
     3  - (Button 2 - Stop)
     4  - (Button 3 - Prev)
     5  - (Button 4 - Next) {20mA}
     6  - 
     7  - MIDI In 3
     8  - MIDI Out 3
     9  - MIDI In 2 (Backup Machine)
    10  - MIDI Out 2
    11  - (Button 5)
    12  - (Button 6)
    13  - LED
    14  - (Button 7)
    15  - (Button 8)
    16  -     {20mA}
    17  -     {20mA} {also duplicated as 5V 8mA output port}
    18  - (Switchover In 1 - Button)
    19  - (Switchover In 2 - from XDANTE or Console)
    20  - 
    21  -     {20mA}
    22  - (to Console)
    23  - (to XDANTE)
    24  - 
    25  - 
    26  - 
  Teensy LC only has 3 Serial ports, so no MIDI 4 & 5 possible (this will also require removing some references to MIDI 4 & 5 from the source code or the compiler is going to get irritated).

***

## Autograph XDANTE1 Pinout:

    1 - V+ (5V - can be jumpered to 12V)
    2 - Switchover (3V pullup, switch to GND)
    3 - Switchover 2
    4 - Tally 2
    5 - Switchover 1
    6 - Tally 1
    7 - Tally (GND when active)
    8 - GND

***

## Yamaha Console GPIO Pinout:
      1 - GPO1
      2 - GPO3
      3 - GPO5
      4 - GND
      5 - V+ (5V)
      6 - GPI1
      7 - GPI3
      8 - GPI1
      9 - GPO2
      10- GPO4
      11- GND
      12- GND
      13- V+
      14- GPI2
      15- GPI4
#### Input pins CH 1-5:
TTL level (input voltage 0–5V) with internal 47kΩ pull-up resistor
#### Output pins CH 1-5:
Open collector output (maximum supply voltage 12V, maximum inflowing current/pin75mA)
#### Power supply pins:
Output voltage 5V, maximum output current 300mA

***

# Notes:

#### Setup Notes: (for standard Theatre setup)

Connect MIDI Inputs 1 and 2 to the MIDI Outputs from your Main & Backup Machine (respectively).

Connect MIDI Outputs 1 and 2 to the MIDI Inputs to your Main & Backup Machine (respectively).

Connect MIDI Input 3 to the MIDI Output from your Console

Connect MIDI Output 5 to a Show Control Gateway (as the default route only takes the Switchover out)

#### MIDI Notes:

MIDI Outputs 1 & 2 are always treated the same (unless one overrides the routing matrix in the setup function).

MIDI Inputs 1 & 2 are always connected to switchover inputs for Main and Backup (respectively)

MIDI Input 3 can control the switchover state.

MIDI Inputs 3 - 5 can be freely routed to all outputs; default settings route them to outputs 1 through 4

Maximum possible SysEx buffer is 1024 bytes, which should be plenty for any normal use (i.e. MSC) however might have trouble for uninterrupted SysEx dumps.
(I have been able to dump a full set of Lexicon registers by setting the buffere size to 1024 bytes and setting a 250ms delay after each chunk, however would not recommend doing it; if the buffer has overflown one gets undefined behaviour that normally requires a restart; just don't be silly and send too much data to all 8 outputs at the same time).