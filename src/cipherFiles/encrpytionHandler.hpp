#pragma once
#include <iostream>

class EncryptionHandler{
    public:
        EncryptionHandler();
        ~EncryptionHandler();
        bool initializeHandler(unsigned int alphabetLength, unsigned int startCharacter);
        bool substitionCipher(char* word, unsigned int length, unsigned int offset);
        bool substitionDecipher(unsigned int length);
        bool evaluateWord(char* word);
        char* getEncryptedWord();
        char* getUnencryptedWord();
        bool printEncryptedWord();
        bool printUnencryptedWord();
    private:
        unsigned int decypherProbability(char* word);
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        char* _cipherWord;
        char* _decipheredWord;
        unsigned int _length;
        unsigned int _attemptProbability;
        const unsigned int probVowLength [6] = {100, 86, 65, 40, 15, 0};
        const unsigned int probConsLength [10] = {100, 95, 84, 73, 62, 48, 37, 27, 14, 5};

};