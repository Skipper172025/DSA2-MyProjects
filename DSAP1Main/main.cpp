#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random 9-character lowercase password
string generatePassword() {
    string password = "";
    for (int i = 0; i < 9; i++) {
        // Generate random number 0-25, add 'a' to get lowercase letter
        char randomChar = 'a' + (rand() % 26);
        password += randomChar;
    }
    return password;
}

// Function to extract just the name (first column) from a line
string extractName(const string& line) {
    // Find the first space or tab - name is everything before it
    size_t pos = line.find_first_of(" \t");
    if (pos != string::npos) {
        return line.substr(0, pos);
    }
    return line; // If no space/tab found, return whole line
}

int main() {
    // Seed random number generator
    srand(time(0));
    
    // Open input file
    ifstream inputFile("names.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open names.txt" << endl;
        return 1;
    }
    
    // Open output file
    ofstream outputFile("rawdata.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create rawdata.txt" << endl;
        inputFile.close();
        return 1;
    }
    
    string line;
    int count = 0;
    
    // Read each line from names.txt
    while (getline(inputFile, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        
        // Extract the name (first column only)
        string userid = extractName(line);
        
        // Generate random password
        string password = generatePassword();
        
        // Write to rawdata.txt
        outputFile << userid << " " << password << endl;
        
        count++;
    }
    
    // Close files
    inputFile.close();
    outputFile.close();
    
    cout << "Successfully generated " << count << " userid/password combinations." << endl;
    cout << "Output written to rawdata.txt" << endl;
    
    return 0;
}
