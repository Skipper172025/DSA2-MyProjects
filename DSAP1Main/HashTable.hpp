#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include "Node.hpp"

class HashTable {
private:
    Node** table;      // Array of pointers to Node
    int tableSize;
    
    // Hash function - converts userid to table index
    int hashFunction(const std::string& userid);
    
public:
    // Constructor
    HashTable(int size);
    
    // Destructor
    ~HashTable();
    
    // Insert a userid and encrypted password
    void insert(const std::string& userid, const std::string& encryptedPassword);
    
    // Search for a userid and return its encrypted password
    // Returns empty string if not found
    std::string search(const std::string& userid);
};

#endif