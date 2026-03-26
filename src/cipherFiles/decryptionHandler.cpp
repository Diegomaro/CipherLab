#include "decryptionHandler.hpp"

int probVowLength [6] = {100, 86, 65, 40, 15, 0};
int probConsLength [10] = {100, 95, 84, 73, 62, 48, 37, 27, 14, 5};



DecryptionHandler::DecryptionHandler(){
    _length = 0;
    _attemptProbability = 0;
    _bestProbability = 0;
}

DecryptionHandler::~DecryptionHandler(){
    if(_decipheredWord){
        delete [] _decipheredWord;
        _decipheredWord = nullptr;
    }
}

bool DecryptionHandler::initializeHandler(unsigned int alphabetLength, unsigned int startCharacter){
    if(alphabetLength <= 0){
        return false;
    }
    _alphabetLength = alphabetLength;
    _startCharacter = startCharacter;
    return true;
}


bool DecryptionHandler::substitionDecipher(char* word, unsigned int length){
    if(!word || _alphabetLength == 0){
        return false;
    }
    if(_decipheredWord){
        delete []_decipheredWord;
        _decipheredWord = nullptr;
    }
    _decipheredWord = new(std::nothrow) char[length];
    if(!_decipheredWord){
        return false;
    }
    _attemptProbability = 0;
    _length = length;
    for(int offset = 1; offset < _alphabetLength; offset++){
        char attemptedDecipher [_length];
        for(unsigned int i = 0; i < _length; i++){
            if(word[i] == ' '){
                attemptedDecipher[i] = word[i];
            }else{
                char cipheredValue = word[i] + offset - _startCharacter;
                cipheredValue %= _alphabetLength;
                attemptedDecipher[i] = _startCharacter + cipheredValue;
            }
        }
        int tempProb = decypherProbability(attemptedDecipher);
        //if(tempProb > _attemptProbability || 1 == 1){
        if(tempProb > _attemptProbability){
        _attemptProbability = tempProb;
            _bestProbability = tempProb;
            for(int i = 0; i < _length; i++){
                _decipheredWord[i] = attemptedDecipher[i];
            }
            //printWord();
        }    
    }
    return true;
}

int DecryptionHandler::decypherProbability(char* word){
    int vowelLength [6] = {0, 0, 0, 0, 0, 0};
    int consonantLength [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ctrPos = 0;
    int ctrChar = 0;
    int state = 0;
    for(int i = 0; i < _length; i++){
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u'){
            if(state == 2){
                if(ctrChar < 11){
                    consonantLength[ctrChar - 1]++;
                }
                ctrChar = 0;
            }
            ctrChar ++;
            state = 1;
        } else if(word[i] == ' ' || word[i] == '\r'){
            if(state == 1){
                if (ctrChar < 7) {
                    vowelLength[ctrChar - 1]++;
                }
                ctrChar = 0;
                state = 0;
            } else if(state == 2){
                if (ctrChar < 11) {
                    consonantLength[ctrChar - 1]++;
                }
                ctrChar = 0;
                state = 0;
            }
        } else{
            if(state == 1){
                if (ctrChar < 7) {
                    vowelLength[ctrChar - 1] ++;
                }
                ctrChar = 0;
            }
            ctrChar ++;
            state = 2;
        }
    }
    if(state == 1){
        if (ctrChar < 7) {
            vowelLength[ctrChar - 1]++;
        }
        ctrChar = 0;
        state = 0;
    } else if(state == 2){
        if (ctrChar < 11) {
            consonantLength[ctrChar - 1]++;
        }
        ctrChar = 0;
        state = 0;
    }
    
    int probVow = 0;
    int probVowCount = 0;
    for(int i = 0; i < 6; i++){
        if(vowelLength[i] != 0){
            probVowCount += vowelLength[i];
            probVow += vowelLength[i] * probVowLength[i];

        }
    }
    if(probVowCount != 0){
        probVow = probVow / probVowCount;
    } else{
        probVow = 100;
    }
    int probCons = 0;
    int probConsCount = 0;
    for(int i = 0; i < 10; i++){
        if(consonantLength[i] != 0){
            probConsCount += consonantLength[i];
            probCons += consonantLength[i] * probConsLength[i];
        }
    }
    if(probConsCount != 0){
        probCons = probCons / probConsCount;
    } else{
        probCons = 100;
    }
    int probTotal = (probVow + probCons) / 2;
    return probTotal;
}

bool DecryptionHandler::evaluateWord(char* word){
    bool equal = true;
    for(int i = 0; i < _length; i++){
        if(word[i] != _decipheredWord[i]){
            equal = false;
        }
    }
    return equal;
}

bool DecryptionHandler::printWord(){
    if(!_decipheredWord || _alphabetLength == 0){
        return false;
    }
    for(unsigned int i = 0; i < _length; i++){
        std::cout << _decipheredWord[i];
    }
    std::cout << std::endl << "Probability of correctness: " << _bestProbability << "%" << std::endl;
    return true;
}
