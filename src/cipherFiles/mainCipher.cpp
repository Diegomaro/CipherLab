#include <iostream>
#include "alphabet.hpp"
#include "encrpytionHandler.hpp"
#include "decryptionHandler.hpp"

int main(){
    Alphabet alphabet(26);

    if(!alphabet.generateAlphabet()){
        std::cout << "Could not generate Alphabet!" << std::endl;
        return 1;
    }
    if(!alphabet.generateWord(5)){
        std::cout << "Could not generate Word!" << std::endl;
        return 1;
    }
    char *word = alphabet.getWord();

    EncryptionHandler encryptionHandler(alphabet.getLength(), alphabet.getFirstElementAlphabet());

    if(!encryptionHandler.substitionCipher(word, alphabet.getWordLength(), 5)){
        std::cout << "Could not cipher Word!" << std::endl;
        return 1;
    }
    
    if(!alphabet.printWord()){
        std::cout << "Could not print word!" << std::endl;
        return 1;
    }

    if(!encryptionHandler.printWord()){
        std::cout << "Could not print cipherword!" << std::endl;
        return 1;
    }

    char *cypherWord = encryptionHandler.getWord();

    DecryptionHandler decryptionHandler(alphabet.getLength(), alphabet.getFirstElementAlphabet());
    decryptionHandler.substitionDecipher(cypherWord, alphabet.getWordLength());
    decryptionHandler.printWord();
    return 0;
}