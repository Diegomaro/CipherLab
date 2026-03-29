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
    return true;
}

bool EncryptionHandler::caesarDecipher(){
    if(!createWordToDecipher()){
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
        unsigned int tempProb = decypherProbabilityModel(decipherAttempt);
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


bool EncryptionHandler::caesarDecipherImproved(){
    if(!createWordToDecipher()){
        return false;
    }
    unsigned int offset = shiftedDecipherModel();
    for(unsigned int i = 0; i < _wordLength; i++){
        if(_cipherWord[i] == ' '){
            _decipheredWord[i] = _cipherWord[i];
        }else{
            char cipheredValue = _cipherWord[i] + (_alphabetLength - offset) - _startCharacter;
            cipheredValue %= _alphabetLength;
            _decipheredWord[i] = _startCharacter + cipheredValue;
        }
    }
    return true;
}

bool EncryptionHandler::scytaleDecipher(){
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

        unsigned int tempProb = decypherProbabilityModel(decipherAttempt);
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

unsigned int EncryptionHandler::decypherProbabilityModel(char* word){
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

unsigned int EncryptionHandler::shiftedDecipherModel(){
    unsigned int letterFrequency [26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    unsigned int totalLetters = 0;
    for(int i = 0; i < _wordLength; i++){
        if(122 >= (int)_cipherWord[i] && (int)_cipherWord[i] >= 97){
            letterFrequency[(int)_cipherWord[i] - 97]++;
            totalLetters ++;
        } else if(90 >= (int)_cipherWord[i] && (int)_cipherWord[i] >= 65){
            letterFrequency[(int)_cipherWord[i] + 32 - 97]++;
            totalLetters ++;
        }
    }
    for(int i = 0; i < 26; i++){
        letterFrequency[i] =  (int) ((float)letterFrequency[i] * 1000) / (float)totalLetters;
    }
    unsigned int totalFrequency = 0;
    for(int i = 0; i < 26; i++){
        totalFrequency += letterFrequency[i];
    }
    int averageDifference = 0;
    int averageDifferenceMin = 10000000;
    int finalOffset = 0;
    for(int i = 0; i < 26; i++){
        averageDifference = 0;
        for(int j = 0; j < 26; j++){
            if(letterFrequency[j] > 25){
                int transformedPos = (j + i) % 26;
                if(letterFrequency[transformedPos] > letterFrequencyModel[j]){
                    averageDifference += letterFrequency[transformedPos] - letterFrequencyModel[j];
                } else{
                    averageDifference += letterFrequencyModel[j] - letterFrequency[transformedPos];
                }
            }
        }
        if(averageDifference < averageDifferenceMin){
            finalOffset = i;
            averageDifferenceMin = averageDifference;
        }
    }
    return finalOffset;
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