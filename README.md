# voidos
Feature packed OS for M5Stack Cardputer

# requirements
- M5Stack Cardputer
- SD Card
- Arduino IDE and libraries: M5Cardputer
- M5Launcher firmware installed on M5Stack Cardputer

# installation
## 1st method
Download voidos.ino and open it in Arduino IDE. Go to Tools > Board and select M5Stack > M5StampS3. Then Go to Sketch > Export Compiled Binary and wait until it finishes. After that go to Sketch > Show sketch folder, then go to build/m5stack.esp32.m5stack_stamp_s3 and there should be a file called stopwatch-cardputer.ino.bin. Put it on your SD Card, then put the SD Card in your M5Stack Cardputer and launch it from the M5Launcher. That's pretty much it, enjoy!

## 2nd method
Go to the Releases tab and download voidos.bin. Put it on the SD Card, then put the SD Card in your M5Stack Cardputer and launch it from the M5Launcher.

You can also flash it directly onto your M5Cardputer, but at the time of writing this, it's not recommended

# navigation
Main menu:
Navigate with < > (left/right arrow keys)
There are 2 pages (atm):
- Main page (Clock)
- Settings page
You can press Enter on Settings page to open settings
In settings:
- Navigate with up/down arrow keys
- Press Enter to enter submenu
- Press Esc in submenu to go back to settings' main menu
In settings/set time:
- Press E/S to +/- Hours
- Press Y/G to +/- Minutes
- Press Enter to accept
BtnGO will (almost always take you to homescreen)
