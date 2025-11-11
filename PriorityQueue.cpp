#include "PriorityQueue.h"
#include <iostream>
#include "Node.h"
PriorityQueue::PriorityQueue(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->array = new Node[this->capacity];
}
PriorityQueue::~PriorityQueue() {
    delete[] this->array;
    this->array = nullptr;
    this->size = 0;
    this->capacity = 0;
}

void PriorityQueue::Enqueue(Node element) {
    if (this->size == this->capacity) {
        this->capacity *= 2;
        Node* tempArray = new Node[this->capacity];
        for (int i = 0; i < this->size; i++) {
            tempArray[i] = this->array[i];
        }
        delete[] this->array;
        this->array = tempArray;
    }

    // Binary search to find insertion index
    int left = 0, right = this->size - 1, mid, insertIndex = this->size;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (this->array[mid].frequency == element.frequency) {
            insertIndex = mid;
            break;
        }
        if (this->array[mid].frequency < element.frequency) {
            right = mid - 1;
            insertIndex = mid;  // Original comparison
        } else {
            left = mid + 1;
        }
    }

    // Shift elements to the right
    for (int i = this->size; i > insertIndex; i--) {
        this->array[i] = this->array[i - 1];
    }

    // Insert element
    this->array[insertIndex] = element;
    this->size++;
}

Node PriorityQueue::Dequeue() {
    if (this->size == 0) {
        throw std::runtime_error("Dequeue is empty");
    }
    else {
        return this->array[--this->size];
    }
}

void PriorityQueue::Print() {
    for (int i = 0; i < this->size; i++) {
        std::cout << this->array[i] << std::endl;
    }
}

Node* PriorityQueue::ComputeHuffmanTree() {
    while (this->size > 1) {
        Node* left = new Node(this->Dequeue());
        Node* right = new Node(this->Dequeue());

        Node* parent = new Node(left->frequency + right->frequency,'\0' , left , right);
        this->Enqueue(*parent);
    }
    return new Node(this->Dequeue());
}