#include <fstream>
#include <iostream>
#include <sstream>


int main(){
    std::ifstream file;
    std::string line;
    std::string fileName;
    std::cout << "Input name of file: ";
    std::cin >> fileName;
    file.open("../data/" + fileName + ".txt");
    if(!file.is_open()){
        return 1;
    }

    unsigned int letterFrequency [26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    while(std::getline(file, line)){
        for(int i = 0; i < line.length(); i++){
            if(122 >= (int)line[i] && (int)line[i] >= 97){
                letterFrequency[(int)line[i] - 97]++;
            } else if(90 >= (int)line[i] && (int)line[i] >= 65){
                letterFrequency[(int)line[i] + 32 - 97]++;
            }
        }
    }
    file.close();
    for(int i = 0; i < 26; i++){
        if(letterFrequency[i] != 0){
            //std::cout << (char) ('a' + i)  << " = ";
            std::cout << letterFrequency[i] << std::endl;
        }
    }

    return 0;
}