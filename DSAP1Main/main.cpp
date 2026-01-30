#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "VigenereCipher.hpp"
#include "HashTable.hpp"

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
    
    // Generate rawdata.txt
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
        string encryptedPassword = cipher.encrypt(password);
        encryptedFile << userid << " " << encryptedPassword << endl;
    }
    
    rawFile.close();
    encryptedFile.close();
    
    // Build hash table and test
    // Create hash table
    HashTable hashTable(10000);
    
    // Load encrypteddata.txt into hash table
    ifstream encFile("encrypteddata.txt");
    if (!encFile.is_open()) {
        cerr << "Error: Could not open encrypteddata.txt" << endl;
        return 1;
    }
    
    while (encFile >> userid >> password) {
        hashTable.insert(userid, password);
    }
    encFile.close();
    
    // Store entries from rawdata.txt for testing
    vector<pair<string, string>> rawEntries;
    ifstream rawTestFile("rawdata.txt");
    if (!rawTestFile.is_open()) {
        cerr << "Error: Could not open rawdata.txt for testing" << endl;
        return 1;
    }
    
    while (rawTestFile >> userid >> password) {
        rawEntries.push_back(make_pair(userid, password));
    }
    rawTestFile.close();
    
    // Test entries 1, 3, 5, 7, 9 (indices 0, 2, 4, 6, 8)
    int testIndices[] = {0, 2, 4, 6, 8};
    
    cout << "\nLegal:" << endl;
    cout << "Userid\t\tPassword(file)\tPassword(table/un)\tResult" << endl;
    
    for (int i = 0; i < 5; i++) {
        int idx = testIndices[i];
        if (idx < rawEntries.size()) {
            string testUserid = rawEntries[idx].first;
            string testPassword = rawEntries[idx].second;
            
            // Encrypt the password from rawdata.txt
            string encryptedTest = cipher.encrypt(testPassword);
            
            // Search in hash table
            string tablePassword = hashTable.search(testUserid);
            
            // Compare
            string result = (encryptedTest == tablePassword) ? "match" : "no match";
            
            cout << testUserid << "\t\t" << testPassword << "\t" << testPassword 
                 << "\t" << result << endl;
        }
    }
    
    cout << "\nIllegal:" << endl;
    cout << "Userid\t\tPassword(mod)\tPassword(table/un)\tResult" << endl;
    
    for (int i = 0; i < 5; i++) {
        int idx = testIndices[i];
        if (idx < rawEntries.size()) {
            string testUserid = rawEntries[idx].first;
            string testPassword = rawEntries[idx].second;
            
            // Modify first character to 'z' (or 'a' if already 'z')
            if (testPassword[0] == 'z') {
                testPassword[0] = 'a';
            } else {
                testPassword[0] = 'z';
            }
            
            // Encrypt the modified password
            string encryptedTest = cipher.encrypt(testPassword);
            
            // Search in hash table
            string tablePassword = hashTable.search(testUserid);
            
            // Get original password for display
            string originalPassword = rawEntries[idx].second;
            
            // Compare
            string result = (encryptedTest == tablePassword) ? "match" : "no match";
            
            cout << testUserid << "\t\t" << testPassword << "\t" << originalPassword 
                 << "\t" << result << endl;
        }
    }
    
    return 0;
}