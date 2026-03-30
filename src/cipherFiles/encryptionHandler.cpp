#include <math.h>
#include "encrpytionHandler.hpp"


EncryptionHandler::EncryptionHandler(){
    _rawWord = nullptr;
    _cipherWord = nullptr;
    _decipheredWord = nullptr;
    _wordLength = 0;
    _attemptProbability = 0;
}

EncryptionHandler::~EncryptionHandler(){
    if(_rawWord){
        delete [] _rawWord;
        _rawWord = nullptr;
    }
    if(_cipherWord){
        delete [] _cipherWord;
        _cipherWord = nullptr;
    }
    if(_decipheredWord){
        delete [] _decipheredWord;
        _decipheredWord = nullptr;
    }
    if(_decipherAttempt){
        delete [] _decipherAttempt;
        _decipherAttempt = nullptr;
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

bool EncryptionHandler::setRawWord(char* word, unsigned int length){
    if(!word || _alphabetLength == 0){
        return false;
    }
    if(_rawWord){
        delete []_rawWord;
        _rawWord = nullptr;
    }
    _rawWord = new(std::nothrow) char[length];
    for(unsigned int i = 0; i < length; i++){
        _rawWord[i] = word[i];
    }
    if(!_rawWord){
        return false;
    }
    _wordLength = length;
    return true;
}

bool EncryptionHandler::createWordToCipher(){
    if(!_rawWord){
        return false;
    }
    if(_cipherWord){
        delete []_cipherWord;
        _cipherWord = nullptr;
    }
    _cipherWord = new(std::nothrow) char[_wordLength];
    if(!_cipherWord){
        return false;
    }
    return true;
}

bool EncryptionHandler::atbashCipher(){
    if(!createWordToCipher()){
        return false;
    }
    for(unsigned int i = 0; i < _wordLength; i++){
        if(_rawWord[i] == ' '){
            _cipherWord[i] = _rawWord[i];
        } else{
            _cipherWord[i] = 2 * _startCharacter + (_alphabetLength - 1) - _rawWord[i];
        }
    }
    return true;
}

bool EncryptionHandler::scytaleCipher(unsigned int offset){
    if(!createWordToCipher()){
        return false;
    }
    unsigned int posCounter = 0;
    unsigned int indexCounter = 0;
    for(unsigned int i = 0; i < offset; i++){
        indexCounter = i;
        while(indexCounter < _wordLength){
            _cipherWord[posCounter] =  _rawWord[indexCounter];
            indexCounter += offset;
            posCounter++;
        }
    }
    return true;
}

bool EncryptionHandler::caesarCipher(unsigned int offset){
    if(!createWordToCipher()){
        return false;
    }
    for(unsigned int i = 0; i < _wordLength; i++){
        if(_rawWord[i] == ' '){
            _cipherWord[i] = _rawWord[i];
        }else{
            char cipheredValue = _rawWord[i] + offset - _startCharacter;
            cipheredValue %= _alphabetLength;
            _cipherWord[i] = _startCharacter + cipheredValue;
        }
    }
    return true;
}

bool EncryptionHandler::createWordToDecipher(){
    if(!_cipherWord){
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
    if(_decipherAttempt){
        delete [] _decipherAttempt;
        _decipherAttempt = nullptr;
    }
    _decipherAttempt = new(std::nothrow) char[_wordLength];
    if(!_decipherAttempt){
        return false;
    }
    return true;
}

bool EncryptionHandler::atbashDecipher(){
    if(!createWordToDecipher()){
        return false;
    }
    for(unsigned int i = 0; i < _wordLength; i++){
        if(_cipherWord[i] == ' '){
            _decipheredWord[i] = _cipherWord[i];
        } else{
        _decipheredWord[i] = 2 * _startCharacter + (_alphabetLength - 1) - _cipherWord[i];
        }
    }
    return true;
}


bool EncryptionHandler::scytaleDecipher(unsigned int model){
    if(!createWordToDecipher()){
        return false;
    }
    _attemptProbability = 0;
    char *decipherAttempt = new(std::nothrow) char[_wordLength];
    if(!decipherAttempt){
        return false;
    }
    unsigned int maxOffset = (_wordLength + 1) / 2;

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

        unsigned int tempProb = modelHandler(model);
        if(tempProb > _attemptProbability || 1 == 1){
            _attemptProbability = tempProb;
            for(unsigned int i = 0; i < _wordLength; i++){
                _decipheredWord[i] = _decipherAttempt[i];
            }
            printUnencryptedWord();
        }
    }
    if(_decipherAttempt){
        delete []_decipherAttempt;
        _decipherAttempt = nullptr;
    }
    return true;
}

bool EncryptionHandler::caesarDecipher(unsigned int model){
    if(!createWordToDecipher()){
        return false;
    }
    _attemptProbability = 0;
    for(unsigned int offset = 1; offset < _alphabetLength; offset++){
        for(unsigned int i = 0; i < _wordLength; i++){
            if(_cipherWord[i] < 97 || _cipherWord[i] > 122){
                _decipherAttempt[i] = _cipherWord[i];
            }else{
                char cipheredValue = _cipherWord[i] + offset - _startCharacter;
                cipheredValue %= _alphabetLength;
                _decipherAttempt[i] = _startCharacter + cipheredValue;
            }
        }
        unsigned int tempProb = modelHandler(model);
        if(tempProb > _attemptProbability){
            _attemptProbability = tempProb;
            for(unsigned int i = 0; i < _wordLength; i++){
                _decipheredWord[i] = _decipherAttempt[i];
            }
        }
    }
    return true;
}

unsigned int EncryptionHandler::modelHandler(unsigned int model){
    unsigned int tempProb = 0;
    switch(model){
        case 1:{
            tempProb = typeLengthProbabilityModel();
        }break;
        case 2:{
            tempProb = letterFrequencyProbabilityModel();
        }break;
        case 3:{
            tempProb += typeLengthProbabilityModel();
            tempProb += letterFrequencyProbabilityModel();
            tempProb /= 2;
        }break;
        default:{
            tempProb = typeLengthProbabilityModel();
        }
    }
    return tempProb;
}

unsigned int EncryptionHandler::typeLengthProbabilityModel(){
    unsigned int vowelLength [6] = {0, 0, 0, 0, 0, 0};
    unsigned int consonantLength [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int ctrChar = 0;
    unsigned int state = 0;
    for(unsigned int i = 0; i < _wordLength; i++){
        if (_decipherAttempt[i] == 'a' || _decipherAttempt[i] == 'e' || _decipherAttempt[i] == 'i' || _decipherAttempt[i] == 'o' || _decipherAttempt[i] == 'u'){
            if(state == 2){
                if(ctrChar < 11){
                    consonantLength[ctrChar - 1]++;
                }
                ctrChar = 0;
            }
            ctrChar ++;
            state = 1;
        } else if(_decipherAttempt[i] == ' ' || _decipherAttempt[i] == '\r'){
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
            probVow += vowelLength[i] * probVowLengthModel[i];

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
            probCons += consonantLength[i] * probConsLengthModel[i];
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

unsigned int EncryptionHandler::letterFrequencyProbabilityModel(){
    unsigned int sumProbability = 0;
    unsigned int totalProbability = 0;
    for(unsigned int i = 0; i < _wordLength; i++){
        if(_decipherAttempt[i] <= 122 && _decipherAttempt[i] >= 97){
            unsigned int wordPosition = _decipherAttempt[i] - _startCharacter;
            sumProbability += letterProbabilityModel[wordPosition];
            totalProbability++;
        }
    }
    unsigned int averageProbability = sumProbability / totalProbability;
    return averageProbability;
}


bool EncryptionHandler::evaluateWord(char* word){
    for(unsigned int i = 0; i < _wordLength; i++){
        if(word[i] != _decipheredWord[i]){
            return false;
        }
    }
    return true;
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