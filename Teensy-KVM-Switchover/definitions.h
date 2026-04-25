#ifndef DEFINITIONS_H_SEEN
#define DEFINITIONS_H_SEEN

#include <Bounce2.h>
#include <EEPROM.h>
#include <MIDI.h>


#define ENABLE          1
#define ENABLED         1
#define DISABLE         0
#define DISABLED        0
#define STARTECH        1
#define XDIP            2
#define ADDER           2
#define MAIN            0
#define BACKUP          1


enum ContactType {
    VOLTAGE         = 0,
    CONTACT_CLOSURE = 1,
    CONTACT_HIGH    = 2,
    VOLTAGE_INV     = 3,
    VOLTAGE_FLOAT   = 4
};

enum MessageType {
    PGM_CHANGE      = 0,
    NOTE_MSG        = 1,
};


enum SysExSize {
    NONE            = 0,
    TINY            = 8,
    SMALL           = 32,
    NORMAL          = 128,
    MEDIUM          = 256,
    HIGHER          = 512,
    MAXIMUM         = 1024
};


#endif