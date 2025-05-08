#ifndef SKKEYBOARD_H
#define SKKEYBOARD_H

#include <Keyboard.h>

class SKKeyboard {
public:
  static void type(const String &text) {
    for (unsigned int i = 0; i < text.length(); i++) {
      write(text[i]);
      delay(5);
    }
  }

  static void write(char c) {
    switch (c) {
      // Diakritické znaky cez AltGr
      case 'á': case 'Á': alt('a'); break;
      case 'č': case 'Č': alt('c'); break;
      case 'ď': case 'Ď': alt('d'); break;
      case 'é': case 'É': alt('e'); break;
      case 'í': case 'Í': alt('i'); break;
      case 'ľ': case 'Ľ': alt('l'); break;
      case 'ň': case 'Ň': alt('n'); break;
      case 'ó': case 'Ó': alt('o'); break;
      case 'š': case 'Š': alt('s'); break;
      case 'ť': case 'Ť': alt('t'); break;
      case 'ú': case 'Ú': alt('u'); break;
      case 'ý': case 'Ý': alt('y'); break;
      case 'ž': case 'Ž': alt('z'); break;

      // Špeciálne znaky cez AltGr
      case '@': alt('v'); break;
      case '#': alt('x'); break;
      case '{': alt('b'); break;
      case '}': alt('n'); break;
      case '[': alt('f'); break;
      case ']': alt('g'); break;
      case '|': alt('w'); break;
      case '\\': alt('q'); break;
      case '~': alt('1'); break;
      case '^': alt('3'); break;
      case '`': alt('2'); break;
      case '<': alt(','); break;
      case '>': alt('.'); break;
      case '$': alt('4'); break;
      case '€': alt('e'); break;

      // Slovenské SHIFT kombinácie
      case ':': shift('.'); break;
      case ';': shift(','); break;

      default: Keyboard.write(c); return;
    }

    delay(5);
    Keyboard.releaseAll();
  }

private:
  static void alt(char base) {
    Keyboard.press(KEY_RIGHT_ALT);
    Keyboard.press(base);
  }

  static void shift(char base) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(base);
  }
};

#endif
