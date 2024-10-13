# ProMicro
Code for make DIY Rubber Ducky lacno

# Connection
## Pro Micro -> SD Card Module
- VCC -> VCC
- GND -> GND
- D14 MISO
- D16 MOSI
- D15 SCK
- D10 CS (or SS)
## LED Diodes
- GREEN_LED (Through 220 ohm Resistor) D3
- LED_ORANGE (Through 220 ohm Resistor) D4

# Commands
- STRING <Something to type on keyboard>
- DELAY <Time in miliseconds like 2000>
- REM (this is just comment for better understand what will be happened)
- GUI Keys like : GUI,CTRL, SPACE ...

# Example Code (or u can use inject.txt file)
- GUI r
- DELAY 100
- STRING Hello this is test
- DELAY 1000
- ENTER
- REM This is just COMMENT Test 123
- Mouse_Move_LEFT 30
- DELAY 1000
- Mouse_Move_RIGHT 30
- DELAY 1000
- Mouse_Move_UP 30
- DELAY 1000
- Mouse_Move_DOWN 30
- DELAY 1000
- Mouse_Click_LEFT
- DELAY 1000
- Mouse_Click_RIGHT

