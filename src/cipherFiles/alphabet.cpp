#include "alphabet.hpp"
#include <iostream>
#include <random>
#include <ctime>

Alphabet::Alphabet() {
    _alphabet = nullptr;
    _word = nullptr;
    _alphabetLength = 0;
    _wordLength = 0;
}

Alphabet::~Alphabet() {
    destroyAlphabet();
}

void Alphabet::setAlphabetLength(unsigned int alphabetLength){
    _alphabetLength = alphabetLength;
}

unsigned int Alphabet::getLength(){
    return _alphabetLength;
}

bool Alphabet::destroyAlphabet(){
    if(_alphabet){
        delete [] _alphabet;
        _alphabet = nullptr;
    }
    if(_word){
        delete [] _word;
        _word = nullptr;
    }
    return true;
}

bool Alphabet::generateAlphabet(){
    if(_alphabetLength == 0){
        return false;
    }
    if(_alphabet){
        delete [] _alphabet;
        _alphabet = nullptr;
    }
    _alphabet = new(std::nothrow) char[_alphabetLength];
    if(!_alphabet){
        return false;
    }
    for(unsigned int i = 0; i < _alphabetLength; i++){
        _alphabet[i] = 97 + i;
    }
    return true;
}

char Alphabet::getFirstElementAlphabet(){
    if(_alphabet){
        return _alphabet[0];
    } else{
        return '\0';
    }
}


char* Alphabet::getAlphabet(){
    return _alphabet;
}

bool Alphabet::generateWord(unsigned int length){
    if(!_alphabet){
        return false;
    }
    if(_word){
        delete []_word;
        _word = nullptr;
    }
    _word = new(std::nothrow) char[length];
    if(!_word){
        return false;
    }
    _wordLength = length;
    for(unsigned int i = 0; i < _wordLength; i++){
        _word[i] = _alphabet[std::rand() % _alphabetLength];
    }
    return true;
}

char* Alphabet::getWord(){
    return _word;
}

bool Alphabet::setWord(std::string word){
    if(_word){
        delete []_word;
        _word = nullptr;
    }
    if (!word.empty() && word.back() == '\r') {
        word.pop_back();
    }
    unsigned int newWordLength = word.length();

    _word = new(std::nothrow) char[newWordLength];
    if(!_word){
        return false;
    }
    _wordLength = newWordLength;
    for(unsigned int i = 0; i < newWordLength; i++){
        _word[i] = word[i];
    }
    return true;
}


unsigned int Alphabet::getWordLength(){
    return _wordLength;
}

bool Alphabet::printWord(){
    if(!_word){
        return false;
    }
    for(unsigned int i = 0; i < _wordLength; i++){
        std::cout << _word[i];
    }
    std::cout << std::endl;
    return true;
}