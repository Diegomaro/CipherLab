#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
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
        bool chooseRunMode();
        bool chooseWord();
        bool chooseOffset();
        bool cipherProcessing();
        bool offsetGenerator();
        bool loadFile();
        bool choosePrintMode();
        bool printTestResults();
        bool printLargeTestResults();
        bool continueToMenu();
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
        unsigned int _runMode;
        unsigned int _printMode;
        unsigned int _total;
        unsigned int _acurracyCounter;
        std::ifstream _readFromFile;
        std::string _lineFromReadFile;
};
