#include <fstream>
#include <iostream>
#include <sstream>

int main(){
    std::ifstream file;
    std::string line;
    file.open("words_alpha.txt");
    if(!file.is_open()){
        return 1;
    }
    int vowelLength [12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int consonantLength [12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ctrPos = 0;
    int ctrChar = 0;
    int state = 0;

    while(std::getline(file, line)){
        ctrPos = 0;
        ctrChar = 0;
        state = 0;
        for(char c : line){
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                if(state == 2){
                    consonantLength[ctrChar]++;
                    ctrChar = 0;
                }
                ctrChar ++;
                state = 1;
            } else if(c == ' ' || c == '\r'){
                if(state == 1){
                    if (ctrChar < 12) {
                        vowelLength[ctrChar]++;
                    }
                    ctrChar = 0;
                    state = 0;
                } else if(state == 2){
                    if (ctrChar < 12) {
                        consonantLength[ctrChar]++;
                    }
                    ctrChar = 0;
                    state = 0;
                }
            } else{
                if(state == 1){
                    if (ctrChar < 12) {
                        vowelLength[ctrChar]++;
                    }
                    ctrChar = 0;
                }
                ctrChar ++;
                state = 2;
            }
        }
        if(state == 1){
            if (ctrChar < 12) {
                vowelLength[ctrChar]++;
            }
            ctrChar = 0;
            state = 0;
        } else if(state == 2){
            if (ctrChar < 12) {
                consonantLength[ctrChar]++;
            }
            ctrChar = 0;
            state = 0;
        }
    }
    file.close();

    for(int i = 0; i < 12; i++){
        if(vowelLength[i] != 0){
            std::cout << "v " << i << " = " << vowelLength[i] << std::endl;
        }
    }
    for(int i = 0; i < 12; i++){
        if(consonantLength[i] != 0){
            std::cout << "c " << i << " = " << consonantLength[i] << std::endl;
        }
    }

    return 0;
}