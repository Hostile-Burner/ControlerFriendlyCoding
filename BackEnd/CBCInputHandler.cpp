#include <iostream>
#include <string>
#include <cmath>
#include "Language/CBCLanguage.cpp"

class CBCInput Handler {
public:
    // Converts joystick X/Y and an active button to DPS
    // identity: n, a, e, s, or c
    std::string processInput(char identity, float stickX, float stickY){
        // Calculate angle in radians, then convert to degrees 0-360
        float radians = std::atan2(stickY, stickX);
        int degrees = static_cast<int>(radians * 180.0 / M_PI);

        //Normalize to 0-360 range
        if (degrees < 0) degrees += 360;

        //Format to 3 digits
        std::string degreeStr = std::to_string(degrees);
        while (degreeStr.length() < 3) degreeStr = "0" + degreeStr;

        return identity + degreeStr;
    }
};
//on startup, select between active translation or file reading
//TODO: Live translation
//TODO: File reading
int main(){
    std::string userInput;
    CBC CBC;

    while(true){
        //selection
        std::cout << "Select useage by entering number:" << "\n"
                << "0. Exit" << "\n"
                << "1. Live Translation" << "\n"
                << "2. Read File" 
                << std::endl;

        std::getline(std::cin, userInput);
        if (userInput == "0"){
            return 0;
        } else if (userInput == "1"){
            std::cout << "This usage has not been implemented, terminating program.";

        } else if (userInput == "2") {
            std::cout << "input file name:";
            std::getline(std::cin, userInput);

            CBC.runFile(userInput); // send file name to language
        } else {
            std::cout << "invalid input detected, please try again." << std::endl;
            continue;
        }
        return 0;
    }
}
