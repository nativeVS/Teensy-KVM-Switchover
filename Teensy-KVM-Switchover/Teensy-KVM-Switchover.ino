#define STARTECH        1
#define XDIP            2
#define ADDER           2
#define ENABLE          1
#define ENABLED         1
#define DISABLE         0
#define DISABLED        0
#define VOLTAGE         0
#define CONTACT_CLOSURE 1
#define CONTACT_HIGH    2
#define VOLTAGE_INV     3
#define VOLTAGE_FLOAT   4

#include <Bounce2.h>
#include <EEPROM.h>


///////------------------- USER SETTINGS -------------------///////

//Set input pins for switchover button (or connect one to GPO from console, or Tally output on other switchover device)
constexpr int pin_switchover1{ 18 };                //external contact closure button (short to gnd)
constexpr int pin_switchover2{ 19 };                //second switchover input, can be configured below

//Enable Second switchover input
constexpr int switchoverType_2{ CONTACT_CLOSURE };
//Following types are possible:
//DISABLE
//VOLTAGE         - pulled low, requires high to trigger
//VOLTAGE_FLOAT   - floating, requires high to trigger
//CONTACT_CLOSURE - pulled high in off state, short to ground to trigger (same mode as first Switchover Input)
//CONTACT_HIGH    - pulled high in off state, requires rising edge to trigger (i.e triggers on release of button shorted to gnd)
//VOLTAGE_INV     - floating, requires low to trigger

//Set input pins to force to either Main or Backup (both contact closure)
constexpr int pin_switchoverSet1{ 11 };
constexpr int pin_switchoverSet2{ 12 };

//LED Pins (maximum current on Teensy 4.x is 4mA; combined with this being 3.3V don't expect to run Blue or White LEDs with any serious brightness)
constexpr int pin_LED{ 13 };   //13 for internal    //On when on backup, off on main; can be used via an inverter buffer to drive devices that require an always on signal to select main
constexpr int pin_set1LED{ 16 };                    //On when Main selected
constexpr int pin_set2LED{ 17 };                    //On when Backup selected - it's possible to connect a bi-colour LED across these two pins (via series resistor of course)

//Set Trigger Outputs
constexpr int pin_momentaryExternal{ 22 };          //external output
constexpr int pin_momentaryExternal_2{ 23 };        //second external output
constexpr int momentaryTime{ 10 };                  //sets time (in milliseoncds) that this signal is active for when a switchover state gets triggered
constexpr int externalType{ CONTACT_CLOSURE };
constexpr int externalType_2{ VOLTAGE };
//Following types are possible:
//VOLTAGE         - low, goes high when triggerd (i.e. ACTIVE_HIGH)
//CONTACT_CLOSURE - floating, goes to ground when triggered (useful when connecting to devices with unknown pullup resistance)
//CONTACT_HIGH    - floating, goes positive when triggerd
//VOLTAGE_INV     - high in off state, goes low when triggerd (i.e. ACTIVE_LOW)


//Set KVM Type - current options: ADDER or STARTECH; can be left blank if no kvm switching required (a bit pointless, I guess, but may hint at options for what is to come)
constexpr int kvmType{ STARTECH };


constexpr bool recallPowerUpState{ ENABLE };        //If enabled switchover will return to state at last power up; if disabled it will reset to Main whenever turned on; useful in case of powerloss on USB


constexpr uint16_t debounceTime{ 10 };              //Default Debounce Time of 10 for all switching
constexpr uint16_t debounceTwo{ 10 };               //seperate debounce time for second switchover Input


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Bounce2::Button switchoverInput1 = Bounce2::Button();
Bounce2::Button switchoverInput2 = Bounce2::Button();
Bounce2::Button switchoverSet1 = Bounce2::Button();
Bounce2::Button switchoverSet2 = Bounce2::Button();

bool currentState{ 1 };         //status of switchover

bool enableSwitchover2{ DISABLE };
int switchover2type{ INPUT_PULLUP };
bool switchover2pressedState{ LOW }; 

void hardwarePinSetup();
void KVMMain();
void KVMBackup();
void switchover();
void momentaryOutput(int, uint16_t, int);
void switchoverSetMain();
void switchoverSetBackup();
void switchoverLoop();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {

  hardwarePinSetup();

  if (recallPowerUpState){
    if (EEPROM.read(0) == (1 || 0)){
      currentState = !(EEPROM.read(0));
    }
  }
  
  switchover();

  digitalWrite(pin_LED,1);
  delay(1000);
  digitalWrite(pin_LED,0);

}

void loop() {

  switchoverLoop();

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
  momentaryOutput(pin_momentaryExternal, momentaryTime, externalType);
  momentaryOutput(pin_momentaryExternal_2, momentaryTime, externalType_2);
  KVMMain();
  digitalWrite(pin_LED,0);
  EEPROM.write(0,0);
  digitalWrite(pin_set1LED, 1);
  digitalWrite(pin_set2LED, 0);
}

void switchoverSetBackup(){
  currentState = 1;
  momentaryOutput(pin_momentaryExternal, momentaryTime, externalType);
  momentaryOutput(pin_momentaryExternal_2, momentaryTime, externalType_2);
  KVMBackup();
  digitalWrite(pin_LED,1);
  EEPROM.write(0,1);
  digitalWrite(pin_set1LED, 0);
  digitalWrite(pin_set2LED, 1);
}


void KVMMain(){
  switch (kvmType){
    case STARTECH:
      Keyboard.press(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.release(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.press(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.release(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.press(KEY_1);
      delay(5);
      Keyboard.release(KEY_1);
      break;
    case XDIP:
      Keyboard.press(MODIFIERKEY_CTRL);
      Keyboard.press(MODIFIERKEY_ALT);
      Keyboard.press(KEY_1);
      delay(10); //arbitrary guess, but works
      Keyboard.release(MODIFIERKEY_CTRL);
      Keyboard.release(MODIFIERKEY_ALT);
      Keyboard.release(KEY_1);
      break;
  }
}

void KVMBackup(){
  switch (kvmType){
    case STARTECH:
      Keyboard.press(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.release(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.press(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.release(MODIFIERKEY_CTRL);
      delay(5);
      Keyboard.press(KEY_2);
      delay(5);
      Keyboard.release(KEY_2);
      break;
    case XDIP:
      Keyboard.press(MODIFIERKEY_CTRL);
      Keyboard.press(MODIFIERKEY_ALT);
      Keyboard.press(KEY_2);
      delay(10); //arbitrary guess, but works
      Keyboard.release(MODIFIERKEY_CTRL);
      Keyboard.release(MODIFIERKEY_ALT);
      Keyboard.release(KEY_2);
      break;
  }
}


void momentaryOutput(int pin, uint16_t interval, int type){
  switch (type){
    case VOLTAGE:
      digitalWrite(pin, 1);
      delay(interval);
      digitalWrite(pin, 1);
      break;
    case CONTACT_CLOSURE:
      digitalWrite(pin, 0);
      delay(interval);
      pinMode(pin, INPUT_DISABLE);
      break;
    case CONTACT_HIGH:
      digitalWrite(pin, 1);
      delay(interval);
      pinMode(pin, INPUT_DISABLE);
      break;
    case VOLTAGE_INV:
      digitalWrite(pin, 0);
      delay(interval);
      digitalWrite(pin, 1);
      break;
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
