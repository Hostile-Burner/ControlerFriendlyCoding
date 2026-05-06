#include <string>
#include <windows.h>

class KEYBOARD{
    private:

    public:
        ///TODO: Handles raw inputs, such as movement, enter, backspace, space
        void inputController (WORD virtualKey){
            INPUT input = { 0 };
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = virtualKey;

            // Press Key
            SendInput(1, &input, sizeof(INPUT));

            // Release Key
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
    }


        ///TODO: handle converted CBC string to keyboard input
        void inputString(std::string input){
            if (input.empty()) return;

            for (char ch : input) {
            INPUT inputs[2] = { 0 };

            // Key Down (using Unicode)
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wScan = ch;
            inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

            // Key Up
            inputs[1] = inputs[0];
            inputs[1].ki.dwFlags |= KEYEVENTF_KEYUP;

            SendInput(2, inputs, sizeof(INPUT));
        }
    }
};