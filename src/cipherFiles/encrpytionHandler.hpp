#pragma once
#include <iostream>

class EncryptionHandler{
    public:
        EncryptionHandler();
        ~EncryptionHandler();
        bool initializeHandler(unsigned int alphabetLength, unsigned int startCharacter);
        bool substitionCipher(char* word, unsigned int length, unsigned int offset);
        char* getWord();
        bool printWord();
    private:
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        char* _cipherWord;
        unsigned int _length;
};