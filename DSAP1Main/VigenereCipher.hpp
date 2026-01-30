#ifndef VIGENERE_CIPHER_HPP
#define VIGENERE_CIPHER_HPP

#include <string>

class VigenereCipher {
private:
    std::string key;

public:
    // Constructor - sets the encryption key
    VigenereCipher(const std::string& encryptionKey);
    
    // Encrypt a password using the Vigenere Cipher
    std::string encrypt(const std::string& plaintext);
    
    // Decrypt a password (optional, but useful for testing)
    std::string decrypt(const std::string& ciphertext);
};

#endif