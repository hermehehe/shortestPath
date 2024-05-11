#ifndef _MYQUEUE_HPP_
#define _MYQUEUE_HPP_
#include <iostream>
#include "QueueEntry.hpp"
//Hermela Gebretsion

class MyQueue {

    public:
    MyQueue(int cap);
    ~MyQueue();

    //memeber functions
    void heapifyUp(int pos); //restructures for when new value is inserted into heap
    void heapifyDown(int pos); //restructures for when new value is removed from heap
    int extractMin();
    bool isEmpty();
    void add_with_priority(int v, double weight);
    void decrease_priority(int v, double weight);

    
    private:
    QueueEntry* minHeap; //this is a dynamic array of Vertex pointers
    int capacity;
    int size;

};


#endif