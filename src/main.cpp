// Include Libraries
#include <Arduino.h>

// Include Custom Header Files
#include "IRprogramming.h"
#include "OLED.h"

// Setup Pins
#define IR_LED 16
#define IR_RECV_DATA 18
#define IR_RECV_VCC 19
#define ACCELEROMETER_SDA 20
#define ACCELEROMETER_SCL 21
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_VCC 23
#define ENCODER_A 23
#define ENCODER_B 24

// Define Button Pins
struct Button {
  const char* name;
  bool isPressed;
  unsigned long lastPressed;
  int pin;
};

Button buttons[] = {
  {"BUTTON_POWER", false, 0, 2},
  {"BUTTON_INPUT", false, 0, 3},

  {"BUTTON_RED", false, 0, 4},
  {"BUTTON_GREEN", false, 0, 5},
  {"BUTTON_YELLOW", false, 0, 6},
  {"BUTTON_BLUE", false, 0, 7},

  {"BUTTON_UP", false, 0, 8},
  {"BUTTON_DOWN", false, 0, 9},
  {"BUTTON_RIGHT", false, 0, 10},
  {"BUTTON_LEFT", false, 0, 11},
  {"BUTTON_SELECT", false, 0, 12},

  {"BUTTON_N", false, 0, 13},
  {"BUTTON_NE", false, 0, 14},
  {"BUTTON_E", false, 0, 15},
  {"BUTTON_SE", false, 0, 16},
  {"BUTTON_S", false, 0, 17},
  {"BUTTON_SW", false, 0, 18},
  {"BUTTON_W", false, 0, 19},
  {"BUTTON_NW", false, 0, 20},

  {"BUTTON_1", false, 0, 21},
  {"BUTTON_2", false, 0, 22},
  {"BUTTON_3", false, 0, 23},
  {"BUTTON_4", false, 0, 24},
  {"BUTTON_5", false, 0, 25},
  {"BUTTON_6", false, 0, 26},
  {"BUTTON_7", false, 0, 27},
  {"BUTTON_8", false, 0, 28},
  {"BUTTON_9", false, 0, 29},
  {"BUTTON_0", false, 0, 30},

  {"BUTTON_SHORTCUT_1", false, 0, 31},
  {"BUTTON_SHORTCUT_2", false, 0, 32},
  {"BUTTON_SHORTCUT_3", false, 0, 33},
  {"BUTTON_SHORTCUT_4", false, 0, 34},
};

// Define Global Variables
const unsigned long LONG_PRESS_TIME = 3000;

// Function Declarations

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize Remote
  setupIRReceiver(IR_RECV_VCC, IR_RECV_DATA);
  setupOLED(OLED_VCC, OLED_SCL, OLED_SDA);

  // // Initialize Buttons
  // for (Button& button : buttons) {
  //   pinMode(button.pin, INPUT_PULLUP);
  // }

  bootAnimation();
}

void loop() {
  // // Check state for each button
  // for (Button& button : buttons) {

  //   // If the button is currently pressed
  //   if (digitalRead(button.pin) == LOW) {
  //     // If the button was just pressed
  //     if (!button.isPressed) {
  //       button.lastPressed = millis();
  //       button.isPressed = true;
  //     } 
      
  //     // If the button has been pressed
  //     else {
  //       // Has the button been pressed for an alotted time?
  //       if (millis() - button.lastPressed >= LONG_PRESS_TIME) {
  //         Serial.print(button.name);
  //         Serial.println(" long pressed!");
  //         delay(200);
  //       }
  //     }
  //   }
    
  //   // If the button is not currently pressed
  //   else {
  //     // If the button has been pressed
  //     if (button.isPressed) {
  //       // Was the button press quick?
  //       if (millis() - button.lastPressed < LONG_PRESS_TIME) {
  //         Serial.print(button.name);
  //         Serial.println(" short pressed");
  //       }
  //       button.isPressed = false;
  //     }
  //   }
  // }
}

// put function definitions here:
