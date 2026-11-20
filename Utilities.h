#ifndef UTILITIES_H
#define UTILITIES_H

class Node {
    private:
        
    
    public:
        int index;
        int dist;
        int weight;
        char ch;
        Node(int i, int d);
        Node(int w, char c);
        Node();
};
class PriorityQueue {
    private:
        Node* queue;
        int* table;
        int size;
        int capacity;

        void heapifyUp(int index);
        void heapifyDown(int i, int size);
    public:
        PriorityQueue(int c);
        PriorityQueue();
        ~PriorityQueue();

        void enqueue(int index, int dist);
        Node dequeue();

        bool isEmpty() const;
        int getSize() const;

        void decreaseKey(int index, int value);
        int getParent(int child);

        bool contains(int index) const;
};

class Graph {

};

void menuLoop();



#endif