#include "Utilities.h"
#include <iostream>

Node::Node(int i, int d) { 
    index = i;
    dist = d;  
    ch = '\0'; // fix later
    weight = -1; // fix later
}
Node::Node(int w, char c) {
    weight = w; 
    ch = c;
    index = 0; // fix later
    dist = 0; // fix later
}
Node::Node() {
    index = 0;
    dist = 0;
    ch = '\0'; // fix later
    weight = -1; // fix later
    
}

// move a new node upward until parent has a smaller frequency
// move a node upward until parent has a smaller distance
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2; // find parent index

        if (queue[index].dist < queue[parent].dist) { // if child is smaller than parent
            std::swap(queue[index], queue[parent]); // swap them

            table[queue[index].index] = index; // update positions in table after swap
            table[queue[parent].index] = parent;

            index = parent; // move up to parent position
        }
        else {
            return; // node is in correct position
        }
    }
}

// move a node down by swapping with its smallest child
void PriorityQueue::heapifyDown(int i, int size) {
    while (true) {
        int left = 2 * i + 1; // left child index
        int right = 2 * i + 2; // right child index
        int smallest = i;

        if (left < size && queue[left].dist < queue[smallest].dist) {
            smallest = left; // left child is smaller
        }

        if (right < size && queue[right].dist < queue[smallest].dist) {
            smallest = right; // right child is smaller
        }

        if (smallest != i) { // if parent is not the smallest
            std::swap(queue[i], queue[smallest]); // swap parent with smallest child

            table[queue[i].index] = i; // update positions after swap
            table[queue[smallest].index] = smallest;

            i = smallest; // continue checking from new position
        }
        else {
            return; // node is in correct position
        }
    }
}
// allocate heap array and table
PriorityQueue::PriorityQueue(int c) {
    capacity = c;
    size = 0;

    queue = new Node[capacity]; // create array for heap
    table = new int[capacity]; // create array to track positions of nodes

    for (int i = 0; i < capacity; i++) {
        table[i] = -1; // -1 means vertex is not in queue
    }
}
PriorityQueue::PriorityQueue() {
    capacity = 0;
    size = 0;
    queue = nullptr;
    table = nullptr;
}
//destructor
PriorityQueue::~PriorityQueue() {
    delete[] queue;
    delete[] table;
}
// add node to end of heap then move it to correct position
void PriorityQueue::enqueue(int index, int dist) {
    if (size >= capacity) { // check if queue is full
        std::cout << "Queue full" << std::endl;
        return;
    }

    queue[size] = Node(index, dist); // add new node at end
    table[index] = size; // store position of node in table

    heapifyUp(size); // move node upward if needed
    size++;
}
// remove and return node with smallest distance
Node PriorityQueue::dequeue() {
    if (size == 0) {
        return Node(-1, 0); // empty queue
    }

    Node temp = queue[0]; // save smallest node to return

    table[temp.index] = -1; // node is no longer in queue

    size--;

    if (size > 0) {
        queue[0] = queue[size]; // move last node to root
        table[queue[0].index] = 0; // update its position in table

        heapifyDown(0, size); // move root down to correct position
    }

    return temp;
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}
int PriorityQueue::getSize() const {
    return size;
}
// update distance of a node and fix its position in heap
void PriorityQueue::decreaseKey(int index, int dist) {
    int position = table[index]; // find position of vertex in heap

    if (position == -1) {
        return; // vertex not in queue
    }

    if (dist < queue[position].dist) { // only update if new distance is smaller
        queue[position].dist = dist; // update distance
        heapifyUp(position); // move node upward if needed
    }
}
int PriorityQueue::getParent(int child) { 
    if (child % 2 == 0) { 
        return (child / 2) - 1;
    } 
    else {
        return child / 2;
    }
}
// check if a vertex is currently in the priority queue
bool PriorityQueue::contains(int index) const {
    return index >= 0 && index < capacity && table[index] != -1; // valid index and exists in queue
}

void menuLoop() {
    std::cout << "=-------------------------=" << std::endl;
    std::cout << "=------- MAIN MENU -------=" << std::endl;
    std::cout << "=-------------------------=" << std::endl;
    std::cout << "=---- 1. Select Map ------=" << std::endl;
    std::cout << "=---- 2. Import Map ------=" << std::endl;
    std::cout << "=---- 3. Start Game ------=" << std::endl;
    std::cout << "--------------------------=" << std::endl;
    std::cout << "=---- 4.   Quit     ------=" << std::endl;
    std::cout << "=-------------------------=" << std::endl;
}


