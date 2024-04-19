# ProMicro
Code for make DIY Rubber Ducky lacno

# Connection
- VCC -> VCC na SD karte
- GND -> GND na SD karte
- D14 (MISO) -> MISO na SD karte
- D16 (MOSI) -> MOSI na SD karte
- D15 (SCK) -> SCK na SD karte
- D10 (SS) -> CS na SD karte

# Commands
- STRING <Something to type on keyboard>
- DELAY <Time in miliseconds like 2000>
- REM (this is just comment for better understand what will be happened)
- GUI Keys like : GUI,CTRL, SPACE ...

# EXAMPLE
GUI r
DELAY 100
STRING Hello this is test
DELAY 1000
ENTER
