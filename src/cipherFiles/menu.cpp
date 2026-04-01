
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
    _encryptionHandler.initializeHandler(_alphabet.getLength(), _alphabet.getFirstElementAlphabet());
    _word = nullptr;
    _cipher = Ciphers::caesar;
    _cipherText  = "Caesar Cipher";
    _model = 1;
    _modelText = "Model 1. Repeated vowel/consonant frequency";

    _cipherOffset = 0;
    _answer = 0;
    _runMode = 0;
    _printMode = 0;
    _veridict = false;
    _total = 0;
    _acurracyCounter = 0;
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
                chooseRunMode();
                if(_runMode == 1){
                    chooseWord();
                    _word = _alphabet.getWord();
                    chooseOffset();
                    cipherProcessing();
                    _veridict = _encryptionHandler.evaluateWord(_word);
                    printTestResults();
                    continueToMenu();
                } else if(_runMode == 2){
                    _total = 0;
                    _acurracyCounter = 0;
                    loadFile();
                    choosePrintMode();

                    while(std::getline(_readFromFile, _lineFromReadFile)){
                        if(!_alphabet.setWord(_lineFromReadFile)){
                            return false;
                        }
                        offsetGenerator();
                        cipherProcessing();
                        _veridict = _encryptionHandler.evaluateWord(_word);
                        _total ++;
                        if(_veridict == true){
                            _acurracyCounter++;
                        }
                        if(_printMode == 1){
                            printTestResults();
                        }
                    }
                    printLargeTestResults();
                    continueToMenu();
                    _lineFromReadFile = "";
                    _readFromFile.close();
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

bool Menu::chooseRunMode(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Running Cipher" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Select an option: " << std::endl << std::endl;
    std::cout << "1. Run one cipher" << std::endl;
    std::cout << "2. Batch run of cipher" << std::endl;
    std::cout << std::endl << "Answer: ";
    std::cin >> _runMode;
    return true;
}


bool Menu::chooseWord(){
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
    return true;
}

bool Menu::chooseOffset(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Choosing offset" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    switch(_cipher){
        case Ciphers::atbash:{
            std::cout << _cipherText << " does not require an offset!" << std::endl;
        } break;
        case Ciphers::scytale:{
            _cipherOffset = 0;
            while(_cipherOffset == 0 || _cipherOffset >= _alphabet.getWordLength()){
                std::cout << "Choose an offset between 1 and " << _alphabet.getWordLength() - 1 << std::endl;
                std::cout << "Input cipher offset desired: ";
                std::cin >> _cipherOffset;
            }
        } break;
        case Ciphers::caesar:{
            _cipherOffset = 0;
            while(_cipherOffset == 0 || _cipherOffset >= _alphabet.getLength()){
                std::cout << "Choose an offset between 1 and 25" << std::endl;
                std::cout << "Input cipher offset desired: ";
                std::cin >> _cipherOffset;
            }
        } break;
        default:{
            std::cout << "Invalid cipher set!" << std::endl;
            return false;
        }
    }
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

bool Menu::offsetGenerator(){
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
    return true;
}

bool Menu::loadFile(){
    _readFromFile.open("../data/test_cases_substitution_cipher.csv");
    if(!_readFromFile.is_open()){
        std::cout << "Could not open file!" << std::endl;
        return false;
    }
    return true;
}

bool Menu::choosePrintMode(){
    std::cout << "Insert '1' to print each test case, insert any other number to not print each test case: ";
    std::cin >> _printMode;
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

bool Menu::printLargeTestResults(){
    unsigned int probabilityOfSuccess = ((float)_acurracyCounter/(float)_total) * 100;
    std::cout << "-------------------------------" << std::endl;
    std::cout << _cipherText <<  " Test Results" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Total tests: " << _total << std::endl << std::endl;
    std::cout << "Total succesfull tests: " << _acurracyCounter << std::endl << std::endl;
    std::cout << "Success: " << probabilityOfSuccess << "%" << std::endl << std::endl;
    return true;
}

bool Menu::continueToMenu(){
    char input;
    std::cout << "Input a character to continue...";
    std::cin >> input;
    return true;
}
