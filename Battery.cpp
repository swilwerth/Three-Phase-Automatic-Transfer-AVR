#include "Battery.h"
#include <Arduino.h>

void Battery::setup() {
    batTimer.setS(BATSAMP);
    batTimer.reset();
}

Battery::Battery() {
    setup();
}

bool Battery::alarm() {
    bool error = false;
    if(vBat <= MINIMAL_V_LEVEL) 
        error = true;
    return error;
}

void Battery::check() {
    int aux = analogRead(VBATPIN);
    vBat = 16.0 * (float) aux / 1023.0;
    logValue();
}

void Battery::logAlarm() {
    manSerial.print("vBat LOW!\n");
}


void Battery::logValue() {
    manSerial.print("vBat: ");
    manSerial.print(vBat);  
    manSerial.print("\n");  
}

void Battery::update() {
    if(batTimer.event()) {
        check();
        if(alarm())
            logAlarm();
        batTimer.reset();
    }
    batTimer.update();
}
