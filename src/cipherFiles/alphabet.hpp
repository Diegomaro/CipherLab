#pragma once
#include <string>

class Alphabet{
    public:
        Alphabet();
        ~Alphabet();
        void setAlphabetLength(unsigned int alphabetLength);
        bool generateAlphabet();
        bool destroyAlphabet();
        char* getAlphabet();
        char getFirstElementAlphabet();
        unsigned int getLength();
        bool generateWord(unsigned int length);
        char* getWord();
        bool setWord(std::string word);
        unsigned int getWordLength();
        bool printWord();

    private:
        unsigned int _alphabetLength;
        char *_alphabet;
        char *_word;
        unsigned int _wordLength;
};