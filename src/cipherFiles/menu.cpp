#include <fstream>
#include <sstream>
#include <ctime>

#include "menu.hpp"

Menu::Menu(){}

bool Menu::menuInitialization(){
    _alphabet.setAlphabetLength(26);
    std::srand(std::time(nullptr));
    if(!_alphabet.generateAlphabet()){
        std::cout << "Could not generate _alphabet!" << std::endl;
        return false;
    }
    _cipher = Ciphers::caesar;
    _model = 1;
    _cipherText  = "Caesar Cipher";
    _modelText = "Model 1. Repeated vowel/consonant frequency";
    _encryptionHandler.initializeHandler(_alphabet.getLength(), _alphabet.getFirstElementAlphabet());
    _answer = 0;
    _veridict = false;
    return true;
}

bool Menu::centralMenu(){
    while(_answer != 4){
        chooseCentral();
        switch(_answer){
            case 1:{
                chooseCipher();
            } break;
            case 2:{
                chooseModel();
            } break;
            case 3:{
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Running Cipher" << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Select an option: " << std::endl << std::endl;
                std::cout << "1. Run one cipher" << std::endl;
                std::cout << "2. Batch run of cipher" << std::endl;
                std::cout << std::endl << "Answer: ";
                unsigned int mode = 0;
                std::cin >> mode;
                if(mode == 1){
                    std::cout << "--------------------------------------" << std::endl;
                    std::cout << "Choosing sentence to process" << std::endl;
                    std::cout << "--------------------------------------" << std::endl;
                    std::cout << "Select an option: " << std::endl << std::endl;
                    std::cout << "1. Set sentence by user" << std::endl;
                    std::cout << "2. Generate a random word (work in progress)" << std::endl;
                    std::cout << std::endl << "Answer: ";
                    unsigned int subAnswer = 0;
                    std::cin >> subAnswer;
                    if(subAnswer == 1){
                        std::string wordString;
                        std::cout << "Input sentence to cipher and decipher: ";
                        std::getline(std::cin >> std::ws, wordString);
                        if(!_alphabet.setWord(wordString)){
                            std::cout << "Could not set Word!" << std::endl;
                            return false;
                        }
                    } else{
                        unsigned int wordLength;
                        std::cout << "Input word length desired: ";
                        std::cin >> wordLength;
                        if(!_alphabet.generateWord(wordLength)){
                            std::cout << "Could not generate Word!" << std::endl;
                            return false;
                        }
                    }
                    _word = _alphabet.getWord();
                    //change depending on cipher, ADD LATER
                    switch(_cipher){
                        case Ciphers::atbash:{
                            std::cout << "No offset required!" << std::endl;
                        } break;
                        case Ciphers::scytale:{
                            std::cout << "Input cipher offset desired: ";
                            std::cin >> _cipherOffset;
                        } break;
                        case Ciphers::caesar:{
                            std::cout << "Input cipher offset desired: ";
                            std::cin >> _cipherOffset;
                        } break;
                        default:{
                            std::cout << "Invalid cipher set!" << std::endl;
                            return false;
                        }
                    }
                    cipherProcessing();
                    _veridict = _encryptionHandler.evaluateWord(_word);
                    printTestResults();
                    char input;
                    std::cout << "Input a character to continue...";
                    std::cin >> input;
                } else if(mode == 2){
                    unsigned int printMode = 0;
                    std::cout << "Insert '1' to print each test case, insert any other number to not print each test case: ";
                    std::cin >> printMode;
                    unsigned int acurracyCounter = 0;
                    unsigned int total = 0;
                    std::ifstream file;
                    std::string line;
                    file.open("../data/test_cases_substitution_cipher.csv");
                    if(!file.is_open()){
                        std::cout << "Could not open file!" << std::endl;
                        return false;
                    }
                    while(std::getline(file, line)){
                        if(!_alphabet.setWord(line)){
                            return false;
                        }
                        _word = _alphabet.getWord();
                        switch(_cipher){
                            case Ciphers::atbash:{
                            } break;
                            case Ciphers::scytale:{
                                _cipherOffset = (rand() % (((_alphabet.getWordLength() + 1) / 2) - 1)) + 2;
                            } break;
                            case Ciphers::caesar:{
                                _cipherOffset = (rand() % 25) + 1;
                            } break;
                        }
                        cipherProcessing();
                        _veridict = _encryptionHandler.evaluateWord(_word);
                        total ++;
                        if(_veridict == true){
                            acurracyCounter++;
                        }
                        if(printMode == 1){
                            printTestResults();
                        }
                    }
                    unsigned int probabilityOfSuccess = ((float)acurracyCounter/(float)total) * 100;
                    std::cout << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << _cipherText <<  " Test Results" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Total tests: " << total << std::endl << std::endl;
                    std::cout << "Total succesfull tests: " << acurracyCounter << std::endl << std::endl;
                    std::cout << "Success: " << probabilityOfSuccess << "%" << std::endl << std::endl;
                    char input;
                    std::cout << "Input a character to continue...";
                    std::cin >> input;
                }
                // test file results and naming of the file, ADD LATER
            } break;
        }
    }
    return true;
}

