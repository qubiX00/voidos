#include <M5Cardputer.h>

int page = 1;
int app = 0;

// for settings/personalize

// 0 = dark, 1 = light
int personalizeTheme = 0;

// 0 = none, 1 = BatLevel
int personalizeHsWidget = 0;

// menu pointers
int settingsPointer = 1;
int appDrawerPointer = 1;
int personalizePointer = 1;

// for time
int timeMin = 0;
int timeHour = 0;

// booleans
bool isAppActive = false;
bool timeActive = true;

// os info
String osname = "voidOS";
String osver = "b2102";

// debounce delay
const unsigned long debounceDelay = 20;
unsigned long lastDebounceTime = 0;

void setup() {

  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextFont(&fonts::FreeSans18pt7b);
  if (personalizeTheme == 0) {
    M5Cardputer.Display.setTextColor(WHITE);
    M5Cardputer.Display.fillScreen(BLACK);
  } else {
    M5Cardputer.Display.setTextColor(BLACK);
    M5Cardputer.Display.fillScreen(WHITE);
  }

  displayPage();
}

void loop() {
  M5Cardputer.update();

  static unsigned long lastTaskTime = 0;
  const unsigned long interval = 60000;

  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  // clock
  if (millis() - lastTaskTime >= interval && timeActive) {
    timeMin++;
    lastTaskTime = millis();
    if (page == 1 && !isAppActive) {
      displayPage();
    } else if (page != 1 && isAppActive) {
      switch (app) {
        case 1:
          displayApp();
      }
    }
  }

  if (timeMin > 59) {
    timeMin = 0;
    timeHour++;
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  }

  if (timeHour > 23) {
    timeHour = 0;
    timeMin = 0;
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  }

  // for keyboard
  if (M5Cardputer.Keyboard.isChange()) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastDebounceTime >= debounceDelay) {
      if (M5Cardputer.Keyboard.isKeyPressed(',') && !isAppActive) {
        // go left in home
        M5Cardputer.Speaker.tone(3000, 40);
        pagePrev();
      } else if (M5Cardputer.Keyboard.isKeyPressed('/') && !isAppActive) {
        // go right in home
        M5Cardputer.Speaker.tone(3000, 40);
        pageNext();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && page == 2 && appDrawerPointer == 1 && !isAppActive) {
        // start settings
        M5Cardputer.Speaker.tone(3850, 40);
        isAppActive = true;
        app = 1;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(';') && isAppActive && app == 1) {
        // settings pointer up
        M5Cardputer.Speaker.tone(3000, 40);
        settingsUp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('.') && isAppActive && app == 1) {
        // settings pointer down
        M5Cardputer.Speaker.tone(2400, 40);
        settingsDown();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 1 && settingsPointer == 1) {
        // go to setting time
        M5Cardputer.Speaker.tone(3850, 40);
        timeActive = false;
        app = 2;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('`') && isAppActive && app == 2) {
        // go back by pressing esc is disabled when changing time
        M5Cardputer.Speaker.tone(2000, 40);
      } else if (M5Cardputer.Keyboard.isKeyPressed('e') && isAppActive && app == 2) {
        // changing time: hour + 1
        timeHour++;
        M5Cardputer.Speaker.tone(3000, 40);
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('s') && isAppActive && app == 2) {
        // changing time: hour - 1
        if (timeHour == 0) {

        } else {
          timeHour--;
        }
        M5Cardputer.Speaker.tone(2400, 40);
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('y') && isAppActive && app == 2) {
        // changing time: min + 1
        timeMin++;
        M5Cardputer.Speaker.tone(3000, 40);
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('g') && isAppActive && app == 2) {
        // changing time: min - 1
        if (timeMin == 0) {

        } else {
          timeMin--;
        }
        M5Cardputer.Speaker.tone(2400, 40);
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 2) {
        // changing time: accept changes
        M5Cardputer.Speaker.tone(3850, 40);
        timeActive = true;
        app = 1;
        settingsPointer = 1;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 1 && settingsPointer == 2) {
        M5Cardputer.Speaker.tone(3850, 40);
        app = 3;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 1 && settingsPointer == 3) {
        // go to system info
        M5Cardputer.Speaker.tone(3850, 40);
        app = 4;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('`') && isAppActive && app == 4) {
        // go back to main settings menu from system info
        M5Cardputer.Speaker.tone(2000, 40);
        app = 1;
        settingsPointer = 1;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(';') && !isAppActive && page == 2) {
        M5Cardputer.Speaker.tone(3000, 40);
        appDrawerUp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('.') && !isAppActive && page == 2) {
        M5Cardputer.Speaker.tone(2400, 40);
        appDrawerDown();
      } else if (M5Cardputer.Keyboard.isKeyPressed('`') && isAppActive && app == 3) {
        // go back to settings main menu from system info
        M5Cardputer.Speaker.tone(2000, 40);
        app = 1;
        settingsPointer = 1;
        displayApp();
      } else if (M5Cardputer.Keyboard.isKeyPressed(';') && isAppActive && app == 3) {
        // personalize pointer up
        M5Cardputer.Speaker.tone(3000, 40);
        sPersonalizeUp();
      } else if (M5Cardputer.Keyboard.isKeyPressed('.') && isAppActive && app == 3) {
        // personalize pointer down
        M5Cardputer.Speaker.tone(2400, 40);
        sPersonalizeDown();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 3 && personalizePointer == 1) {
        // switching theme
        M5Cardputer.Speaker.tone(3850, 40);
        switchTheme();
      } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 3 && personalizePointer == 2) {
        // switching homescreen widget
        M5Cardputer.Speaker.tone(3850, 40);
        switchHsWidget();
      }
      lastDebounceTime = currentMillis;
    }
  }

  if (M5Cardputer.BtnA.wasPressed()) {
    goHomescreen();
  }
}

