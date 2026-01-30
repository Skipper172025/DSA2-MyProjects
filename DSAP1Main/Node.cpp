#include "Node.hpp"

Node::Node(const std::string& uid, const std::string& pwd) {
    userid = uid;
    encryptedPassword = pwd;
    next = nullptr;
}