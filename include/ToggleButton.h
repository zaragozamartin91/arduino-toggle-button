#ifndef TOGGLEBTN_H
#define TOGGLEBTN_H

namespace mz
{
    class ToggleButton {
        private:
            int pin; // pin of button signal
            bool toggleOn; // keeps track of toggling
            int pressCount; // counts total press count
            int buttonRead; // signal value
            int (*buttonSignalSupplier)(int pin); // Supplier of the button signal
            void (*toggleCallback)(int); // Action to execute when toggle happens
            void (*pressCallback)(int); // Action to execute while button is being pressed
            void (*releaseCallback)(int); // Action to execute while button is released

            void safeCall(void (*callback)(int), int arg);

        public:
            ToggleButton(
                int pin, // pin of button signal
                int (*buttonSignalSupplier)(int pin),  // supplier of button signal
                void (*toggleCallback)(int) = nullptr,  // function to invoke on toggle
                void (*pressCallback)(int) = nullptr, // function to call on press
                void (*releaseCallback)(int) = nullptr // function to call on release
            );

            /* Empty constructor used for array initialization */
            ToggleButton();

            /* Copy constructor */
            ToggleButton(ToggleButton& other);

            /* To be called on every loop cycle. @param buttonRead Value of button read. */
            void update();

            // returns press count
            int getPressCount();

            // returns current value of button signal
            int buttonPressed();
    };
} // namespace mz

#endif
