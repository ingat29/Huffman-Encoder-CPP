#ifndef NODE_H
#define NODE_H
#pragma once
#include <cstdint>
#include <ostream>


class Node {
public:
    uint64_t frequency;
    uint8_t symbol;
    Node* left;
    Node* right;

    Node();
    Node(uint64_t frequency , uint8_t symbol  , Node* left = nullptr, Node* right = nullptr);
    Node(const Node& node);
    Node& operator=(const Node& node);
    // ~Node();
    friend class PriorityQueue;
    friend class Utils;
    friend class Header;
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};



#endif //NODE_H
