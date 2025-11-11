#include "Node.h"
#include <iostream>


Node::Node() {
    this->symbol='\0';
    this->frequency = 0;
    this->left = nullptr;
    this->right = nullptr;
}
Node::Node(uint64_t frequency, uint8_t symbol , Node* left, Node* right) {
    this->symbol = symbol;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}
Node::Node(const Node& node) {
    this->symbol = node.symbol;
    this->frequency = node.frequency;
    this->left = node.left;
    this->right = node.right;
}
Node& Node::operator=(const Node& node) {
    if (this != &node) {
        this->symbol = node.symbol;
        this->frequency = node.frequency;
        this->left = node.left;
        this->right = node.right;
        return *this;
    }else {
        return *this;
    }
}
// Node::~Node() {
//     this->symbol = '\0';
//     this->frequency = 0;
//
//     delete this->left;
//     delete this->right;
// }

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os <<"Symbol:"<< node.symbol << '|' <<"Frequency:" <<node.frequency <<'|'<<"Left:" << node.left << '|'<<"Right:" << node.right;
    return os;
}
