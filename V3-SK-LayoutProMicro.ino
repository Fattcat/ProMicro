// I want to learn how spacehuhn made support for other Keyboard Langguages.
It is Hard to make library for supoorting non US keyboard type.

// here is Beta V1.0.0 for SK
// code

// SK_Keyboard.h - Slovak Keyboard Layout for Arduino Pro Micro (HID) // Author: ChatGPT for custom HID SK layout usage // Version: 1.0.0

#ifndef SK_KEYBOARD_H #define SK_KEYBOARD_H

#include <Arduino.h> #include <HID-Project.h> #include <HID-Settings.h>

// Modifier macros #define MOD_SHIFT 0x02 #define MOD_ALTGR 0x40

// HID Keycode definitions for SK QWERTY // These map Slovak keyboard characters to HID codes and modifier states typedef struct { uint8_t modifier; uint8_t keycode; } SK_Key;

// ASCII to HID mapping for Slovak QWERTY // This map includes common diacritic characters and symbols const SK_Key SK_AsciiMap[128] PROGMEM = { {0, 0},      // 0x00 NUL {0, 0},      // 0x01 SOH {0, 0},      // 0x02 STX {0, 0},      // 0x03 ETX {0, 0},      // 0x04 EOT {0, 0},      // 0x05 ENQ {0, 0},      // 0x06 ACK {0, 0},      // 0x07 BEL {0, 0x2a},   // 0x08 BACKSPACE {0, 0x2b},   // 0x09 TAB {0, 0x28},   // 0x0A LF {0, 0},      // ... up to 0x1F skipped

// Printable ASCII
{0, 0x2c},           // Space
{MOD_SHIFT, 0x1e},  // !
{MOD_SHIFT, 0x34},  // "
{MOD_SHIFT, 0x20},  // #
{MOD_SHIFT, 0x21},  // $
{MOD_SHIFT, 0x22},  // %
{MOD_SHIFT, 0x24},  // &
{0, 0x34},           // '
{MOD_SHIFT, 0x26},  // (
{MOD_SHIFT, 0x27},  // )
{MOD_SHIFT, 0x25},  // *
{0, 0x2e},           // +
{0, 0x36},           // ,
{0, 0x2d},           // -
{0, 0x37},           // .
{0, 0x38},           // /
{0, 0x27},           // 0
{0, 0x1e},           // 1
{0, 0x1f},           // 2
{0, 0x20},           // 3
{0, 0x21},           // 4
{0, 0x22},           // 5
{0, 0x23},           // 6
{0, 0x24},           // 7
{0, 0x25},           // 8
{0, 0x26},           // 9
{MOD_SHIFT, 0x33},  // :
{0, 0x33},           // ;
{MOD_SHIFT, 0x36},  // <
{0, 0x2e},           // =
{MOD_SHIFT, 0x37},  // >
{MOD_SHIFT, 0x38},  // ?
{MOD_ALTGR, 0x14},  // @
// Letters (a-z, y/z swapped)
{0, 0x14}, {0, 0x05}, {0, 0x06}, {0, 0x07}, {0, 0x08},
{0, 0x09}, {0, 0x0a}, {0, 0x0b}, {0, 0x0c}, {0, 0x0d},
{0, 0x0e}, {0, 0x0f}, {0, 0x10}, {0, 0x11}, {0, 0x12},
{0, 0x13}, {0, 0x04}, {0, 0x15}, {0, 0x16}, {0, 0x17},
{0, 0x18}, {0, 0x19}, {0, 0x1d}, {0, 0x1b}, {0, 0x1c}, {0, 0x1a},
// Uppercase A-Z
{MOD_SHIFT, 0x14}, {MOD_SHIFT, 0x05}, {MOD_SHIFT, 0x06}, {MOD_SHIFT, 0x07}, {MOD_SHIFT, 0x08},
{MOD_SHIFT, 0x09}, {MOD_SHIFT, 0x0a}, {MOD_SHIFT, 0x0b}, {MOD_SHIFT, 0x0c}, {MOD_SHIFT, 0x0d},
{MOD_SHIFT, 0x0e}, {MOD_SHIFT, 0x0f}, {MOD_SHIFT, 0x10}, {MOD_SHIFT, 0x11}, {MOD_SHIFT, 0x12},
{MOD_SHIFT, 0x13}, {MOD_SHIFT, 0x04}, {MOD_SHIFT, 0x15}, {MOD_SHIFT, 0x16}, {MOD_SHIFT, 0x17},
{MOD_SHIFT, 0x18}, {MOD_SHIFT, 0x19}, {MOD_SHIFT, 0x1d}, {MOD_SHIFT, 0x1b}, {MOD_SHIFT, 0x1c}, {MOD_SHIFT, 0x1a},
// Symbols
{MOD_ALTGR, 0x64}, // [
{MOD_ALTGR, 0x64}, // \
{MOD_ALTGR, 0x64}, // ]
{MOD_ALTGR, 0x20}, // ^
{MOD_ALTGR, 0x38}, // _
{0, 0x34},         // `
// Diacritics and national chars (é, ä, ô, ľ, etc.) can be added as UTF8 handling or additional maps

};

#endif // SK_KEYBOARD_H

