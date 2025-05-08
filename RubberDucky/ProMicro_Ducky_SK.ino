#include <Keyboard.h>
#include <SPI.h>
#include <SD.h>
#include "SKKeyboard.h"

const int chipSelect = 10;
File duckyScript;

void handleGUICombo(String line) {
  if (line.length() == 5 && line.startsWith("GUI ")) {
    char key = line.charAt(4);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(key);
    delay(100);
    Keyboard.releaseAll();
  }
}

void pressSpecial(String key) {
  if (key == "ENTER") Keyboard.write(KEY_RETURN);
  else if (key == "TAB") Keyboard.write(KEY_TAB);
  else if (key == "ESCAPE") Keyboard.write(KEY_ESC);
  else if (key == "SPACE") Keyboard.write(' ');
  else if (key == "UP") Keyboard.write(KEY_UP_ARROW);
  else if (key == "DOWN") Keyboard.write(KEY_DOWN_ARROW);
  else if (key == "LEFT") Keyboard.write(KEY_LEFT_ARROW);
  else if (key == "RIGHT") Keyboard.write(KEY_RIGHT_ARROW);
  else if (key == "F1") Keyboard.write(KEY_F1);
  else if (key == "F2") Keyboard.write(KEY_F2);
  else if (key == "F3") Keyboard.write(KEY_F3);
  else if (key == "F4") Keyboard.write(KEY_F4);
  else if (key == "F5") Keyboard.write(KEY_F5);
  else if (key == "F6") Keyboard.write(KEY_F6);
  else if (key == "F7") Keyboard.write(KEY_F7);
  else if (key == "F8") Keyboard.write(KEY_F8);
  else if (key == "F9") Keyboard.write(KEY_F9);
  else if (key == "F10") Keyboard.write(KEY_F10);
  else if (key == "F11") Keyboard.write(KEY_F11);
  else if (key == "F12") Keyboard.write(KEY_F12);
}

void setup() {
  delay(2000);
  Keyboard.begin();
  Serial.begin(9600);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD karta sa nenačítala.");
    return;
  }

  duckyScript = SD.open("inject.txt");
  if (!duckyScript) {
    Serial.println("inject.txt sa nenačítal.");
    return;
  }

  while (duckyScript.available()) {
    String line = duckyScript.readStringUntil('\n');
    line.trim();

    if (line.startsWith("REM") || line.length() == 0) continue;

    if (line.startsWith("DELAY")) {
      int t = line.substring(6).toInt();
      delay(t);
    } else if (line.startsWith("STRING")) {
      String toType = line.substring(7);
      SKKeyboard::type(toType); // Použitie SK mapy
    } else if (line.startsWith("GUI ")) {
      handleGUICombo(line);
    } else {
      pressSpecial(line);
    }

    delay(50);
  }

  duckyScript.close();
  Keyboard.end();
}

void loop() {
  // Prázdne
}