bool Menu::chooseCentral(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Cipher Attack Menu" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Select an option: " << std::endl << std::endl;
    std::cout << "1. Choose cipher" << std::endl;
    std::cout << "2. Choose prediction model" << std::endl;
    std::cout << "3. Run cipher" << std::endl;
    std::cout << "4. Exit program" << std::endl;
    std::cout << std::endl << "Answer: ";
    std::cin >> _answer;
    std::cout << std::endl;
    return true;
}

bool Menu::chooseCipher(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Choosing Cipher" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Select an option: " << std::endl << std::endl;
    std::cout << "1. Atbash Cipher" << std::endl;
    std::cout << "2. Scytale Cipher" << std::endl;
    std::cout << "3. Caesar Cipher (default)" << std::endl;
    std::cout << "4. Vignere Cipher" << std::endl;
    std::cout << std::endl << "Answer: ";
    unsigned int cipherInt = 0;
    std::cin >> cipherInt;
    _cipher = static_cast<Ciphers>(cipherInt);
    if(_cipher == Ciphers::atbash) _cipherText = "Atbash Cipher";
    else if(_cipher == Ciphers::scytale) _cipherText = "Scytale Cipher";
    else if(_cipher == Ciphers::caesar) _cipherText = "Caesar Cipher";
    else if(_cipher == Ciphers::vignere) _cipherText = "Vignere Cipher";
    return true;
}

bool Menu::chooseModel(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Choosing Model" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Select an option: " << std::endl << std::endl;
    std::cout << "1. Repeated vowel/consonant frequency" << std::endl;
    std::cout << "2. Letter frequency" << std::endl;
    std::cout << "3. Model 1 and 2 combined" << std::endl;
    std::cout << std::endl << "Answer: ";
    std::cin >> _model;
    if(_model == 1) _modelText = "Model 1: Repeated vowel/consonant frequency";
    else if(_model == 2) _modelText = "Model 2: Letter frequency";
    else if(_model == 3) _modelText = "Model 3: Repeated vowel/consonant frequency + Letter frequency";
    return true;
}

bool Menu::cipherProcessing(){
    if(!_encryptionHandler.setRawWord(_word, _alphabet.getWordLength())){
        std::cout << "Could not set word to cipher!" << std::endl;
        return false;
    }

    switch(_cipher){
        case Ciphers::atbash:{
            if(!_encryptionHandler.atbashCipher()){
                std::cout << "Could not cipher Word!" << std::endl;
                return false;
            }
            if(!_encryptionHandler.atbashDecipher()){
                std::cout << "Could not decipher Word!" << std::endl;
                return false;
            }
        } break;
        case Ciphers::scytale:{
            if(!_encryptionHandler.scytaleCipher(_cipherOffset)){
                std::cout << "Could not cipher Word!" << std::endl;
                return false;
            }
            if(!_encryptionHandler.scytaleDecipher(_model)){
                std::cout << "Could not decipher Word!" << std::endl;
                return false;
            }
        } break;
        case Ciphers::caesar:{
            if(!_encryptionHandler.caesarCipher(_cipherOffset)){
                std::cout << "Could not cipher Word!" << std::endl;
                return false;
            }
            if(!_encryptionHandler.caesarDecipher(_model)){
                std::cout << "Could not decipher Word!" << std::endl;
                return false;
        }
        } break;
        default:{
            std::cout << "Invalid cipher set!" << std::endl;
            return false;
        }
    }
    return true;
}

bool Menu::printTestResults(){
    std::cout << "------------------------------" << std::endl;
    std::cout << _cipherText << " Test Results" << std::endl;
    std::cout << "------------------------------" << std::endl << std::endl;

    std::cout << "Word Length: " << _alphabet.getWordLength();
    std::cout << "  Offset: "<< _cipherOffset << std::endl;

    std::cout << "Original sentence: ";
    _encryptionHandler.printRawWord();
    std::cout << "Encrypted sentence: ";
    _encryptionHandler.printEncryptedWord();
    std::cout << "Decrypted sentence: ";
    _encryptionHandler.printUnencryptedWord();
    std::cout << "Decipher results: ";
    if(_veridict == true){
        std::cout << "Success!" << std::endl << std::endl;
    } else{
        std::cout << "Failure!" << std::endl << std::endl;
    }
    return true;
}