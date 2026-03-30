#pragma once
#include <iostream>

class EncryptionHandler{
    public:
        EncryptionHandler();
        ~EncryptionHandler();
        bool initializeHandler(unsigned int alphabetLength, unsigned int startCharacter);
        bool setRawWord(char* word, unsigned int length);
        bool createWordToCipher();

        bool atbashCipher();
        bool scytaleCipher(unsigned int offset);
        bool caesarCipher(unsigned int offset);

        bool createWordToDecipher();
        bool atbashDecipher();
        bool scytaleDecipher(unsigned int model);
        bool caesarDecipher(unsigned int model);

        bool evaluateWord(char* word);

        char* getEncryptedWord();
        char* getUnencryptedWord();
        bool printRawWord();
        bool printEncryptedWord();
        bool printUnencryptedWord();
    private:
        unsigned int modelHandler(unsigned int model);
        unsigned int typeLengthProbabilityModel();
        unsigned int letterFrequencyProbabilityModel();
        unsigned int _alphabetLength;
        unsigned int _startCharacter;
        unsigned int _wordLength;
        char *_rawWord;
        char* _cipherWord;
        char* _decipheredWord;
        char* _decipherAttempt;
        unsigned int _attemptProbability;
        //model 1
        const unsigned int probVowLengthModel [6] = {100, 86, 65, 40, 15, 0};
        const unsigned int probConsLengthModel [10] = {100, 95, 84, 73, 62, 48, 37, 27, 14, 5};
        //model 2
        const unsigned int letterProbabilityModel [26] = {
            96, 83, 87, 92, 100, 86, 84, 95, 95, 63, 76, 91, 88,
            95, 96, 83, 61, 94, 94, 97, 88, 80, 86, 64, 86, 60
        };
};