#ifndef OLED_H
#define OLED_H

// Include Libraries
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Define Constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Define Pins
extern int OLED_VCC;
extern int OLED_SDA;
extern int OLED_SCL;

// Function Declarations
void setupOLED(int vcc, int scl, int sda);
void setOLEDPower(bool on);
void displayText(const char* text, int x, int y, int size = 1);
void clearDisplay();
void bootAnimation();
#endif

