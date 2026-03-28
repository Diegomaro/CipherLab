#include <math.h>
#include "encrpytionHandler.hpp"


EncryptionHandler::EncryptionHandler(){
    _cipherWord = nullptr;
    _decipheredWord = nullptr;
    _wordLength = 0;
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
    _wordLength = length; 
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

bool EncryptionHandler::scytaleCipher(char* word, unsigned int length, unsigned int offset){
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
    _wordLength = length;

    unsigned int posCounter = 0;
    unsigned int indexCounter = 0;

    for(unsigned int i = 0; i < offset; i++){
        indexCounter = i;
        while(indexCounter < _wordLength){
            _cipherWord[posCounter] =  word[indexCounter];
            indexCounter += offset;
            posCounter++;
        }
    }
    return true;
}


bool EncryptionHandler::substitionDecipher(){
    if(!_cipherWord || _alphabetLength == 0){
        return false;
    }
    if(_decipheredWord){
        delete []_decipheredWord;
        _decipheredWord = nullptr;
    }
    _decipheredWord = new(std::nothrow) char[_wordLength];
    if(!_decipheredWord){
        return false;
    }
    _attemptProbability = 0;
    char *decipherAttempt = new(std::nothrow) char[_wordLength];
    if(!decipherAttempt){
        return false;
    }
    for(unsigned int offset = 1; offset < _alphabetLength; offset++){
        for(unsigned int i = 0; i < _wordLength; i++){
            if(_cipherWord[i] == ' '){
                decipherAttempt[i] = _cipherWord[i];
            }else{
                char cipheredValue = _cipherWord[i] + offset - _startCharacter;
                cipheredValue %= _alphabetLength;
                decipherAttempt[i] = _startCharacter + cipheredValue;
            }
        }
        unsigned int tempProb = decypherProbability(decipherAttempt);
        if(tempProb > _attemptProbability){
            _attemptProbability = tempProb;
            for(unsigned int i = 0; i < _wordLength; i++){
                _decipheredWord[i] = decipherAttempt[i];
            }
        }    
    }
    if(decipherAttempt){
        delete []decipherAttempt;
        decipherAttempt = nullptr;
    }
    return true;
}

bool EncryptionHandler::scytaleDecipher(){
    if(!_cipherWord || _alphabetLength == 0){
        return false;
    }
    if(_decipheredWord){
        delete []_decipheredWord;
        _decipheredWord = nullptr;
    }
    _decipheredWord = new(std::nothrow) char[_wordLength];
    if(!_decipheredWord){
        return false;
    }
    
    _attemptProbability = 0;
    char *decipherAttempt = new(std::nothrow) char[_wordLength];
    if(!decipherAttempt){
        return false;
    }
    unsigned int maxOffset = (_wordLength + 1) / 2;
    //unsigned int maxOffset = _wordLength;
    
    for(unsigned int offset = 1; offset < maxOffset; offset++){
        unsigned int posCounter = 0;
        unsigned int indexCounter = 0;
        unsigned int charsPerJump = (int) ceil((float)_wordLength / (float)offset);
        unsigned int maxWordLength = charsPerJump * offset;
        for(unsigned int j = 0; j < offset; j++){
            unsigned int missing = maxWordLength - _wordLength;
            missing = charsPerJump - missing;
            unsigned int tmpOffset = offset;
            indexCounter = j;
            while(indexCounter < _wordLength){
                tmpOffset = offset;
                if(missing > 0){
                    missing--;
                } else{
                    tmpOffset--;
                }
                decipherAttempt[posCounter] =  _cipherWord[indexCounter];
                indexCounter += tmpOffset;
                posCounter++;
            }
        }    

        unsigned int tempProb = decypherProbability(decipherAttempt);
        if(tempProb > _attemptProbability || 1 == 1){
            _attemptProbability = tempProb;
            for(unsigned int i = 0; i < _wordLength; i++){
                _decipheredWord[i] = decipherAttempt[i];
            }
            printUnencryptedWord();
        }  
    }
    if(decipherAttempt){
        delete []decipherAttempt;
        decipherAttempt = nullptr;
    }
    return true;
}

unsigned int EncryptionHandler::decypherProbability(char* word){
    unsigned int vowelLength [6] = {0, 0, 0, 0, 0, 0};
    unsigned int consonantLength [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int ctrChar = 0;
    unsigned int state = 0;
    for(unsigned int i = 0; i < _wordLength; i++){
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
    for(unsigned int i = 0; i < _wordLength; i++){
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
    for(unsigned int i = 0; i < _wordLength; i++){
        std::cout << _cipherWord[i];
    }
    std::cout << std::endl;
    return true;
}

bool EncryptionHandler::printUnencryptedWord(){
    if(!_decipheredWord || _alphabetLength == 0){
        return false;
    }
    for(unsigned int i = 0; i < _wordLength; i++){
        std::cout << _decipheredWord[i];
    }
    std::cout << std::endl;
    return true;
}