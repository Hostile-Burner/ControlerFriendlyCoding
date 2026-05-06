#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <windows.h>
#include "Categories.cpp"
#include "CInputToCBC.cpp" 

class CBC {
    private:
        std::unordered_map<int, std::string> env;
        Category cat;

        // Helper to simulate keyboard typing
        void sendKeyboardOutput(const std::string& text) {
            for (char c : text) {
                INPUT input = {0};
                input.type = INPUT_KEYBOARD;
                input.ki.wVk = 0;
                input.ki.wScan = c;
                input.ki.dwFlags = KEYEVENTF_UNICODE;
                SendInput(1, &input, sizeof(INPUT));

                input.ki.dwFlags |= KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(INPUT));
            }
        }

        //used to trim extra spaces
        std::string trim(const std::string& str) {
            if (str.empty()) return str;   
            auto start = str.begin();
            while (start != str.end() && std::isspace(*start)) ++start;
            auto end = str.end();
            if (start == end) return "";
            do { --end; } while (end != start && std::isspace(*end));
            return std::string(start, end + 1);
        }
        template <typename T>
        std::string toString(const T& value) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }

        // Translates tokens like "n045" into the actual character
        std::string translate(std::string input) {
            if (input.length() < 4) return "";
            return toString(cat.getCat(input[0], input.substr(1)));
        }
        
        std::string run(std::string input) {
            std::string translatedLine = "";
            while(!input.empty()) {
                
                // Handle leading spaces
                if (std::isspace(input.front())) {
                    input.erase(0, 1);
                    continue;
                }

                // Translate 4-character tokens :'''###'
                if (input.length() >= 4) { 
                    translatedLine.append(translate(input.substr(0, 4)));
                    input.erase(0, 4);
                } else {
                    input.clear();
                }
            }
            return translatedLine;
        }

    public:
        ///TODO: take input from controller handler
        void runLive(std::string token) {
            if (token.empty()) return;
            std::string output = translate(token);[cite: 9]
            if (!output.empty()) {
                sendKeyboardOutput(output); 
            }
        }

        // Logic for Backspace (assigned to Button 3/Square/X)
        void sendBackspace() {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_BACK; 
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

        // Logic for Enter/New Line (assigned to Button 2/Circle/B)
        void sendEnter() {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_RETURN; 
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }

        // Processes a full string of tokens from a file
        std::string run(std::string input) {
            std::string translatedLine = "";
            while(!input.empty()) {
                if (std::isspace(input.front())) {
                    input.erase(0, 1);
                    continue;
                }
                // Tokens are 1 char prefix + 3 char degree
                if (input.length() >= 4) { 
                    translatedLine.append(translate(input.substr(0, 4)));[cite: 9]
                    input.erase(0, 4);
                } else {
                    input.clear();
                }
            }
            return translatedLine;
        }

       void runFile(std::string fileName, std::string extension = ".cpp") {
            std::ifstream fileIn(fileName);
            
            if (!fileIn.is_open()) {
                std::cerr << "Error: Could not open " << fileName <<"." << std::endl;
                exit(1);
            }

            ///TODO: replace ".cpp" with input from controller handler to select any language
            fileName = fileName.substr(0, fileName.find_last_of('.')) + ".cpp";
            std::ofstream fileOut;
            fileOut.open(fileName, std::ios::out);

            std::string line;
            //loop each line in file till end of file
            while (std::getline(fileIn, line)){
                fileOut << run(trim(line)) << std::endl;
            }
            fileIn.close();
            fileOut.close();

            ///TODO: add to dump the files with the inputfile location
            std::cout << "Source translated to: " << outputFileName << std::endl;
           
            //Compiles a .exe to run the file output
            std::string compile = "cl \"" + fileName + "\"";
            if (system(compile.c_str()) != 0) {
                std::cerr << "Compile failed." << std::endl;
                exit(1);
            }
            //executes .exe
            std::string exeName = ".\\" + outputFileName.substr(0, outputFileName.find_last_of('.')) + ".exe";
            std::cout << "Executing: " << exeName << std::endl;
            system(exeName.c_str());
        }
};
