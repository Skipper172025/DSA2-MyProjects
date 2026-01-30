#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
public:
    std::string userid;
    std::string encryptedPassword;
    Node* next;
    
    // Constructor
    Node(const std::string& uid, const std::string& pwd);
};

#endif