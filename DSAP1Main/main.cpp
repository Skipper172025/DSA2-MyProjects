#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "VigenereCipher.hpp"

using namespace std;

// Function to generate a random 9-character lowercase password
string generatePassword() {
    string password = "";
    for (int i = 0; i < 9; i++) {
        char randomChar = 'a' + (rand() % 26);
        password += randomChar;
    }
    return password;
}

// Function to extract just the name (first column) from a line
string extractName(const string& line) {
    size_t pos = line.find_first_of(" \t");
    if (pos != string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

int main() {
    srand(time(0));
    
    // Create Vigenere Cipher with key "jones"
    VigenereCipher cipher("jones");
    
    ifstream inputFile("names.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open names.txt" << endl;
        return 1;
    }
    
    ofstream outputFile("rawdata.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create rawdata.txt" << endl;
        inputFile.close();
        return 1;
    }
    
    string line;
    
    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        
        string userid = extractName(line);
        string password = generatePassword();
        
        outputFile << userid << " " << password << endl;
    }
    
    inputFile.close();
    outputFile.close();
    
    //Encrypt passwords and create encrypteddata.txt
    ifstream rawFile("rawdata.txt");
    if (!rawFile.is_open()) {
        cerr << "Error: Could not open rawdata.txt" << endl;
        return 1;
    }
    
    ofstream encryptedFile("encrypteddata.txt");
    if (!encryptedFile.is_open()) {
        cerr << "Error: Could not create encrypteddata.txt" << endl;
        rawFile.close();
        return 1;
    }
    
    string userid, password;
    
    while (rawFile >> userid >> password) {
        // Use the cipher object to encrypt
        string encryptedPassword = cipher.encrypt(password);
        encryptedFile << userid << " " << encryptedPassword << endl;
    }
    
    rawFile.close();
    encryptedFile.close();
    
    cout << "Files created successfully." << endl;
    
    return 0;
}