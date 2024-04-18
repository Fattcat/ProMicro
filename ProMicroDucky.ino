// ProMicroDucky.ino code
// ------------------------------------
// Konejšn                            -
//                                    -
// VCC -> VCC na SD karte             -
// GND -> GND na SD karte             -
// D14 (MISO) -> MISO na SD karte     -
// D16 (MOSI) -> MOSI na SD karte     -
// D15 (SCK) -> SCK na SD karte       -
// D10 (SS) -> CS na SD karte         -
//                                    -
// ------------------------------------

// d Duck kode
#include <SD.h>
#include <Keyboard.h>

const int chipSelect = 10; // Pin na ktorom je CS pripojený

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  
  // Skontroluje či je SD karta k dispozícii
  if (!SD.begin(chipSelect)) {
    Serial.println("Nepodarilo sa inicializovať SD kartu");
    return;
  }
  Serial.println("SD karta inicializovaná");

  executeCommands(); // Vykoná príkazy zo súboru
}

void loop() {}

void executeCommands() {
  File file = SD.open("inject.txt");
  
  if (file) {
    while (file.available()) {
      String command = file.readStringUntil('\n');
      executeCommand(command);
    }
    file.close();
  } else {
    Serial.println("Nepodarilo sa otvoriť súbor inject.txt");
  }
}

void executeCommand(String command) {
  if (command.startsWith("DELAY")) {
    int delayTime = command.substring(6).toInt();
    delay(delayTime);
  } else if (command.startsWith("STRING")) {
    String text = command.substring(7);
    Keyboard.print(text);
  } else if (command.startsWith("PRESS")) {
    String key = command.substring(6);
    pressKey(key);
  }
}

void pressKey(String key) {
  if (key == "ENTER") {
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.release(KEY_RETURN);
  } else if (key == "GUI") {
    Keyboard.press(KEY_LEFT_GUI);
    delay(100);
    Keyboard.release(KEY_LEFT_GUI);
  } else if (key == "ESC") {
    Keyboard.press(KEY_ESC);
    delay(100);
    Keyboard.release(KEY_ESC);
  } else if (key == "TAB") {
    Keyboard.press(KEY_TAB);
    delay(100);
    Keyboard.release(KEY_TAB);
  } // add more keys as needed
}
