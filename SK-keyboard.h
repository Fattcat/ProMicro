#ifndef SK_KEYBOARD_H
#define SK_KEYBOARD_H

#include "Arduino.h"
#include "Keyboard.h"

class SK_Keyboard {
public:
    static void typeChar(char c) {
        switch (c) {
            // Písmená bez diakritiky
            case 'a' ... 'z':
                if (c == 'y') Keyboard.write('z');
                else if (c == 'z') Keyboard.write('y');
                else Keyboard.write(c);
                break;

            case 'A' ... 'Z':
                if (c == 'Y') Keyboard.write('Z');
                else if (c == 'Z') Keyboard.write('Y');
                else Keyboard.write(c);
                break;

            // Diakritika
            case 'á': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('a'); Keyboard.releaseAll(); break;
            case 'é': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('e'); Keyboard.releaseAll(); break;
            case 'í': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('i'); Keyboard.releaseAll(); break;
            case 'ó': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('o'); Keyboard.releaseAll(); break;
            case 'ú': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('u'); Keyboard.releaseAll(); break;
            case 'ý': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('y'); Keyboard.releaseAll(); break;
            case 'č': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('c'); Keyboard.releaseAll(); break;
            case 'š': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('s'); Keyboard.releaseAll(); break;
            case 'ž': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('z'); Keyboard.releaseAll(); break;
            case 'ľ': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('l'); Keyboard.releaseAll(); break;
            case 'ť': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('t'); Keyboard.releaseAll(); break;
            case 'ň': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('n'); Keyboard.releaseAll(); break;
            case 'ď': Keyboard.press(KEY_LEFT_ALT); Keyboard.press('d'); Keyboard.releaseAll(); break;

            // Špeciálne znaky
            case '-': Keyboard.write('-'); break;
            case '_': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('-'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case ',': Keyboard.write(','); break;
            case '.': Keyboard.write('.'); break;
            case ':': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('.'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case ';': Keyboard.write(';'); break;
            case '!': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('1'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case '?': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('-'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case '\'': Keyboard.write('\''); break;
            case '"': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('\''); Keyboard.release(KEY_LEFT_SHIFT); break;
            case '@': Keyboard.press(KEY_RIGHT_ALT); Keyboard.write('v'); Keyboard.releaseAll(); break;
            case '+': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('='); Keyboard.release(KEY_LEFT_SHIFT); break;
            case '*': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write(';'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case '/': Keyboard.write('/'); break;
            case '\\': Keyboard.press(KEY_RIGHT_ALT); Keyboard.write('q'); Keyboard.releaseAll(); break;
            case '(': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('9'); Keyboard.release(KEY_LEFT_SHIFT); break;
            case ')': Keyboard.press(KEY_LEFT_SHIFT); Keyboard.write('0'); Keyboard.release(KEY_LEFT_SHIFT); break;

            // Medzery, nový riadok
            case ' ': Keyboard.write(' '); break;
            case '\n': Keyboard.write(KEY_RETURN); break;

            default: Keyboard.write(c); break;
        }
    }

    static void typeString(const char* str) {
        while (*str) {
            typeChar(*str++);
            delay(10); // Krátka pauza medzi znakmi
        }
    }
};

#endif