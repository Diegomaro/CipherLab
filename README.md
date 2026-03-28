# Cipher Lab
Lab for experimenting with different encryption algorithms and breaking them as well as finding which is the correct decipher with a custom language model. (Will add better models as new encryptions require better ones)

**Ciphers implemented so far:**
* Substitution Cipher (600 BCE)
* Scytale Cipher (400 BCE)

**Language model used:**
* Statistical Heuristics: Sequential consonants/vowels. Average probability of each sequence of consonants and vowels appearing in a word.

**Project Structure:**
Alphabet: Creates alphabet based on a given length and generates words
EncryptionHandler: Manages encryption and decryption processes, as well as the language model predictions.

**How to use:**
1. Download src files.
2. Go to directory /src/cipherFiles
3. g++ *.cpp -o cipher_lab
4. ./cipher_lab
If you want to run test cases, find or generate a database of sentences in english. Name it "test_cases_substitution_cipher", in csv format. (Will change this later on)
