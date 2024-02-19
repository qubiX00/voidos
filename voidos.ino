#include <M5Cardputer.h>

int page = 1;
int app = 0;

int settingsPointer = 1;

int timeMin = 0;
int timeHour = 0;

bool isAppActive = false;
bool timeActive = true;

String osname = "voidOS";
String osver = "b1902";

void setup() {

  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextFont(&fonts::FreeSans18pt7b);
  M5Cardputer.Display.setTextColor(WHITE);

  displayPage();
}

void loop() {
  M5Cardputer.update();
  
  static unsigned long lastTaskTime = 0;
  const unsigned long interval = 60000;

  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);


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

  if (timeMin == 59) {
    timeMin = -1;
    timeHour++;
  }

  if (timeHour == 23) {
    timeHour = -1;
    timeMin = 0;
  }

  if (M5Cardputer.Keyboard.isChange()) {
  if (M5Cardputer.Keyboard.isKeyPressed(',') && !isAppActive) {
    M5Cardputer.Speaker.tone(3000, 40);
    pagePrev();
  } else if (M5Cardputer.Keyboard.isKeyPressed('/') && !isAppActive) {
    M5Cardputer.Speaker.tone(3000, 40);
    pageNext();
  } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && page == 2 && !isAppActive) {
    M5Cardputer.Speaker.tone(3850, 40);
    isAppActive = true;
    app = 1;
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed(';') && isAppActive && app == 1) {
    M5Cardputer.Speaker.tone(3000, 40);
    settingsUp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('.') && isAppActive && app == 1) {
    M5Cardputer.Speaker.tone(3000, 40);
    settingsDown();
  } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 1 && settingsPointer == 1) {
    M5Cardputer.Speaker.tone(3850, 40);
    timeActive = false;
    app = 2;
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('`') && isAppActive && app == 2) {
    M5Cardputer.Speaker.tone(2000, 40);
    app = 1;
    settingsPointer = 1;
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('e') && isAppActive && app == 2) {
    // hour + 1
    timeHour++;
    M5Cardputer.Speaker.tone(3000, 40);
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('s') && isAppActive && app == 2) {
    // hour - 1
    if (timeHour == 0) {

    } else {
      timeHour--;
    }
    M5Cardputer.Speaker.tone(2400, 40);
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('y') && isAppActive && app == 2) {
    // min + 1
    timeMin++;
    M5Cardputer.Speaker.tone(3000, 40);
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('g') && isAppActive && app == 2) {
    // min - 1
    if (timeMin == 0) {

    } else {
    timeMin--;
    }
    M5Cardputer.Speaker.tone(2400, 40);
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 2) {
    // accept changes
    timeActive = true;
    app = 1;
    settingsPointer = 1;
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) && isAppActive && app == 1 && settingsPointer == 2) {
    M5Cardputer.Speaker.tone(3850, 40);
    app = 3;
    displayApp();
  } else if (M5Cardputer.Keyboard.isKeyPressed('`') && isAppActive && app == 3) {
    M5Cardputer.Speaker.tone(2000, 40);
    app = 1;
    settingsPointer = 1;
    displayApp();
  }
}

  if (M5Cardputer.BtnA.wasPressed()) {
    goHomescreen();
  }
}

void settingsDown() {
  if (settingsPointer == 2) {
    settingsPointer = 1;
    displayApp();
  } else {
    settingsPointer++;
    displayApp();
  }
}

void settingsUp() {
  if (settingsPointer == 1) {
    settingsPointer = 2;
    displayApp();
  } else {
    settingsPointer--;
    displayApp();
  }
}

void goHomescreen() {
  if (app == 2 && !timeActive) {
  M5Cardputer.Speaker.tone(2000, 40);
  } else {
  M5Cardputer.Speaker.tone(2000, 40);
  isAppActive = false;
  page = 1;
  app = 0;
  displayPage();
  }
}

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

void displayTime() {
  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  M5Cardputer.Display.setTextSize(2);
  if (timeMin < 10) {
    M5Cardputer.Display.drawString(strTimeHour + ":0" + strTimeMin, 45, 45);
  } else {
    M5Cardputer.Display.drawString(strTimeHour + ":" + strTimeMin, 45, 45); }
}

void displayPage() {
  switch (page) {
    case 1: 
        M5Cardputer.Display.clear();
        M5Cardputer.Display.fillScreen(BLACK);
        M5Cardputer.Display.setTextSize(2);
        displayTime();
        break;
    case 2:
        M5Cardputer.Display.clear();
        M5Cardputer.Display.fillScreen(BLACK);
        M5Cardputer.Display.setTextSize(1.5);
        M5Cardputer.Display.drawString("Settings", 30, 45);
        break;
  }
}

void displayApp() {
  String strTimeMin = String(timeMin);
  String strTimeHour = String(timeHour);

  switch (app) {
    case 1:
        M5Cardputer.Display.clear();
        M5Cardputer.Display.fillScreen(BLACK);
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
        M5Cardputer.Display.drawString(strTimeHour + ":" + strTimeMin, 75, 40); }
        }
        if (settingsPointer == 2) {
        M5Cardputer.Display.drawString("> System info...", 5, 65); } else {
          M5Cardputer.Display.drawString("System info...", 5, 65);
        }
        break;
    case 2:
        M5Cardputer.Display.clear();
        M5Cardputer.Display.fillScreen(BLACK);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.drawString("Set time...", 5, 5);
        M5Cardputer.Display.setTextSize(0.75);
        displayTime();
        break;
    case 3:
        M5Cardputer.Display.clear();
        M5Cardputer.Display.fillScreen(BLACK);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.drawString("System info...", 5, 5);
        M5Cardputer.Display.setTextSize(0.75);
        M5Cardputer.Display.drawString("OS: " + osname, 5, 40);
        M5Cardputer.Display.drawString("v" + osver, 5, 65);
        break;
  }
}