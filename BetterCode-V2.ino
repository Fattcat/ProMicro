// Here GOING TO BE ADDED stuff like :
// 1. RED, GREEN, ORANGE LEDS Indicators :
// - RED LED    - If LIGHTS then it Indicates CODE Error or else error
// - GREEN LED  - If LIGHTS then it Indicates CODE 
// - ORANGE LED - If LIGHTS then it Indicates CODE Code still in process (Code still running)
// COMMANDS :
// - Blink(RED_LED, int times) // Which LED and how many times to blink
// --> Blink(RED_LED, 3)

// 2. ADDed Function for MOUSE MOVING
// - void(MOUSE_Move_Left, int pixels)
// - void(MOUSE_Move_Right, int pixels)
// - void(MOUSE_Move_Down, int pixels)
// - void(MOUSE_Move_Up, int pixels)
// - void(Mouse_Click) // Just click
// - void(Mouse_Click, int x_position, int y_position) // Click on x, y Position
// And Other ...
// Code

// Konečné pripojenie SD karty a Pro Micro
// ------------------------------------
// VCC -> VCC na SD karte
// GND -> GND na SD karte
// D14 (MISO) -> MISO na SD karte
// D16 (MOSI) -> MOSI na SD karte
// D15 (SCK) -> SCK na SD karte
// D10 (SS) -> CS na SD karte
// ------------------------------------

#include <SPI.h>
#include <SD.h>
#include <string.h>
#include "Keyboard.h"
#include "Mouse.h"  // Pridáme podporu pre myš

#define GREEN_LED 3  // GREEN LED Pin 3 na Pro Micro (označuje dokončenie)
#define ORANGE_LED 4 // ORANGE LED Pin 4 na Pro Micro (označuje prebiehajúce spracovanie)

File myFile;
boolean first = true;
String DEFAULT_FILE_NAME = "inject.txt";

void setup() {
  // Nastavíme piny pre LED diódy
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);

  // Rozsvietime oranžovú LED, kód sa začína spracovávať
  digitalWrite(ORANGE_LED, HIGH);

  // PIN CS JE na Pri Micro Pine číslo 10
  if (!SD.begin(10)) {
    return;
  }

  myFile = SD.open(DEFAULT_FILE_NAME);
  if (myFile) {
    Keyboard.begin();
    Mouse.begin();  // Spustíme podporu myši

    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n') {
        Line(line);
        line = "";
      } else if ((int)m != 13) {
        line += m;
      }
    }
    Line(line);

    myFile.close();
  }

  Keyboard.end();
  Mouse.end();  // Ukončíme podporu myši po spracovaní

  // Keď je kód ukončený, zhasneme oranžovú LED a rozsvietime zelenú
  digitalWrite(ORANGE_LED, LOW);  // Zhasneme oranžovú LED
  digitalWrite(GREEN_LED, HIGH);  // Rozsvietime zelenú LED (signalizuje ukončenie)
}

void Line(String l) {
  int space_1 = l.indexOf(" ");
  if (space_1 == -1) {
    Press(l);
  } else if (l.substring(0, space_1) == "STRING") {
    Keyboard.print(l.substring(space_1 + 1));
  } else if (l.substring(0, space_1) == "DELAY") {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  } else if (l.substring(0, space_1) == "Mouse_Move_RIGHT") {
    int move_amount = l.substring(space_1 + 1).toInt();
    Mouse.move(move_amount, 0);  // Pohyb myši do prava
  } else if (l.substring(0, space_1) == "Mouse_Move_LEFT") {
    int move_amount = l.substring(space_1 + 1).toInt();
    Mouse.move(-move_amount, 0);  // Pohyb myši do ľava
  } else if (l.substring(0, space_1) == "Mouse_Move_UP") {
    int move_amount = l.substring(space_1 + 1).toInt();
    Mouse.move(0, -move_amount);  // Pohyb myši hore
  } else if (l.substring(0, space_1) == "Mouse_Move_DOWN") {
    int move_amount = l.substring(space_1 + 1).toInt();
    Mouse.move(0, move_amount);  // Pohyb myši dole
  } else if (l.substring(0, space_1) == "REM") {
    // Komentár, nič nerobiť
  } else {
    String remain = l;
    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      } else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }

  Keyboard.releaseAll();
}

