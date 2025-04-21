#include "SKKeyboard.h"

void SKKeyboard::begin() {
    Keyboard.begin();
}

void SKKeyboard::end() {
    Keyboard.end();
}

void SKKeyboard::releaseAll() {
    Keyboard.releaseAll();
}

void SKKeyboard::pressKey(uint8_t modifier, uint8_t keycode) {
    if (modifier) Keyboard.press(modifier);
    Keyboard.press(keycode);
    delay(5);
    releaseAll();
}

void SKKeyboard::pressChar(char c) {
    switch (c) {
        // Písmená bez diakritiky (malé)
        case 'a': pressKey(0, 0x04); break;
        case 'b': pressKey(0, 0x05); break;
        case 'c': pressKey(0, 0x06); break;
        case 'd': pressKey(0, 0x07); break;
        case 'e': pressKey(0, 0x08); break;
        case 'f': pressKey(0, 0x09); break;
        case 'g': pressKey(0, 0x0A); break;
        case 'h': pressKey(0, 0x0B); break;
        case 'i': pressKey(0, 0x0C); break;
        case 'j': pressKey(0, 0x0D); break;
        case 'k': pressKey(0, 0x0E); break;
        case 'l': pressKey(0, 0x0F); break;
        case 'm': pressKey(0, 0x10); break;
        case 'n': pressKey(0, 0x11); break;
        case 'o': pressKey(0, 0x12); break;
        case 'p': pressKey(0, 0x13); break;
        case 'q': pressKey(0, 0x14); break;
        case 'r': pressKey(0, 0x15); break;
        case 's': pressKey(0, 0x16); break;
        case 't': pressKey(0, 0x17); break;
        case 'u': pressKey(0, 0x18); break;
        case 'v': pressKey(0, 0x19); break;
        case 'w': pressKey(0, 0x1A); break;
        case 'x': pressKey(0, 0x1B); break;
        case 'y': pressKey(0, 0x1C); break;
        case 'z': pressKey(0, 0x1D); break;

        // Veľké písmená bez diakritiky
        case 'A': pressKey(MOD_SHIFT, 0x04); break;
        case 'B': pressKey(MOD_SHIFT, 0x05); break;
        case 'C': pressKey(MOD_SHIFT, 0x06); break;
        case 'D': pressKey(MOD_SHIFT, 0x07); break;
        case 'E': pressKey(MOD_SHIFT, 0x08); break;
        case 'F': pressKey(MOD_SHIFT, 0x09); break;
        case 'G': pressKey(MOD_SHIFT, 0x0A); break;
        case 'H': pressKey(MOD_SHIFT, 0x0B); break;
        case 'I': pressKey(MOD_SHIFT, 0x0C); break;
        case 'J': pressKey(MOD_SHIFT, 0x0D); break;
        case 'K': pressKey(MOD_SHIFT, 0x0E); break;
        case 'L': pressKey(MOD_SHIFT, 0x0F); break;
        case 'M': pressKey(MOD_SHIFT, 0x10); break;
        case 'N': pressKey(MOD_SHIFT, 0x11); break;
        case 'O': pressKey(MOD_SHIFT, 0x12); break;
        case 'P': pressKey(MOD_SHIFT, 0x13); break;
        case 'Q': pressKey(MOD_SHIFT, 0x14); break;
        case 'R': pressKey(MOD_SHIFT, 0x15); break;
        case 'S': pressKey(MOD_SHIFT, 0x16); break;
        case 'T': pressKey(MOD_SHIFT, 0x17); break;
        case 'U': pressKey(MOD_SHIFT, 0x18); break;
        case 'V': pressKey(MOD_SHIFT, 0x19); break;
        case 'W': pressKey(MOD_SHIFT, 0x1A); break;
        case 'X': pressKey(MOD_SHIFT, 0x1B); break;
        case 'Y': pressKey(MOD_SHIFT, 0x1C); break;
        case 'Z': pressKey(MOD_SHIFT, 0x1D); break;

        // Slovenská diakritika (malé)
        case 'á': pressKey(MOD_ALTGR, 0x14); break; // AltGr + Q
        case 'ä': pressKey(MOD_ALTGR, 0x1F); break; // AltGr + S
        case 'č': pressKey(MOD_ALTGR, 0x06); break; // AltGr + C
        case 'ď': pressKey(MOD_ALTGR, 0x07); break; // AltGr + D
        case 'é': pressKey(MOD_ALTGR, 0x08); break; // AltGr + E
        case 'í': pressKey(MOD_ALTGR, 0x0C); break; // AltGr + I
        case 'ľ': pressKey(MOD_ALTGR, 0x0F); break; // AltGr + L
        case 'ĺ': pressKey(MOD_ALTGR, 0x0F); break; // rovnaký ako ľ (alebo vlastné makro)
        case 'ň': pressKey(MOD_ALTGR, 0x11); break; // AltGr + N
        case 'ó': pressKey(MOD_ALTGR, 0x12); break; // AltGr + O
        case 'ô': pressKey(MOD_ALTGR, 0x13); break; // AltGr + P
        case 'ŕ': pressKey(MOD_ALTGR, 0x15); break; // AltGr + R
        case 'š': pressKey(MOD_ALTGR, 0x16); break; // AltGr + S
        case 'ť': pressKey(MOD_ALTGR, 0x17); break; // AltGr + T
        case 'ú': pressKey(MOD_ALTGR, 0x18); break; // AltGr + U
        case 'ý': pressKey(MOD_ALTGR, 0x1C); break; // AltGr + Y
        case 'ž': pressKey(MOD_ALTGR, 0x1D); break; // AltGr + Z

        // Interpunkcia a špeciálne znaky
        case ' ': pressKey(0, 0x2C); break;
        case '\n': pressKey(0, 0x28); break;
        case '.': pressKey(0, 0x37); break;
        case ',': pressKey(0, 0x36); break;
        case '!': pressKey(MOD_SHIFT, 0x1E); break; // Shift + 1
        case '?': pressKey(MOD_SHIFT, 0x38); break; // Shift + ,
        case '-': pressKey(0, 0x2D); break;
        case '_': pressKey(MOD_SHIFT, 0x2D); break;
        case ':': pressKey(MOD_SHIFT, 0x33); break;
        case ';': pressKey(0, 0x33); break;
        case '"': pressKey(MOD_SHIFT, 0x34); break;
        case '\'': pressKey(0, 0x34); break;
        case '(': pressKey(MOD_SHIFT, 0x26); break;
        case ')': pressKey(MOD_SHIFT, 0x27); break;

        default:
            break; // Neznámy/nezmapovaný znak
    }
}

void SKKeyboard::writeString(const char* str) {
    while (*str) {
        pressChar(*str++);
        delay(5);
    }
}