void switchHsWidget() {
  if (personalizeHsWidget <= 0) {
    personalizeHsWidget++;
    
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  } else {
    personalizeHsWidget = 0;
    
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  }
}



void switchTheme() {
  if (personalizeTheme == 0) {
    personalizeTheme = 1;
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  } else {
    personalizeTheme = 0;
    if (isAppActive) {
      displayApp();
    } else {
      displayPage();
    }
  }
}

// control settings/personalize
void sPersonalizeDown() {
  if (personalizePointer == 2) {
    personalizePointer = 1;
    displayApp();
  } else {
    personalizePointer++;
    displayApp();
  }
}

void sPersonalizeUp() {
  if (personalizePointer == 1) {
    personalizePointer = 2;
    displayApp();
  } else {
    personalizePointer--;
    displayApp();
  }
}

// control app drawer
void appDrawerDown() {
  if (appDrawerPointer == 5) {
    appDrawerPointer = 1;
    displayPage();
  } else {
    appDrawerPointer++;
    displayPage();
  }
}

void appDrawerUp() {
  if (appDrawerPointer == 1) {
    appDrawerPointer = 5;
    displayPage();
  } else {
    appDrawerPointer--;
    displayPage();
  }
}

// control settings
void settingsDown() {
  if (settingsPointer == 3) {
    settingsPointer = 1;
    displayApp();
  } else {
    settingsPointer++;
    displayApp();
  }
}

void settingsUp() {
  if (settingsPointer == 1) {
    settingsPointer = 3;
    displayApp();
  } else {
    settingsPointer--;
    displayApp();
  }
}

void goHomescreen() {
  if (app == 2 && !timeActive) {
    // only make a sound when changing time to alert user that going to homescreen while changing time is not possible
    M5Cardputer.Speaker.tone(2000, 40);
  } else if (page == 1) {
    // do nothing when on homescreen
  } else {
    M5Cardputer.Speaker.tone(2000, 40);
    isAppActive = false;
    page = 1;
    app = 0;
    displayPage();
  }
}

// control pages
void pageNext() {
  if (page == 2) {
    page = 1;
    displayPage();
  } else {
    page++;
    displayPage();
  }
}

void pagePrev() {
  if (page == 1) {
    page = 2;
    displayPage();
  } else {
    page--;
    displayPage();
  }
}

void displayHsWidget() {
  if (page == 1 && !isAppActive) {
    if (personalizeHsWidget == 0) {
      // display nothing
    }
    if (personalizeHsWidget == 1) {
      int battLevel =  M5Cardputer.Power.getBatteryLevel();

    if (battLevel == 100) {
      String strBattLevel = String(battLevel); 
      M5Cardputer.Display.setTextSize(0.75);
      M5Cardputer.Display.drawString(strBattLevel + "%", 102, 95);
      } else {
      String strBattLevel = String(battLevel); 
      M5Cardputer.Display.setTextSize(0.75);
      M5Cardputer.Display.drawString(strBattLevel + "%", 98, 95);
      }
    }
    if (personalizeHsWidget == 2) {
    M5Cardputer.Display.setTextSize(0.75);
    M5Cardputer.Display.drawString("test", 102, 95);
    }
  }
}

void displayTime() {
  // turn ints into strings to put time into drawString() function
  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  M5Cardputer.Display.setTextSize(2);
  if (timeMin < 10) {
    if (timeHour < 10) {
      M5Cardputer.Display.drawString("0" + strTimeHour + ":0" + strTimeMin, 37, 37);
    } else {
      M5Cardputer.Display.drawString("" + strTimeHour + ":0" + strTimeMin, 37, 37);
    }
  } else {
    if (timeHour < 10) {
      M5Cardputer.Display.drawString("0" + strTimeHour + ":" + strTimeMin, 37, 37);
    } else {
      M5Cardputer.Display.drawString("" + strTimeHour + ":" + strTimeMin, 37, 37);
    }
  }
}

