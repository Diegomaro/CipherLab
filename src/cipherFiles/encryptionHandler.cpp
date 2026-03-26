#include "encrpytionHandler.hpp"


EncryptionHandler::EncryptionHandler(){
    _cipherWord = nullptr;
    _length = 0;
}

EncryptionHandler::~EncryptionHandler(){
    if(_cipherWord){
        delete [] _cipherWord;
        _cipherWord = nullptr;
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

char* EncryptionHandler::getWord(){
    return _cipherWord;
}

bool EncryptionHandler::printWord(){
    if(!_cipherWord || _alphabetLength == 0){
        return false;
    }
    for(unsigned int i = 0; i < _length; i++){
        std::cout << _cipherWord[i];
    }
    std::cout << std::endl;
    return true;
}