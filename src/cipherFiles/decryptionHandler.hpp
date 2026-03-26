#pragma once
#include <iostream>

class DecryptionHandler{
    public:
        DecryptionHandler();
        ~DecryptionHandler();
        bool initializeHandler(unsigned int alphabetLength, unsigned int startCharacter);
        bool substitionDecipher(char* word, unsigned int length);
        bool evaluateWord(char* word);
        bool printWord();
    private:
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        char* _decipheredWord;
        unsigned int _length;
        unsigned int _attemptProbability;
        unsigned int _bestProbability;
        int decypherProbability(char* word);
};