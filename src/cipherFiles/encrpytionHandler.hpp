#pragma once
#include <iostream>

class EncryptionHandler{
    public:
        EncryptionHandler();
        ~EncryptionHandler();
        bool initializeHandler(unsigned int alphabetLength, unsigned int startCharacter);
        bool setRawWord(char* word, unsigned int length);
        bool createWordToCipher();

        bool caesarCipher(unsigned int offset);
        bool scytaleCipher(unsigned int offset);
        bool atbashCipher();

        bool createWordToDecipher();
        bool caesarDecipher();
        bool scytaleDecipher();
        bool atbashDecipher();

        bool evaluateWord(char* word);

        char* getEncryptedWord();
        char* getUnencryptedWord();
        bool printEncryptedWord();
        bool printUnencryptedWord();
    private:
        unsigned int decypherProbability(char* word);
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        unsigned int _wordLength;
        char *_rawWord;
        char* _cipherWord;
        char* _decipheredWord;
        unsigned int _attemptProbability;
        const unsigned int probVowLength [6] = {100, 86, 65, 40, 15, 0};
        const unsigned int probConsLength [10] = {100, 95, 84, 73, 62, 48, 37, 27, 14, 5};
};