#include "HashTable.hpp"

HashTable::HashTable(int size) {
    tableSize = size;
    table = new Node*[tableSize];
    
    // Initialize all buckets to nullptr
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    // Delete all nodes in each bucket
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    // Delete the table array itself
    delete[] table;
}

int HashTable::hashFunction(const std::string& userid) {
    // Simple hash: sum ASCII values of characters, mod by table size
    int sum = 0;
    for (int i = 0; i < userid.length(); i++) {
        sum += userid[i];
    }
    return sum % tableSize;
}

void HashTable::insert(const std::string& userid, const std::string& encryptedPassword) {
    // Get hash index
    int index = hashFunction(userid);
    
    // Create new node
    Node* newNode = new Node(userid, encryptedPassword);
    
    // Insert at front of linked list (easiest method)
    newNode->next = table[index];
    table[index] = newNode;
}

std::string HashTable::search(const std::string& userid) {
    // Get hash index
    int index = hashFunction(userid);
    
    // Search through linked list at that index
    Node* current = table[index];
    while (current != nullptr) {
        if (current->userid == userid) {
            return current->encryptedPassword;
        }
        current = current->next;
    }
    
    // Not found
    return "";
}