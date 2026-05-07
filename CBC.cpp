#include <iostream>
#include <string>
#include "BackEnd/Language/CBCLanguage.cpp"

//on startup, select between active translation or file reading
///TODO: Live translation
///TODO: File reading
int main(){
    std::string userInput;
    CBC CBC;

    ///TODO: maybe add trim spaces
    //Trim leading/trailing whitespace
    std::string trimInput(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));

    while(true){
        //selection
        std::cout << "Select useage by entering number:" << "\n"
                << "0. Exit" << "\n"
                << "1. Live Translation" << "\n"
                << "2. Read File" 
                    << std::endl;

        std::getline(std::cin, userInput);
        userInput = trimInput(userInput);

        if (userInput == "0"){
            std::cout << "Exiting Controller Live..." << std::endl;
            exit(0);
        }
         else if (userInput == "1"){
            std::cout << "Starting Live Translation Mode..." << std::endl;
            runControllerInput(); 
            //runControllerInput() contains its own while(true) loop
        }
        else if (userInput == "2") {
            //TODO File Reading Done
            std::cout << "input file name:";
            std::getline(std::cin, userInput);
            userInput = trimInput(userInput);

            if (!userInput.empty()) {
                cbcProcessor.runFile(userInput); 
                std::cout << "\nFile processing and compilation complete." << std::endl;
            } else {
                std::cout << "Error: File name cannot be empty." << std::endl;
            }
            
            // --- TODO: think of something better (COMPLETED) ---
            // Instead of an infinite loop, we let the main loop continue 
            // so the user can process another file or switch to Live mode.
            std::cout << "Returning to main menu..." << std::endl;
        } 
        else {
            std::cout << "Invalid input detected, please try again." << std::endl;
        }
    }
    return 0;
}
