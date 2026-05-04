#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

class CBC {
    private:
    std::vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::vector<char> numbers = {'1','2','3','4','5','6','7','8','9','0'};
    std::vector<std::string> equations = {"=", "+", "-", "*", "/", "()"};
    std::vector<char> special = {' ', '!', '/', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '\"', ',', '<', '>', '.', '?'};
    std::vector<std::string> conditions = {"if ()", "else", "else if ()"};

    //used to trim extra spaces
    std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) ++start;
        auto end = str.end();
        do { --end; } while (end != start && std::isspace(*end));
        return std::string(start, end + 1);
    }

    //Map a degree 0-360 to an index in a vector
    template<typename T>
    T getFromWheel(int degrees, const std::vector<T>& vec) {
        if (vec.empty()) return T();
        int index = (degrees * vec.size()) / 361; 
        return vec[index];
    }
    //translate raw inputs into readable language
    std::string translate(std::string input){
        if (input.length() < 2) return "";

        char identity = input[0]; 
        int degrees = std::stoi(input.substr(1));

        switch (identity) {
            case 'n': return std::string(1, getFromWheel(degrees, numbers));
            case 'a': return std::string(1, getFromWheel(degrees, alphabet));
            case 'e': return getFromWheel(degrees, equations);
            case 's': return std::string(1, getFromWheel(degrees, special));
            case 'c': return getFromWheel(degrees, conditions);
            default: return "";
        }
    }

public:
    void run(std::string line) {
        //parser to split n120 a010 into tokens
        std::string  translatedLine = "";
        std::string currentToken = "";
        for (char c : line){
            if (c== ' '){
                translatedLine+= translate(currentToken);
                currentToken = "";
            } else {
                currentToken += c;
            }
        }
        translatedLine+= translate(currentToken);

        std::cout << "Executed: " <<translatedLine << std::endl;
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
