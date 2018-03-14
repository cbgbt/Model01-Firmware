// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details
// This is cbgbt's fork of the default Model01 Firmware.
//
// These keymaps are largely inspired by the original default layout of the
// Atreus keyboard.
// Changes:
// - Change QWERTY layer to emulate Atreus more closely on RHS of right hand
// - Add Atreus support to LHS of NUMPAD layer
// - Fix RHS of Numpad layer to be more Atreus-like
// - Add ATREMU layer to emulate the bottom row of keys on an Atreus in the bottom of Keyboardio (keyboardio homerow is lower than Atreus)
// - Add DigitalRain plugin
// - Remove mouse support
// - Remove a few default LED plugins
// TODO -- Make an FPS layer which binds keys away from index finger

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LEDEffect-DigitalRain.h"
#include "Kaleidoscope-HostPowerManagement.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };



/** The Model 01's key layouts are defined as 'keymaps'.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(KBIOFUNCTION)' will switch to KBIOFUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, KBIOFUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { QWERTY, NUMPAD, ATREMU, KBIOFUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

/* Missing keys:
 * QWERTY
 * Key_LeftGui
 * Key_PageUp, Key_PageDown
 * Key_RightShift
 *
 * NUMPAD
 * Key_KeypadSubtract, Key_KeypadDivide
 */

const Key keymaps[][ROWS][COLS] PROGMEM = {
  [QWERTY] = KEYMAP_STACKED
  (___,           Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Tab,       Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_Tab,       Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_Escape,    Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftShift, Key_Backspace, Key_LeftControl, Key_Quote,
   ShiftToLayer(ATREMU),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Enter,
   Key_Minus, Key_LeftAlt, Key_Spacebar, ShiftToLayer(NUMPAD),
   ShiftToLayer(ATREMU)),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, LSHIFT(Key_1), LSHIFT(Key_2), LSHIFT(Key_LeftCurlyBracket), LSHIFT(Key_RightCurlyBracket), LSHIFT(Key_Backslash), ___,
   ___, LSHIFT(Key_3), LSHIFT(Key_4), LSHIFT(Key_9),                LSHIFT(Key_0),                 Key_Backtick,
   ___, LSHIFT(Key_5), LSHIFT(Key_6), Key_LeftCurlyBracket,         Key_RightCurlyBracket,         LSHIFT(Key_Backtick),  ___,
                  ___, LSHIFT(Key_Insert), Key_PrintScreen, ___,
                                           ___,

   M(MACRO_VERSION_INFO),  Key_PageUp,    XXX,         Key_KeypadDot, Key_Keypad0,  Key_KeypadMultiply, ___,
   ___,                    Key_PageDown,  Key_Keypad7, Key_Keypad8,   Key_Keypad9,  Key_KeypadAdd,      ___,
                           LSHIFT(Key_7), Key_Keypad4, Key_Keypad5,   Key_Keypad6,  Key_Backslash,      Key_Quote,
   ___,                    ___,           Key_Keypad1, Key_Keypad2,   Key_Keypad3,  Key_Equals,         Key_Enter,
   ___, ___, ___, ___,
        ___),

  // The atreus has an additional row of keys under the home row which add
  // A few keys committed to my muscle memory. We make a special function row
  // which allows for atreus-like pressing of these keys.
  [ATREMU] = KEYMAP_STACKED
  (___, ___,        ___,     ___, ___, ___, ___,
   ___, ___,        ___,     ___, ___, ___, ___,
   ___, ___,        ___,     ___, ___, ___,
   ___, Key_Escape, Key_Tab, ___, ___, ___, ___,
                    ___, ___, ___, ___,
                         ___,

   ___, ___, ___, ___,       ___,       ___,       ___,
   ___, ___, ___, ___,       ___,       ___,       ___,
        ___, ___, ___,       ___,       ___,       ___,
   ___, ___, ___, Key_Minus, Key_Quote, Key_Enter, ___,
   ShiftToLayer(KBIOFUNCTION), ___, ___, ___,
             ___),

  [KBIOFUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,     Key_F3, Key_F4, Key_F5, XXX,
   Key_Tab,  ___,              ___,        Key_UpArrow,    ___,    ___,    ___,
   Key_Home, ___,              Key_LeftArrow, Key_DownArrow,    Key_RightArrow,    ___,
   Key_End,  Key_PrintScreen,  Key_Insert, ___,    ___,    ___,    ___,
                                           ___, Key_Delete, ___, ___,
                                                 ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)

};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

void setup() {
  Kaleidoscope.setup();

  // Tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // Pulse LED button for 10 seconds on startup.
    &BootGreetingEffect,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // Makes green digital rain
    &LEDDigitalRainEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The macros plugin adds support for macros
    &Macros,

    // The HostPowerManagement plugin enables waking up the host from suspend,
    // and allows us to turn LEDs off when it goes to sleep.
    &HostPowerManagement
  );

  LEDDigitalRainEffect.DROP_TICKS = 22;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

void loop() {
  Kaleidoscope.loop();
}
