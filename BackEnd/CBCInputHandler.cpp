#include <iostream>
#include <string>
#include "Language/CBCLanguage.cpp"

//on startup, select between active translation or file reading
//TODO: Live translation
//TODO: File reading
int main(){
    std::string userInput;

    //selection
    std::cout << "Select useage by entering number:" << "\n"
              << "1. Live Translation" << "\n"
              << "2. Read File" 
              << std::endl;

    std::getline(std::cin, userInput);
    if(userInput == "1"){
        std::cout << "This usage has not been implemented, terminating program.";

    } else if (userInput == "2") {
        std::cout << "input file name:";
        std::getline(std::cin, userInput);

        runFile(userInput);
    } else {
        std::cerr << "Error: invalid input detected, restart program to select again.";
        return 1;
    }
    return 0;
}