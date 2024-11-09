// Include Header File
#include "IRprogramming.h"
#include <IRremote.hpp>

// Define Global Variables
int IR_RECV_DATA;
int IR_RECV_VCC;

// Function Definitions
void setupIRReceiver(int vcc, int data) {
    // Define IR receiver pins
    IR_RECV_VCC = vcc;
    IR_RECV_DATA = data;

    // Map IR receiver pins
    pinMode(IR_RECV_VCC, OUTPUT);
    pinMode(IR_RECV_DATA, INPUT);

    // Initialize IR receiver disabled
    disableIRReceiver();

    Serial.println("IR Receiver Setup");
}

void enableIRReceiver() {
    digitalWrite(IR_RECV_VCC, HIGH);
    IrReceiver.begin(IR_RECV_DATA, ENABLE_LED_FEEDBACK);
    Serial.println("IR Receiver Enabled");
}

void disableIRReceiver() {
    digitalWrite(IR_RECV_VCC, LOW);
    IrReceiver.stop();
    Serial.println("IR Receiver Disabled");
}

void programRemoteIR() {
    // Read the IR signal
    if (IrReceiver.decode()) {
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRResultRawFormatted(&Serial, true);

        IrReceiver.resume();
        delay(100);
    }
}