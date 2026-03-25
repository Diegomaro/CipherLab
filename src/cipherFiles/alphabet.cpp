#include "alphabet.hpp"
#include <iostream>
#include <random>
#include <ctime>

Alphabet::Alphabet(unsigned int length) {
    _alphabet = nullptr;
    _alphaLength = length;
    _wordLength = 0;
    std::srand(std::time(nullptr));
}

Alphabet::~Alphabet() {
    destroyAlphabet();
}

unsigned int Alphabet::getLength(){
    return _alphaLength;
}

bool Alphabet::destroyAlphabet(){
    if(!_alphabet){
        return false;  
    }
    delete [] _alphabet;
    _alphabet = nullptr;
    if(!_word){
        return false;  
    }
    delete [] _word;
    _word = nullptr;
    return true;
}

bool Alphabet::generateAlphabet(){
    if(_alphabet){
        return false;
    }
    _alphabet = new(std::nothrow) char[_alphaLength];
    for(unsigned int i = 0; i < _alphaLength; i++){
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
        delete _word;
        _word = nullptr;
    }
    _word = new(std::nothrow) char[length];
    if(!_word){
        return false;
    }
    _wordLength = length;
    _word[0] = 't';
    _word[1] = 'o';
    _word[2] = 'w';
    _word[3] = 'e';
    _word[4] = 'r';

    
    /*for(unsigned int i = 0; i < _wordLength; i++){
        _word[i] = _alphabet[std::rand() % _alphaLength];
    }*/
    return true;
}

char* Alphabet::getWord(){
    return _word;
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