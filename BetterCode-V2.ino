//Connection SD karty a Pro Micro
// ------------------------------------
// VCC -> VCC na SD karte
// GND -> GND na SD karte
// D14 (MISO) -> MISO na SD karte
// D16 (MOSI) -> MOSI na SD karte
// D15 (SCK) -> SCK na SD karte
// D10 (SS) -> CS na SD karte
// ------------------------------------
// Code
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include "Keyboard.h"
#include "Mouse.h"

#define GREEN_LED 3  // GREEN LED Pin 3 na Pro Micro (označuje dokončenie)
#define ORANGE_LED 4 // ORANGE LED Pin 4 na Pro Micro (označuje prebiehajúce spracovanie)

File myFile;
String DEFAULT_FILE_NAME = "inject.txt";

void setup() {
  // Nastavíme piny pre LED diódy
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);

  // Rozsvietime oranžovú LED, kód sa začína spracovávať
  digitalWrite(ORANGE_LED, HIGH);

  // Inicializujeme SD kartu
  if (!SD.begin(10)) {
    // Ak sa SD karta nedá inicializovať, blíkame oranžovou LED a vraciame sa
    for (int i = 0; i < 9; i++) {
      digitalWrite(ORANGE_LED, HIGH);
      delay(100);
      digitalWrite(ORANGE_LED, LOW);
      delay(100);
    }
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
        processLine(line); // Zmenená funkcia pre spracovanie riadka
        line = "";
      } else if (m != '\r') { // Ignorujeme carriage return
        line += m;
      }
    }
    if (line.length() > 0) { // Spracujeme posledný riadok, ak existuje
      processLine(line);
    }

    myFile.close();
  }

  Keyboard.end();
  Mouse.end();  // Ukončíme podporu myši po spracovaní

  // Zhasneme oranžovú LED a rozsvietime zelenú
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void processLine(String line) {
  // Rozdelíme riadok na jednotlivé príkazy
  int spaceIndex = line.indexOf(" ");
  String command = (spaceIndex == -1) ? line : line.substring(0, spaceIndex);
  String parameters = (spaceIndex == -1) ? "" : line.substring(spaceIndex + 1);

  if (command.equals("STRING")) {
    Keyboard.print(parameters);
  } else if (command.equals("DELAY")) {
    int delayTime = parameters.toInt();
    delay(delayTime);
  } else if (command.equals("Mouse_Click_LEFT")) {
    Mouse.click(MOUSE_LEFT); // Klikneme ľavým tlačidlom myši
  } else if (command.equals("Mouse_Click_RIGHT")) {
    Mouse.click(MOUSE_RIGHT); // Klikneme pravým tlačidlom myši
  } else if (command.startsWith("Mouse_Move_")) {
    int move_amount = parameters.toInt();
    if (command.equals("Mouse_Move_RIGHT")) {
      Mouse.move(move_amount, 0);  // Pohyb myši doprava
    } else if (command.equals("Mouse_Move_LEFT")) {
      Mouse.move(-move_amount, 0);  // Pohyb myši doľava
    } else if (command.equals("Mouse_Move_UP")) {
      Mouse.move(0, -move_amount);  // Pohyb myši hore
    } else if (command.equals("Mouse_Move_DOWN")) {
      Mouse.move(0, move_amount);  // Pohyb myši dole
    }
  } else if (command.equals("REM")) {
    // Komentár, nič nerobíme
  } else {
    handleKeyCombination(command, parameters);
  }

  Keyboard.releaseAll();
}

void handleKeyCombination(String modifier, String keys) {
  // Stlačíme modifikátor (ALT, GUI, atď.)
  if (modifier.equals("ALT")) {
    Keyboard.press(KEY_LEFT_ALT);
  } else if (modifier.equals("CTRL")) {
    Keyboard.press(KEY_LEFT_CTRL);
  } else if (modifier.equals("SHIFT")) {
    Keyboard.press(KEY_LEFT_SHIFT);
  } else if (modifier.equals("GUI")) {
    Keyboard.press(KEY_LEFT_GUI);
  }

  // Rozdelíme ďalšie kľúče, ktoré sa majú stlačiť
  String key;
  while (keys.length() > 0) {
    int spaceIndex = keys.indexOf(" ");
    if (spaceIndex == -1) {
      key = keys; // posledný kľúč
      keys = "";  // Prázdny reťazec
    } else {
      key = keys.substring(0, spaceIndex);
      keys = keys.substring(spaceIndex + 1);
    }

    // Stlačíme klávesu
    pressKey(key);
  }

  // Uvoľníme modifikátor
  if (modifier.equals("ALT")) {
    Keyboard.release(KEY_LEFT_ALT);
  } else if (modifier.equals("CTRL")) {
    Keyboard.release(KEY_LEFT_CTRL);
  } else if (modifier.equals("SHIFT")) {
    Keyboard.release(KEY_LEFT_SHIFT);
  } else if (modifier.equals("GUI")) {
    Keyboard.release(KEY_LEFT_GUI);
  }
}

void pressKey(String b) {
  if (b.equals("ENTER")) {
    Keyboard.press(KEY_RETURN);
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
  } else if (b.startsWith("F")) {
    int functionKey = b.substring(1).toInt(); // Získa číslo klávesy F
    if (functionKey >= 1 && functionKey <= 12) {
      Keyboard.press(KEY_F1 + functionKey - 1); // Prevod na správny kláves
    }
  } else if (b.equals("SPACE")) {
    Keyboard.press(' ');
  } else {
    char c = b[0];
    uint8_t keyCode = oemKeyToKeyCode(c);
    if (keyCode != 0) {
      Keyboard.press(keyCode);
    }
  }
}

// Funkcia pre prevod hexadecimálneho kódu na klávesu
uint8_t oemKeyToKeyCode(char c) {
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
void loop() {} // nič sa nestane po nastavení 
