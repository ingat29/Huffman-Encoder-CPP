#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#pragma once
#include "Node.h"

class PriorityQueue {
private:
    Node* array;
    int size;
    int capacity;

public:
    PriorityQueue(int capacity = 2);
    ~PriorityQueue();
    void Enqueue(Node element);
    Node Dequeue();
    void Print();
    Node* ComputeHuffmanTree();
};



#endif //PRIORITYQUEUE_H
