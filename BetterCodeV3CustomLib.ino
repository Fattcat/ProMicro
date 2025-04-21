#include <SPI.h>
#include <SD.h>
#include <string.h>
#include "Keyboard.h"
#include "Mouse.h"

#define GREEN_LED 3
#define ORANGE_LED 4
#define SD_CS 10

File myFile; String DEFAULT_FILE_NAME = "inject.txt";

void setup() { pinMode(GREEN_LED, OUTPUT); pinMode(ORANGE_LED, OUTPUT); digitalWrite(ORANGE_LED, HIGH);

if (!SD.begin(SD_CS)) { for (int i = 0; i < 9; i++) { digitalWrite(ORANGE_LED, HIGH); delay(100); digitalWrite(ORANGE_LED, LOW); delay(100); } return; }

myFile = SD.open(DEFAULT_FILE_NAME); if (myFile) { Keyboard.begin(); Mouse.begin();

String line = ""; while (myFile.available()) { char m = myFile.read(); if (m == '\n') { processLine(line); line = ""; } else if (m != '\r') { line += m; } } if (line.length() > 0) { processLine(line); } myFile.close(); 

}

Keyboard.end(); Mouse.end(); digitalWrite(ORANGE_LED, LOW); digitalWrite(GREEN_LED, HIGH); }

void processLine(String line) { int spaceIndex = line.indexOf(" "); String command = (spaceIndex == -1) ? line : line.substring(0, spaceIndex); String parameters = (spaceIndex == -1) ? "" : line.substring(spaceIndex + 1);

if (command.equals("STRING")) { Keyboard.print(parameters); } else if (command.equals("DELAY")) { delay(parameters.toInt()); } else if (command.equals("Mouse_Click_LEFT")) { Mouse.click(MOUSE_LEFT); } else if (command.equals("Mouse_Click_RIGHT")) { Mouse.click(MOUSE_RIGHT); } else if (command.startsWith("Mouse_Move_")) { int move_amount = parameters.toInt(); if (command.equals("Mouse_Move_RIGHT")) Mouse.move(move_amount, 0); else if (command.equals("Mouse_Move_LEFT")) Mouse.move(-move_amount, 0); else if (command.equals("Mouse_Move_UP")) Mouse.move(0, -move_amount); else if (command.equals("Mouse_Move_DOWN")) Mouse.move(0, move_amount); } else if (command.equals("REM")) { // Komentár } else { handleKeyCombination(command, parameters); }

Keyboard.releaseAll(); }

void handleKeyCombination(String modifier, String keys) { if (modifier.equals("ALT")) Keyboard.press(KEY_LEFT_ALT); else if (modifier.equals("CTRL")) Keyboard.press(KEY_LEFT_CTRL); else if (modifier.equals("SHIFT")) Keyboard.press(KEY_LEFT_SHIFT); else if (modifier.equals("GUI")) Keyboard.press(KEY_LEFT_GUI);

String key; while (keys.length() > 0) { int spaceIndex = keys.indexOf(" "); if (spaceIndex == -1) { key = keys; keys = ""; } else { key = keys.substring(0, spaceIndex); keys = keys.substring(spaceIndex + 1); } pressKey(key); }

if (modifier.equals("ALT")) Keyboard.release(KEY_LEFT_ALT); else if (modifier.equals("CTRL")) Keyboard.release(KEY_LEFT_CTRL); else if (modifier.equals("SHIFT")) Keyboard.release(KEY_LEFT_SHIFT); else if (modifier.equals("GUI")) Keyboard.release(KEY_LEFT_GUI); }

void pressKey(String b) { if (b.equals("ENTER")) Keyboard.press(KEY_RETURN); else if (b.equals("UP") || b.equals("UPARROW")) Keyboard.press(KEY_UP_ARROW); else if (b.equals("DOWN") || b.equals("DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW); else if (b.equals("LEFT") || b.equals("LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW); else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW); else if (b.equals("DELETE")) Keyboard.press(KEY_DELETE); else if (b.equals("PAGEUP")) Keyboard.press(KEY_PAGE_UP); else if (b.equals("PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN); else if (b.equals("HOME")) Keyboard.press(KEY_HOME); else if (b.equals("ESC")) Keyboard.press(KEY_ESC); else if (b.equals("INSERT")) Keyboard.press(KEY_INSERT); else if (b.equals("TAB")) Keyboard.press(KEY_TAB); else if (b.equals("END")) Keyboard.press(KEY_END); else if (b.equals("CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK); else if (b.startsWith("F")) { int fn = b.substring(1).toInt(); if (fn >= 1 && fn <= 12) Keyboard.press(KEY_F1 + fn - 1); } else if (b.equals("SPACE")) { Keyboard.press(' '); } else { char c = b.charAt(0); uint8_t k = oemKeyToKeyCode(c); if (k != 0) Keyboard.press(k); } }

uint8_t oemKeyToKeyCode(char c) { switch (c) { case 'a': case 'A': return 'a'; case 'b': case 'B': return 'b'; case 'c': case 'C': return 'c'; // Rozšír podľa potreby default: return 0; } }

void loop() {}
