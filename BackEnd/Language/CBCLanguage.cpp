#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

std::unordered_map<int, std::string> env;

void run(std::string input){
    
}
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
        run(line);
    }

    file.close();
    return;
}