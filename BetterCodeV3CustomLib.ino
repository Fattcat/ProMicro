#include <SPI.h>
#include <SD.h>
#include <Keyboard.h>
#include <Mouse.h>

#define GREEN_LED 3
#define ORANGE_LED 4
#define SD_CS_PIN 10
#define FILENAME "inject.txt"

File injectFile;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  digitalWrite(ORANGE_LED, HIGH);

  if (!SD.begin(SD_CS_PIN)) {
    blinkError();
    return;
  }

  injectFile = SD.open(FILENAME);
  if (!injectFile) {
    blinkError();
    return;
  }

  Keyboard.begin();
  Mouse.begin();

  String line = "";
  while (injectFile.available()) {
    char ch = injectFile.read();
    if (ch == '\n') {
      processLine(line);
      line = "";
    } else if (ch != '\r') {
      line += ch;
    }
  }

  if (line.length() > 0) {
    processLine(line);
  }

  injectFile.close();
  Keyboard.end();
  Mouse.end();

  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void blinkError() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ORANGE_LED, HIGH);
    delay(100);
    digitalWrite(ORANGE_LED, LOW);
    delay(100);
  }
}

void processLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  int spaceIdx = line.indexOf(' ');
  String cmd = (spaceIdx == -1) ? line : line.substring(0, spaceIdx);
  String param = (spaceIdx == -1) ? "" : line.substring(spaceIdx + 1);

  if (cmd == "STRING") {
    Keyboard.print(param);
  } else if (cmd == "DELAY") {
    delay(param.toInt());
  } else if (cmd == "REM") {
    // komentár, nič sa nevykoná
  } else if (cmd == "Mouse_Click_LEFT") {
    Mouse.click(MOUSE_LEFT);
  } else if (cmd == "Mouse_Click_RIGHT") {
    Mouse.click(MOUSE_RIGHT);
  } else if (cmd == "Mouse_Move_LEFT") {
    Mouse.move(-param.toInt(), 0);
  } else if (cmd == "Mouse_Move_RIGHT") {
    Mouse.move(param.toInt(), 0);
  } else if (cmd == "Mouse_Move_UP") {
    Mouse.move(0, -param.toInt());
  } else if (cmd == "Mouse_Move_DOWN") {
    Mouse.move(0, param.toInt());
  } else if (cmd == "CTRL" || cmd == "SHIFT" || cmd == "ALT" || cmd == "GUI") {
    handleModifier(cmd, param);
  } else {
    pressKey(cmd);
  }

  Keyboard.releaseAll();
}

void handleModifier(String modifier, String keys) {
  if (modifier == "CTRL") Keyboard.press(KEY_LEFT_CTRL);
  else if (modifier == "SHIFT") Keyboard.press(KEY_LEFT_SHIFT);
  else if (modifier == "ALT") Keyboard.press(KEY_LEFT_ALT);
  else if (modifier == "GUI") Keyboard.press(KEY_LEFT_GUI);

  delay(50);

  while (keys.length() > 0) {
    int spaceIdx = keys.indexOf(' ');
    String key = (spaceIdx == -1) ? keys : keys.substring(0, spaceIdx);
    pressKey(key);
    keys = (spaceIdx == -1) ? "" : keys.substring(spaceIdx + 1);
  }

  delay(50);

  if (modifier == "CTRL") Keyboard.release(KEY_LEFT_CTRL);
  else if (modifier == "SHIFT") Keyboard.release(KEY_LEFT_SHIFT);
  else if (modifier == "ALT") Keyboard.release(KEY_LEFT_ALT);
  else if (modifier == "GUI") Keyboard.release(KEY_LEFT_GUI);
}

void pressKey(String key) {
  key.toUpperCase();

  if (key == "ENTER") Keyboard.press(KEY_RETURN);
  else if (key == "TAB") Keyboard.press(KEY_TAB);
  else if (key == "ESC") Keyboard.press(KEY_ESC);
  else if (key == "SPACE") Keyboard.press(' ');
  else if (key == "UP" || key == "UPARROW") Keyboard.press(KEY_UP_ARROW);
  else if (key == "DOWN" || key == "DOWNARROW") Keyboard.press(KEY_DOWN_ARROW);
  else if (key == "LEFT" || key == "LEFTARROW") Keyboard.press(KEY_LEFT_ARROW);
  else if (key == "RIGHT" || key == "RIGHTARROW") Keyboard.press(KEY_RIGHT_ARROW);
  else if (key == "DELETE") Keyboard.press(KEY_DELETE);
  else if (key == "HOME") Keyboard.press(KEY_HOME);
  else if (key == "END") Keyboard.press(KEY_END);
  else if (key == "PAGEUP") Keyboard.press(KEY_PAGE_UP);
  else if (key == "PAGEDOWN") Keyboard.press(KEY_PAGE_DOWN);
  else if (key.startsWith("F")) {
    int fn = key.substring(1).toInt();
    if (fn >= 1 && fn <= 12) Keyboard.press(KEY_F1 + fn - 1);
  } else if (key.length() == 1) {
    Keyboard.press(key.charAt(0));
  }
}

void loop() {
  // nič sa nevykonáva
}
