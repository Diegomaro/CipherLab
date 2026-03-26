#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

#include "alphabet.hpp"
#include "encrpytionHandler.hpp"


int main(){
    std::srand(std::time(nullptr));

    Alphabet alphabet(26);
    EncryptionHandler eh;
    //DecryptionHandler dh;
    char *word;

    if(!alphabet.generateAlphabet()){
        std::cout << "Could not generate Alphabet!" << std::endl;
        return 1;
    }
    eh.initializeHandler(alphabet.getLength(), alphabet.getFirstElementAlphabet());
    //dh.initializeHandler(alphabet.getLength(), alphabet.getFirstElementAlphabet());

    unsigned int answer = 0;
    while(answer != 11){
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "CIPHER ATTACK MENU" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Choose an option: " << std::endl << std::endl;
        std::cout << "1. Set sentence to cipher and decipher" << std::endl;
        std::cout << "2. Generate word of length 'n'" << std::endl;
        std::cout << "3. Run substitution cipher" << std::endl;
        std::cout << "4. Run substitution on test cases" << std::endl;
        std::cout << std::endl;
		std::cout << "Answer: ";
        std::cin >> answer;
        switch(answer){
            case 1: {
                std::string word;
                std::cout << "Input sentence to cipher and decipher: ";
                std::cin >> word;
                if(!alphabet.setWord(word)){
                    std::cout << "Could not set Word!" << std::endl;
                    return 1;
                }
                word = alphabet.getWord();
            } break;
            case 2: {
                unsigned int wordLength;
                std::cout << "Input word length desired: ";
                std::cin >> wordLength;
                if(!alphabet.generateWord(wordLength)){
                    std::cout << "Could not generate Word!" << std::endl;
                    return 1;
                }
                word = alphabet.getWord();
            } break;
            case 3: {
                unsigned int cipherOffset;
                std::cout << "Input cipher offset desired: ";
                std::cin >> cipherOffset;
                if(!eh.substitionCipher(word, alphabet.getWordLength(), cipherOffset)){
                    std::cout << "Could not cipher Word!" << std::endl;
                    return 1;
                }
                if(!eh.substitionDecipher(alphabet.getWordLength())){
                    std::cout << "Could not decipher Word!" << std::endl;
                    return 1;
                }
                bool veridict = eh.evaluateWord(word);

                std::cout << "------------------------------" << std::endl;
                std::cout << "SUBSTITION CIPHER TEST RESULTS" << std::endl;
                std::cout << "------------------------------" << std::endl << std::endl;

                std::cout << "Offset: "<< cipherOffset << std::endl;
                
                std::cout << "Original sentence" << std::endl;
                std::cout << "------------------------------" << std::endl;
                alphabet.printWord();
                std::cout << std::endl;
                std::cout << "Encrypted sentence" << std::endl;
                std::cout << "------------------------------" << std::endl;
                eh.printEncryptedWord();
                std::cout << std::endl;
                std::cout << "Decrypted sentence" << std::endl;
                std::cout << "------------------------------" << std::endl;
                eh.printUnencryptedWord();
                std::cout << std::endl;

                std::cout << "Verification " << std::endl;
                std::cout << "------------------------------" << std::endl;
                std::cout << "Decipher results: ";
                if(veridict == true){
                    std::cout << "SUCESS!" << std::endl << std::endl;
                } else{
                    std::cout << "FAILURE!" << std::endl << std::endl;
                }
                char input;
                std::cout << "Input a character to continue...";
                std::cin >> input;
            } break;
            case 4: {
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
                    unsigned int cipherOffset = (rand() % 25) + 1;
                    if(!eh.substitionCipher(word, alphabet.getWordLength(), cipherOffset)){
                        std::cout << "Could not cipher Word!" << std::endl;
                        return 1;
                    }
                    if(!eh.substitionDecipher(alphabet.getWordLength())){
                        std::cout << "Could not decipher Word!" << std::endl;
                        return 1;
                    }
                    bool veridict = eh.evaluateWord(word);
                    std::cout << "Offset: "<< cipherOffset << std::endl;
                    std::cout << "Original sentence:  ";
                    alphabet.printWord();
                    std::cout << "Encrypted sentence: ";
                    eh.printEncryptedWord();
                    std::cout << "Decrypted sentence: ";
                    eh.printUnencryptedWord();
                    if(veridict == true){
                        acurracyCounter++;
                        total ++;
                        std::cout << "SUCESS!" << std::endl << std::endl;
                    } else{
                        total ++;
                        std::cout << "FAILURE!" << std::endl << std::endl;
                    }
                }

                unsigned int probabilityOfSuccess = ((float)acurracyCounter/(float)total)*100;

                std::cout << "------------------------------------" << std::endl;
                std::cout << "SUBSTITION CIPHER LARGE TEST RESULTS" << std::endl;
                std::cout << "------------------------------------" << std::endl;

                std::cout << "Total tests" << std::endl;
                std::cout << "Total: " << total << std::endl << std::endl;;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Total succesfull tests" << std::endl;
                std::cout << "Completed: " << acurracyCounter << std::endl << std::endl;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Average success" << std::endl;
                std::cout << "Probability of success: " << probabilityOfSuccess << "%" << std::endl << std::endl;            
                std::cout << "------------------------------------" << std::endl;
                char input;
                std::cout << "Input a character to continue...";
                std::cin >> input;
            }break;
        }
        std::cout << std::endl;
    }
    return 0;
}