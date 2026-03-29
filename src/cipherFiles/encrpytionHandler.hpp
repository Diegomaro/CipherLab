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
        bool caesarDecipherImproved();
        bool scytaleDecipher();
        bool atbashDecipher();

        bool evaluateWord(char* word);

        char* getEncryptedWord();
        char* getUnencryptedWord();
        bool printEncryptedWord();
        bool printUnencryptedWord();
    private:
        unsigned int decypherProbabilityModel(char* word);
        unsigned int shiftedDecipherModel();
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        unsigned int _wordLength;
        char *_rawWord;
        char* _cipherWord;
        char* _decipheredWord;
        unsigned int _attemptProbability;
        //model 1
        const unsigned int probVowLengthModel [6] = {100, 86, 65, 40, 15, 0};
        const unsigned int probConsLengthModel [10] = {100, 95, 84, 73, 62, 48, 37, 27, 14, 5};
        //model 2
        const unsigned int letterFrequencyModel [26] = {
            80, 15, 24, 45, 128, 22, 19, 64, 70, 1, 7, 40, 26,
            68, 75, 16, 1, 57, 62, 91, 30, 10, 24, 2, 22, 1
        };
};