void Press(String b) {
  if (b.equals("ENTER")) {
    Keyboard.press(KEY_RETURN);
  } else if (b.equals("CTRL")) {
    Keyboard.press(KEY_LEFT_CTRL);
  } else if (b.equals("SHIFT")) {
    Keyboard.press(KEY_LEFT_SHIFT);
  } else if (b.equals("ALT")) {
    Keyboard.press(KEY_LEFT_ALT);
  } else if (b.equals("GUI")) {
    Keyboard.press(KEY_LEFT_GUI);
  } else if (b.equals("UP") || b.equals("UPARROW")) {
    Keyboard.press(KEY_UP_ARROW);
  } else if (b.equals("DOWN") || b.equals("DOWNARROW")) {
    Keyboard.press(KEY_DOWN_ARROW);
  } else if (b.equals("LEFT") || b.equals("LEFTARROW")) {
    Keyboard.press(KEY_LEFT_ARROW);
  } else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) {
    Keyboard.press(KEY_RIGHT_ARROW);
  } else if (b.equals("DELETE")) {
    Keyboard.press(KEY_DELETE);
  } else if (b.equals("PAGEUP")) {
    Keyboard.press(KEY_PAGE_UP);
  } else if (b.equals("PAGEDOWN")) {
    Keyboard.press(KEY_PAGE_DOWN);
  } else if (b.equals("HOME")) {
    Keyboard.press(KEY_HOME);
  } else if (b.equals("ESC")) {
    Keyboard.press(KEY_ESC);
  } else if (b.equals("INSERT")) {
    Keyboard.press(KEY_INSERT);
  } else if (b.equals("TAB")) {
    Keyboard.press(KEY_TAB);
  } else if (b.equals("END")) {
    Keyboard.press(KEY_END);
  } else if (b.equals("CAPSLOCK")) {
    Keyboard.press(KEY_CAPS_LOCK);
  } else if (b.equals("F1")) {
    Keyboard.press(KEY_F1);
  } else if (b.equals("F2")) {
    Keyboard.press(KEY_F2);
  } else if (b.equals("F3")) {
    Keyboard.press(KEY_F3);
  } else if (b.equals("F4")) {
    Keyboard.press(KEY_F4);
  } else if (b.equals("F5")) {
    Keyboard.press(KEY_F5);
  } else if (b.equals("F6")) {
    Keyboard.press(KEY_F6);
  } else if (b.equals("F7")) {
    Keyboard.press(KEY_F7);
  } else if (b.equals("F8")) {
    Keyboard.press(KEY_F8);
  } else if (b.equals("F9")) {
    Keyboard.press(KEY_F9);
  } else if (b.equals("F10")) {
    Keyboard.press(KEY_F10);
  } else if (b.equals("F11")) {
    Keyboard.press(KEY_F11);
  } else if (b.equals("F12")) {
    Keyboard.press(KEY_F12);
  } else if (b.equals("SPACE")) {
    Keyboard.press(' ');
  } else {
    char c = b[0];
    uint8_t keyCode = OemKeyToKeyCode(c);
    if (keyCode != 0) {
      Keyboard.press(keyCode);
    }
  }
}

// Funkcia pre prevod hexadecimálneho kódu na klávesu
uint8_t OemKeyToKeyCode(char c) {
  switch (c) {
    case 'a':
    case 'A':
      return 'a';
    case 'b':
    case 'B':
      return 'b';
    case 'c':
    case 'C':
      return 'c';
    // Pridajte ďalšie písmená a znaky podľa potreby
    default:
      return 0;
  }
}

void loop() {
  // nič sa nestane po nastavení
}
