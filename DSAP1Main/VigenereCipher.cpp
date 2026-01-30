#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher(const std::string& encryptionKey) {
    key = encryptionKey;
}

std::string VigenereCipher::encrypt(const std::string& plaintext) {
    std::string encrypted = "";
    
    for (int i = 0; i < plaintext.length(); i++) {
        // Get the current character from plaintext
        char plaintextChar = plaintext[i];
        
        // Get the corresponding key character (cycling through key)
        char keyChar = key[i % key.length()];
        
        // Calculate offset: how far keyChar is from 'a'
        int offset = keyChar - 'a';
        
        // Shift plaintextChar by offset
        char encryptedChar = ((plaintextChar - 'a' + offset) % 26) + 'a';
        
        encrypted += encryptedChar;
    }
    
    return encrypted;
}

std::string VigenereCipher::decrypt(const std::string& ciphertext) {
    std::string decrypted = "";
    
    for (int i = 0; i < ciphertext.length(); i++) {
        // Get the current character from ciphertext
        char ciphertextChar = ciphertext[i];
        
        // Get the corresponding key character (cycling through key)
        char keyChar = key[i % key.length()];
        
        // Calculate offset: how far keyChar is from 'a'
        int offset = keyChar - 'a';
        
        // Shift back by offset (add 26 to handle negative numbers)
        char decryptedChar = ((ciphertextChar - 'a' - offset + 26) % 26) + 'a';
        
        decrypted += decryptedChar;
    }
    
    return decrypted;
}