#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

#include "alphabet.hpp"
#include "encrpytionHandler.hpp"
#include "enumerators.hpp"

int main(){
    std::srand(std::time(nullptr));

    Alphabet alphabet(26);
    EncryptionHandler eh;
    char *word;
    if(!alphabet.generateAlphabet()){
        std::cout << "Could not generate Alphabet!" << std::endl;
        return 1;
    }
    unsigned int cipherOffset = 0;
    Ciphers cipher = Ciphers::caesar;
    std::string cipherText  = "Caesar cipher";

    eh.initializeHandler(alphabet.getLength(), alphabet.getFirstElementAlphabet());
    unsigned int answer = 0;

    while(answer != 4){
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Cipher Attack Menu" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Select an option: " << std::endl << std::endl;
        std::cout << "1. Choose cipher" << std::endl;
        std::cout << "2. Run cipher" << std::endl;
        std::cout << "3. Choose prediction model" << std::endl;
        std::cout << "4. Exit program" << std::endl;
        std::cout << std::endl << "Answer: ";
        std::cin >> answer;
        std::cout << std::endl;
        switch(answer){
            case 1:{
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Choosing Cipher" << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Select an option: " << std::endl << std::endl;
                std::cout << "1. Caesar Cipher (default)" << std::endl;
                std::cout << "2. Scytale Cipher" << std::endl;
                std::cout << "3. Atbash Cipher" << std::endl;
                std::cout << std::endl << "Answer: ";
                unsigned int cipherInt = 0;
                std::cin >> cipherInt;
                cipher = static_cast<Ciphers>(cipherInt);
                if(cipher == Ciphers::caesar) cipherText = "Caesar Cipher";
                else if(cipher == Ciphers::scytale) cipherText = "Scytale Cipher";
                else if(cipher == Ciphers::atbash) cipherText = "Atbash Cipher";
            } break;
            case 2:{
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
                        if(!alphabet.setWord(wordString)){
                            std::cout << "Could not set Word!" << std::endl;
                            return 1;
                        }
                    } else{
                        unsigned int wordLength;
                        std::cout << "Input word length desired: ";
                        std::cin >> wordLength;
                        if(!alphabet.generateWord(wordLength)){
                            std::cout << "Could not generate Word!" << std::endl;
                            return 1;
                        }
                    }
                    word = alphabet.getWord();

                    //change depending on cipher, ADD LATER
                    switch(cipher){
                        case Ciphers::caesar:{
                            std::cout << "Input cipher offset desired: ";
                            std::cin >> cipherOffset;
                        } break;
                        case Ciphers::scytale:{
                            std::cout << "Input cipher offset desired: ";
                            std::cin >> cipherOffset;
                        } break;
                        case Ciphers::atbash:{
                            std::cout << "No offset required!" << std::endl;
                        } break;
                        default:{
                            std::cout << "Invalid cipher set!" << std::endl;
                            return 1;
                        }
                    }


                    if(!eh.setRawWord(word, alphabet.getWordLength())){
                        std::cout << "Could not set word to cipher!" << std::endl;
                        return 1;
                    }
                    switch(cipher){
                        case Ciphers::caesar:{
                            if(!eh.caesarCipher(cipherOffset)){
                                std::cout << "Could not cipher Word!" << std::endl;
                                return 1;
                            }
                            if(!eh.caesarDecipher()){
                                std::cout << "Could not decipher Word!" << std::endl;
                                return 1;
                            }
                        } break;
                        case Ciphers::scytale:{
                            if(!eh.scytaleCipher(cipherOffset)){
                                std::cout << "Could not cipher Word!" << std::endl;
                                return 1;
                            }
                            if(!eh.scytaleDecipher()){
                                std::cout << "Could not decipher Word!" << std::endl;
                                return 1;
                            }
                        } break;
                        case Ciphers::atbash:{
                            if(!eh.atbashCipher()){
                                std::cout << "Could not cipher Word!" << std::endl;
                                return 1;
                            }
                            if(!eh.atbashDecipher()){
                                std::cout << "Could not decipher Word!" << std::endl;
                                return 1;
                            }
                        } break;
                    }
                    if(cipher == Ciphers::caesar){
                    } else if(cipher == Ciphers::scytale){
                    }
                    bool veridict = eh.evaluateWord(word);

                    std::cout << "------------------------------" << std::endl;
                    std::cout << cipherText << " Test Results" << std::endl;
                    std::cout << "------------------------------" << std::endl << std::endl;

                    std::cout << "Word Length: " << alphabet.getWordLength();
                    std::cout << "  Offset: "<< cipherOffset << std::endl;

                    std::cout << "Original sentence" << std::endl;
                    alphabet.printWord();
                    std::cout << std::endl;
                    std::cout << "Encrypted sentence" << std::endl;
                    eh.printEncryptedWord();
                    std::cout << std::endl;
                    std::cout << "Decrypted sentence" << std::endl;
                    eh.printUnencryptedWord();
                    std::cout << std::endl;
                    std::cout << "Decipher results: ";
                    if(veridict == true){
                        std::cout << "Success!" << std::endl << std::endl;
                    } else{
                        std::cout << "Failure!" << std::endl << std::endl;
                    }
                    char input;
                    std::cout << "Input a character to continue...";
                    std::cin >> input;
                } else if( mode == 2) {
                    unsigned int printMode = 0;
                    std::cout << "Insert '1' to print each test case, insert any other number to not print each test case: ";
                    std::cin >> printMode;
                    unsigned int acurracyCounter = 0;
                    unsigned int total = 0;
                    std::ifstream file;
                    std::string line;
                    file.open("test_cases_substitution_cipher.csv");
                    if(!file.is_open()){
                        std::cout << "Could not open file!" << std::endl;
                        return 1;
                    }
                    while(std::getline(file, line)){
                        if(!alphabet.setWord(line)){
                            return false;
                        }
                        word = alphabet.getWord();
                        if(!eh.setRawWord(word, alphabet.getWordLength())){
                            std::cout << "Could not set word to cipher!" << std::endl;
                            return 1;
                        }
                        switch(cipher){
                            case Ciphers::caesar:{
                                cipherOffset = (rand() % 25) + 1;
                                if(!eh.caesarCipher(cipherOffset)){
                                    std::cout << "Could not cipher Word!" << std::endl;
                                    return 1;
                                }
                                if(!eh.caesarDecipher()){
                                    std::cout << "Could not decipher Word!" << std::endl;
                                    return 1;
                            }
                            } break;
                            case Ciphers::scytale:{
                                cipherOffset = (rand() % (((alphabet.getWordLength() + 1) / 2) - 1)) + 2;
                                if(!eh.scytaleCipher(cipherOffset)){
                                    std::cout << "Could not cipher Word!" << std::endl;
                                    return 1;
                                }
                                if(!eh.scytaleDecipher()){
                                    std::cout << "Could not decipher Word!" << std::endl;
                                    return 1;
                                }
                            } break;
                            case Ciphers::atbash:{
                                if(!eh.atbashCipher()){
                                    std::cout << "Could not cipher Word!" << std::endl;
                                    return 1;
                                }
                                if(!eh.atbashDecipher()){
                                    std::cout << "Could not decipher Word!" << std::endl;
                                    return 1;
                                }
                            } break;
                            default:{
                                std::cout << "Invalid cipher set!" << std::endl;
                                return 1;
                            }
                        }
                        bool veridict = eh.evaluateWord(word);
                        total ++;
                        if(printMode == 1){
                            std::cout << "Word Length: " << alphabet.getWordLength();
                            std::cout << "  Offset: "<< cipherOffset << std::endl;
                            std::cout << "Original sentence:  ";
                            alphabet.printWord();
                            std::cout << "Encrypted sentence: ";
                            eh.printEncryptedWord();
                            std::cout << "Decrypted sentence: ";
                            eh.printUnencryptedWord();
                        }
                        if(veridict == true){
                            acurracyCounter++;
                            if(printMode == 1){
                                std::cout << "SUCESS!" << std::endl << std::endl;
                            }
                        } else{
                            if(printMode == 1){
                                std::cout << "FAILURE!" << std::endl << std::endl;
                            }
                        }
                    }
                    unsigned int probabilityOfSuccess = ((float)acurracyCounter/(float)total)*100;

                    std::cout << "-------------------------------" << std::endl;
                    std::cout << cipherText <<  " Test Results" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Total tests" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Total: " << total << std::endl << std::endl;;
                    std::cout << "Total succesfull tests" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Completed: " << acurracyCounter << std::endl << std::endl;
                    std::cout << "Average success" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Probability of success: " << probabilityOfSuccess << "%" << std::endl << std::endl;
                    char input;
                    std::cout << "Input a character to continue...";
                    std::cin >> input;
                }
                // test file results and naming of the file, ADD LATER
            } break;
            case 3:{
                // Choose prediction model
            } break;
        }
    }
    return 0;
}
