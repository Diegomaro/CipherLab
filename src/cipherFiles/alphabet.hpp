#pragma once
class Alphabet{
    public:
        Alphabet(unsigned int length);
        ~Alphabet();
        bool generateAlphabet();
        bool destroyAlphabet();
        char* getAlphabet();
        char getFirstElementAlphabet();
        unsigned int getLength();
        bool generateWord(unsigned int length);
        char* getWord();
        unsigned int getWordLength();
        bool printWord();

    private:
        unsigned int _alphaLength;
        char *_alphabet;
        char *_word;
        unsigned int _wordLength;
};