#ifndef SKKEYBOARD_H
#define SKKEYBOARD_H

#include <Arduino.h>
#include <Keyboard.h>

// Modifier keys
#define MOD_SHIFT KEY_LEFT_SHIFT
#define MOD_ALTGR KEY_RIGHT_ALT

class SKKeyboard {
public:
    void begin();
    void end();
    void writeString(const char* str);

private:
    void pressChar(char c);
    void pressKey(uint8_t modifier, uint8_t keycode);
    void releaseAll();
};

#endif
