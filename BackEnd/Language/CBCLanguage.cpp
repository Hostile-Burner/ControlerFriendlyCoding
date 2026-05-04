#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

class CBC {
    private:
    std::unordered_map<int, std::string> env;

    //used to trim extra spaces
    std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) ++start;
        auto end = str.end();
        do { --end; } while (end != start && std::isspace(*end));
        return std::string(start, end + 1);
    }

    //translate raw inputs into readable language
    std::string translate(std::string input){
        if (input.empty()) return "";
        
        //Identifies the category from the first character
        char category = input[0];
        //Extract the jostick degrees
        int degrees = std::stoi(input.substr(1));

        if (category == 'c') { 
            if (degrees < 90) return "if (";
            if (degrees >= 90 && degrees <180) return "loop ";
        }
        else if (category == 'n') {
            //Converts degree range to a specific number of variable identity
            return "2";
        }
        else if (category == 'e') {
            return ") {";
        }
        else if (category == 's') {
            return "}" ;
        }
        return input; 
    }
    void run(std::string input){
        // run calls 'translate' to convert "c024" into "if ("
        std::string translatedCode = translate(input);

        std::cout<< "Executing: " << translatedCode << std::endl;
    }

    public:
    void runLive(){

    }
    void runFile(std::string fileName){
        std::ifstream file(fileName);
        
        if (!file.is_open()) {
            std::cerr << "Error: Could not open " << fileName <<"." << std::endl;
            return;
        }

        std::string line;
        //loop each line in file till end of file
        while (std::getline(file, line)){
            run(trim(line));
        }

        file.close();
        return;
    }
};
