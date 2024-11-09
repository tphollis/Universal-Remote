#ifndef IR_PROGRAMMING_H
#define IR_PROGRAMMING_H

// Include Libraries
#include <Arduino.h>

// Define Pins
extern int IR_RECV_DATA;
extern int IR_RECV_VCC;

// Function Declarations
void setupIRReceiver(int vcc, int data);
void enableIRReceiver();
void disableIRReceiver();
void programRemoteIR();

#endif