void displayPage() {
  switch (page) {
    case 1:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(2);
      displayTime();
      displayHsWidget();
      break;
    case 2:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(0.5);
      if (appDrawerPointer == 1) {
        M5Cardputer.Display.drawString("> Settings", 5, 5);
      } else {
        M5Cardputer.Display.drawString("Settings", 5, 5);
      }
      if (appDrawerPointer == 2) {
        M5Cardputer.Display.drawString("> Alarm", 5, 20);
      } else {
        M5Cardputer.Display.drawString("Alarm", 5, 20);
      }
      if (appDrawerPointer == 3) {
        M5Cardputer.Display.drawString("> Calculator", 5, 35);
      } else {
        M5Cardputer.Display.drawString("Calculator", 5, 35);
      }
      if (appDrawerPointer == 4) {
        M5Cardputer.Display.drawString("> Stopwatch", 5, 50);
      } else {
        M5Cardputer.Display.drawString("Stopwatch", 5, 50);
      }
      if (appDrawerPointer == 5) {
        M5Cardputer.Display.drawString("> To do", 5, 65);
      } else {
        M5Cardputer.Display.drawString("To do", 5, 65);
      }
      break;
  }
}

void displayApp() {
  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  switch (app) {
    case 1:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(1);
      M5Cardputer.Display.drawString("Settings", 5, 5);
      M5Cardputer.Display.setTextSize(0.75);
      if (settingsPointer == 1) {
        M5Cardputer.Display.drawString("> Time: ", 5, 40);
        if (timeMin < 10) {
          M5Cardputer.Display.drawString(strTimeHour + ":0" + strTimeMin, 95, 40);
        } else {
          M5Cardputer.Display.drawString(strTimeHour + ":" + strTimeMin, 95, 40);
        }
      } else {
        M5Cardputer.Display.drawString("Time: ", 5, 40);
        if (timeMin < 10) {
          M5Cardputer.Display.drawString(strTimeHour + ":0" + strTimeMin, 75, 40);
        } else {
          M5Cardputer.Display.drawString(strTimeHour + ":" + strTimeMin, 75, 40);
        }
      }
      if (settingsPointer == 2) {
        M5Cardputer.Display.drawString("> Personalize...", 5, 65);
      } else {
        M5Cardputer.Display.drawString("Personalize...", 5, 65);
      }
      if (settingsPointer == 3) {
        M5Cardputer.Display.drawString("> System info...", 5, 90);
      } else {
        M5Cardputer.Display.drawString("System info...", 5, 90);
      }
      break;
    case 2:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(1);
      M5Cardputer.Display.drawString("Set time...", 5, 5);
      M5Cardputer.Display.setTextSize(0.75);
      displayTime();
      break;
    case 3:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(1);
      M5Cardputer.Display.drawString("< Personalize...", 5, 5);
      M5Cardputer.Display.setTextSize(0.75);
      if (personalizePointer == 1) {
        if (personalizeTheme == 0) {
          M5Cardputer.Display.drawString("> Theme: Dark", 5, 40);
        } else {
          M5Cardputer.Display.drawString("> Theme: Light", 5, 40);
        }
      } else {
        if (personalizeTheme == 0) {
          M5Cardputer.Display.drawString("Theme: Dark", 5, 40);
        } else {
          M5Cardputer.Display.drawString("Theme: Light", 5, 40);
        }
      }
      if (personalizePointer == 2) {
        if (personalizeHsWidget == 0) {
        M5Cardputer.Display.drawString("> Widget: None", 5, 65);
        } else if (personalizeHsWidget == 1) {
        M5Cardputer.Display.drawString("> Widget: BatLevel", 5, 65);
        } else if (personalizeHsWidget == 2) {
        M5Cardputer.Display.drawString("> Widget: test", 5, 65);
        }
      } else {
        if (personalizeHsWidget == 0) {
        M5Cardputer.Display.drawString("Widget: None", 5, 65);
        } else if (personalizeHsWidget == 1) {
        M5Cardputer.Display.drawString("Widget: BatLevel", 5, 65);
        } else if (personalizeHsWidget == 2) {
        M5Cardputer.Display.drawString("Widget: test", 5, 65);
      }
      break;
    case 4:
      M5Cardputer.Display.clear();
      if (personalizeTheme == 0) {
        M5Cardputer.Display.setTextColor(WHITE);
        M5Cardputer.Display.fillScreen(BLACK);
      } else {
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.fillScreen(WHITE);
      }
      M5Cardputer.Display.setTextSize(1);
      M5Cardputer.Display.drawString("<  System info...", 5, 5);
      M5Cardputer.Display.setTextSize(0.75);
      M5Cardputer.Display.drawString("OS: " + osname, 5, 40);
      M5Cardputer.Display.drawString("v" + osver, 5, 65);
  }
}
} 