#include "ToggleButton.h"

void mz::ToggleButton::safeCall(void (*callback)(int), int arg) {
    if(callback != nullptr) { callback(arg); }
}


mz::ToggleButton::ToggleButton(
    int pin,
    int (*buttonSignalSupplier)(int pin), 
    void (*toggleCallback)(int),
    void (*pressCallback)(int),
    void (*releaseCallback)(int)
) :     
    pin{pin},
    toggleOn{false}, 
    pressCount{0}, 
    buttonRead{0},
    buttonSignalSupplier{buttonSignalSupplier},
    toggleCallback{toggleCallback},
    pressCallback{pressCallback},
    releaseCallback{releaseCallback} {}


mz::ToggleButton::ToggleButton() : 
    pin{-1},
    toggleOn{false}, 
    pressCount{0}, 
    buttonRead{0},
    buttonSignalSupplier{nullptr},
    toggleCallback{nullptr},
    pressCallback{nullptr},
    releaseCallback{nullptr} {}
    

mz::ToggleButton::ToggleButton(ToggleButton &other) : 
    pin{other.pin},
    toggleOn{other.toggleOn}, 
    pressCount{other.pressCount}, 
    buttonRead{other.buttonRead},
    buttonSignalSupplier{other.buttonSignalSupplier},
    toggleCallback{other.toggleCallback},
    pressCallback{other.pressCallback},
    releaseCallback{other.releaseCallback} {}


void mz::ToggleButton::update() {
    // Reads signal from putton
    buttonRead = this->buttonSignalSupplier(pin);

    // Button was NOT being pressed and NOW it IS PRESSED
    if(!toggleOn && buttonRead) {
        toggleOn = true;
        pressCount++;
        safeCall(toggleCallback, pressCount);
    }

    // Button WAS pressed and NOW it is RELEASED
    if(toggleOn && !buttonRead) { toggleOn = false; }


    if (buttonRead) { safeCall(pressCallback, pressCount); } 
    else            { safeCall(releaseCallback, pressCount);}
}

int mz::ToggleButton::getPressCount() {
    return this->pressCount;
}

int mz::ToggleButton::buttonPressed() {
    return buttonRead;
}
