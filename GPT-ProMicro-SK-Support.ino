#include <SPI.h>
#include <SD.h>
#include <HID-Project.h> // Uisti sa, že máš nainštalovanú túto knižnicu

#define GREEN_LED 3
#define ORANGE_LED 4

File myFile;
String DEFAULT_FILE_NAME = "inject.txt";

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  digitalWrite(ORANGE_LED, HIGH);

  if (!SD.begin(10)) {
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
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n') {
        processLine(line);
        line = "";
      } else if (m != '\r') {
        line += m;
      }
    }
    if (line.length() > 0) {
      processLine(line);
    }
    myFile.close();
  }

  Keyboard.end();
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void processLine(String line) {
  int spaceIndex = line.indexOf(" ");
  String command = (spaceIndex == -1) ? line : line.substring(0, spaceIndex);
  String parameters = (spaceIndex == -1) ? "" : line.substring(spaceIndex + 1);

  if (command.equals("STRING")) {
    typeString(parameters);
  } else if (command.equals("DELAY")) {
    int delayTime = parameters.toInt();
    delay(delayTime);
  } else if (command.equals("REM")) {
    // Komentár
  } else {
    // Pridajte ďalšie príkazy podľa potreby
  }

  Keyboard.releaseAll();
}

void typeString(String text) {
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);
    // Mapovanie slovenských znakov na HID kódy
    switch (c) {
      case 'á':
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('a');
        delay(5);
        Keyboard.releaseAll();
        break;
      // Pridajte ďalšie znaky podľa potreby
      default:
        Keyboard.write(c);
        break;
    }
    delay(5);
  }
}