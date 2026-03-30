#pragma once
#include <iostream>
#include "alphabet.hpp"
#include "encryptionHandler.hpp"
#include "enumerators.hpp"

class Menu{
    public:
        Menu();
        bool menuInitialization();
        bool centralMenu();
    private:
        bool chooseCentral();
        bool chooseCipher();
        bool chooseModel();
        bool cipherProcessing();
        bool printTestResults();
        Alphabet _alphabet;
        EncryptionHandler _encryptionHandler;
        unsigned int _cipherOffset;
        char *_word;
        Ciphers _cipher;
        unsigned int _model;
        std::string _cipherText;
        std::string _modelText;
        unsigned int _answer;
        bool _veridict;
};
