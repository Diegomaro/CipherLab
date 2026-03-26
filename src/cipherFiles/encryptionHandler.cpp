#include "encrpytionHandler.hpp"


EncryptionHandler::EncryptionHandler(){
    _cipherWord = nullptr;
    _decipheredWord = nullptr;
    _length = 0;
    _attemptProbability = 0;
}

EncryptionHandler::~EncryptionHandler(){
    if(_cipherWord){
        delete [] _cipherWord;
        _cipherWord = nullptr;
    }
    if(_decipheredWord){
        delete [] _decipheredWord;
        _decipheredWord = nullptr;
    }
}

bool EncryptionHandler::initializeHandler(unsigned int alphabetLength, unsigned int startCharacter){
    if(alphabetLength <= 0){
        return false;
    }
    _alphabetLength = alphabetLength;
    _startCharacter = startCharacter;
    return true;
}

bool EncryptionHandler::substitionCipher(char* word, unsigned int length, unsigned int offset){
    if(!word || _alphabetLength == 0){
        return false;
    }
    if(_cipherWord){
        delete []_cipherWord;
        _cipherWord = nullptr;
    }
    _cipherWord = new(std::nothrow) char[length];
    if(!_cipherWord){
        return false;
    }
    _length = length; 
    for(unsigned int i = 0; i < length; i++){
        if(word[i] == ' '){
            _cipherWord[i] = word[i];
        }else{
            char cipheredValue = word[i] + offset - _startCharacter;
            cipheredValue %= _alphabetLength;
            _cipherWord[i] = _startCharacter + cipheredValue;
        }
    }
    return true;
}

bool EncryptionHandler::substitionDecipher(unsigned int length){
    if(!_cipherWord || _alphabetLength == 0){
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
            if(_cipherWord[i] == ' '){
                attemptedDecipher[i] = _cipherWord[i];
            }else{
                char cipheredValue = _cipherWord[i] + offset - _startCharacter;
                cipheredValue %= _alphabetLength;
                attemptedDecipher[i] = _startCharacter + cipheredValue;
            }
        }
        unsigned int tempProb = decypherProbability(attemptedDecipher);
        if(tempProb > _attemptProbability){
        _attemptProbability = tempProb;
        for(int i = 0; i < _length; i++){
            _decipheredWord[i] = attemptedDecipher[i];
        }
        }    
    }
    return true;
}

unsigned int EncryptionHandler::decypherProbability(char* word){
    unsigned int vowelLength [6] = {0, 0, 0, 0, 0, 0};
    unsigned int consonantLength [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int ctrPos = 0;
    unsigned int ctrChar = 0;
    unsigned int state = 0;
    for(unsigned int i = 0; i < _length; i++){
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
    
    unsigned int probVow = 0;
    unsigned int probVowCount = 0;
    for(unsigned int i = 0; i < 6; i++){
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
    unsigned int probCons = 0;
    unsigned int probConsCount = 0;
    for(unsigned int i = 0; i < 10; i++){
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
    unsigned int probTotal = (probVow + probCons) / 2;
    return probTotal;
}

bool EncryptionHandler::evaluateWord(char* word){
    bool equal = true;
    for(unsigned int i = 0; i < _length; i++){
        if(word[i] != _decipheredWord[i]){
            equal = false;
        }
    }
    return equal;
}

char* EncryptionHandler::getEncryptedWord(){
    return _cipherWord;
}

char* EncryptionHandler::getUnencryptedWord(){
    return _decipheredWord;
}

bool EncryptionHandler::printEncryptedWord(){
    if(!_cipherWord || _alphabetLength == 0){
        return false;
    }
    for(unsigned int i = 0; i < _length; i++){
        std::cout << _cipherWord[i];
    }
    std::cout << std::endl;
    return true;
}

bool EncryptionHandler::printUnencryptedWord(){
    if(!_decipheredWord || _alphabetLength == 0){
        return false;
    }
    for(unsigned int i = 0; i < _length; i++){
        std::cout << _decipheredWord[i];
    }
    std::cout << std::endl;
    return true;
}