#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Node {
    private:
        
    
    public:
        int index;
        int dist;
        Node(int i, int d);
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
private:
    struct Edge {
        int destination;
        int weight;
    };

    int numVertices;
    vector<vector<Edge>> adjacencyList;
    // edge is one destination and the weight of that edge
    // vector<edge> is one vertex's list of edges
    // vector<vector<edge>> is the list of all vertexes and their lists

public:
    Graph(int vertexCount): numVertices(vertexCount), adjacencyList(vertexCount) {}; // creates an empty list for each vertex
    

    
    void addEdge(int source, int destination, int weight); // adds an edge to the graph, if edge already exists, update weight of that edge
    int getEdge(int source, int destination) const; // finds weight of an edge (0 means it does not exist)
    void removeEdge(int source, int destination); // removes an edge if it exists within the graph
    vector<int> getAdjacentVertices(int vertex) const; // get all adjacent vertices from one vertex
    void displayGraph() const; // display the vertices of the graph and their adjacent vertices as well as the weight of the edges to get there
    void dijkstraV1(int s, double* &d, int* &pi);
    void dijkstraV2(int s, int destination, double* &d, int* &pi);
    void dijkstraV3(int s, const vector<int>& destinations, double* &d, int* &pi);
};


int main() { 
    Graph g(6); // vertices 1-5, index 0 unused

    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 14);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 34);
    g.addEdge(4, 5, 58);

    cout << "Graph:" << endl;
    g.displayGraph();

    double* distance = nullptr;
    int* predecessor = nullptr;

    int source = 1;

    g.dijkstraV1(source, distance, predecessor);

    cout << "\nSource: " << source << endl;
    cout << "Vertex\tDistance\tPredecessor\n";

    for (int i = 1; i <= 5; i++) {
        cout << i << "\t"
             << distance[i] << "\t\t"
             << predecessor[i] << endl;
    }

    delete[] distance;
    delete[] predecessor;

    return 0;
}


Node::Node(int i, int d) { 
    index = i;
    dist = d;   
}

int PriorityQueue::getParent(int child) { 
    if (child % 2 == 0) { 
        return (child / 2) - 1;
    } 
    else {
        return child / 2;
    }
}
// move a new node upward until parent has a smaller frequency
// move a node upward until parent has a smaller distance
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2; // find parent index

        if (queue[index].dist < queue[parent].dist) { // if child is smaller than parent
            swap(queue[index], queue[parent]); // swap them

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
            swap(queue[i], queue[smallest]); // swap parent with smallest child

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
        cout << "Queue full" << endl;
        return;
    }

    queue[size] = Node(index, dist); // add new node at end
    table[index] = size; // store position of node in table

    heapifyUp(size); // move node upward if needed
    size++;
}




bool PriorityQueue::isEmpty() const {
    return size == 0;
}
int PriorityQueue::getSize() const {
    return size;
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


Node::Node() {
    index = 0;
    dist = 0;
    
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

// check if a vertex is currently in the priority queue
bool PriorityQueue::contains(int index) const {
    return index >= 0 && index < capacity && table[index] != -1; // valid index and exists in queue
}

void Graph::addEdge(int source, int destination, int weight) {
    // Make sure both vertices exist.
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) { // make sure it is within valid indices (checks before accessing)
        cout << "Invalid vertex." << endl;
        return;
    }

    // Reject weight of 0 because 0 means no edge, why would you create an edge with no edge? you wouldn't pirate a house. (also -1 because dijkstra)
    if (weight <= 0) {
        cout << "Edge weight cannot be zero or negative" << endl;
        return;
    }

    // If this edge already exists, update its weight.
    int i = 0;

    while (i < adjacencyList[source].size()) { 
        if (adjacencyList[source][i].destination == destination) { // if edge already exists
            adjacencyList[source][i].weight = weight; // update weight

            // Find and update the reverse entry.
            int j = 0;
            bool found = false;

            while (j < adjacencyList[destination].size() && !found) {
                if (adjacencyList[destination][j].destination == source) { // if reverse entry 
                    adjacencyList[destination][j].weight = weight; // update reverse entry
                    found = true; // replacement for break lol
                }

                j++;
            }

            return; // weight update, return
        }

        i++;
    }

    // this is a new edge, so add it to both lists.
    adjacencyList[source].push_back({destination, weight});

    if (source != destination) {
        adjacencyList[destination].push_back({source, weight}); // if its not a self loop then add to vector
    }



}


int Graph::getEdge(int source, int destination) const { // const stops from modifying graph data, just reading instead
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) { // verify edges exist before accessing
        cout << "Invalid vertex." << endl;
        return 0;
    }

    int i = 0;

    while (i < adjacencyList[source].size()) {
        if (adjacencyList[source][i].destination == destination) { // find edge
            return adjacencyList[source][i].weight; // return weight of that edge
        }

        i++;
    }

    return 0; // edge not found 
}


void Graph::removeEdge(int source, int destination) { 
    //verify edges exist before accessing
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) { 
        cout << "Invalid vertex." << endl;
        return;
    }

    int i = 0;
    int found = false;

    while (i < adjacencyList[source].size() && !found) { //search and erase
        if (adjacencyList[source][i].destination == destination) { 
            adjacencyList[source].erase(adjacencyList[source].begin() + i);
            found = true;
        }
        i++;
        
    }
    if (source != destination) { // if not self loop
        i = 0;
        found = false;

        while (i < adjacencyList[destination].size() && !found) { // find and erase
            if (adjacencyList[destination][i].destination == source) {
                adjacencyList[destination].erase(adjacencyList[destination].begin() + i);
                found = true;
            }
            i++;
        }
    }

    

}

vector<int> Graph::getAdjacentVertices(int vertex) const {
    vector<int> neighbors; // empty vector to store all neigbors of current vertex

    if (vertex >= numVertices || vertex < 0) { // if vertex is not within range then give error message
        cout << "Invalid Vertex \n";
        return neighbors;
    }

    int i = 0;

    while (i < adjacencyList[vertex].size()) { // add connected vertexes of the current vertex to neighbors vector
        neighbors.push_back(adjacencyList[vertex][i].destination);
        i++;
    }
    return neighbors;
    
}


void Graph::displayGraph() const {
    int vertex = 0;

    while (vertex < numVertices) { 
        cout << vertex << ": "; // current vertex

        int i = 0; // connected edges with their destinations and weights
        while (i < adjacencyList[vertex].size()) {
            cout << "(" << adjacencyList[vertex][i].destination << ", weight " << adjacencyList[vertex][i].weight << ") ";
            i++;
        }
        cout << endl;
        vertex++;
    }
}


void Graph::dijkstraV1(int s, double* &d, int* &pi) {
    
    if (s < 0 || s >= numVertices) { // make sure  source vertex exists
        cout << "Invalid source vertex" << endl;
        d = nullptr;
        pi = nullptr;
        return;
    }

    // Create distance and predecessor arrays
    d = new double[numVertices];
    pi = new int[numVertices];

    
    vector<bool> visited(numVertices, false); // track vertices already done

    
    PriorityQueue pq(numVertices); // make priority queue

    
    for (int i = 0; i < numVertices; i++) { // initialize distances to infinity and predecessors to -1
        d[i] = numeric_limits<double>::infinity();
        pi[i] = -1;
    }

    
    d[s] = 0; // distance from source to itself is zero
    pq.enqueue(s, 0);

    
    while (!pq.isEmpty()) { // continue until all reachable vertices are processed
        
        Node current = pq.dequeue(); // get vertex with smallest current distance
        int u = current.index;

        
        visited[u] = true; // mark current vertex as visited

        
        vector<int> neighbors = getAdjacentVertices(u); // get all adjacent vertices

        for (int v : neighbors) {
            int weight = getEdge(u, v);

         
            if (!visited[v]) {  // only consider vertices not done

                
                if (d[u] + weight < d[v]) { // relax edge if a shorter path is found
                    d[v] = d[u] + weight;
                    pi[v] = u;

                    
                    if (pq.contains(v)) { // update vertex if already in priority queue
                        pq.decreaseKey(v, static_cast<int>(d[v]));
                    }
                    else { // otherwise add vertex to priority queue
                        
                        pq.enqueue(v, static_cast<int>(d[v]));
                    }
                }
            }
        }
    }
}

// find shortest path from source to one destination
void Graph::dijkstraV2(int s, int destination, double* &d, int* &pi) {
    if (s < 0 || s >= numVertices || destination < 0 || destination >= numVertices) { // check if source and destination exist
        cout << "Invalid vertex" << endl;
        d = nullptr;
        pi = nullptr;
        return;
    }

    d = new double[numVertices]; // create distance array
    pi = new int[numVertices]; // create predecessor array

    vector<bool> visited(numVertices, false); // track vertices already done
    PriorityQueue pq(numVertices); // make priority queue

    for (int i = 0; i < numVertices; i++) { // initialize distances and predecessors
        d[i] = numeric_limits<double>::infinity();
        pi[i] = -1;
    }

    d[s] = 0; // source distance is zero
    pq.enqueue(s, 0); // start with source in queue

    while (!pq.isEmpty()) { // continue until destination is found or queue is empty
        Node current = pq.dequeue(); // get vertex with smallest distance
        int u = current.index;

        visited[u] = true; // mark vertex as done

        if (u == destination) { // if destination is reached, shortest path is found
            return;
        }

        vector<int> neighbors = getAdjacentVertices(u); // get all adjacent vertices

        for (int v : neighbors) {
            int weight = getEdge(u, v); // get weight between current vertex and neighbor

            if (!visited[v]) { // only check vertices not done

                if (d[u] + weight < d[v]) { // check if going through u gives a shorter path
                    d[v] = d[u] + weight; // update shortest distance
                    pi[v] = u; // update predecessor to current vertex

                    if (pq.contains(v)) { // if vertex already in queue, update its distance
                        pq.decreaseKey(v, static_cast<int>(d[v]));
                    }
                    else {
                        pq.enqueue(v, static_cast<int>(d[v])); // otherwise add it to queue
                    }
                }
            }
        }
    }
}

// find shortest paths from source to a list of destinations
void Graph::dijkstraV3(int s, const vector<int>& destinations, double* &d, int* &pi) {
    if (s < 0 || s >= numVertices) { // check if source exists
        cout << "Invalid source vertex" << endl;
        d = nullptr;
        pi = nullptr;
        return;
    }

    for (int v : destinations) { // make sure all destinations exist
        if (v < 0 || v >= numVertices) {
            cout << "Invalid destination vertex" << endl;
            d = nullptr;
            pi = nullptr;
            return;
        }
    }

    d = new double[numVertices]; // create distance array
    pi = new int[numVertices]; // create predecessor array

    vector<bool> visited(numVertices, false); // track vertices already done
    vector<bool> target(numVertices, false); // track which vertices are destinations

    PriorityQueue pq(numVertices); // make priority queue

    int remaining = 0; // number of destinations left to reach

    for (int v : destinations) { // mark all destinations in target array
        if (!target[v]) { // avoid counting duplicate destinations
            target[v] = true;
            remaining++;
        }
    }

    for (int i = 0; i < numVertices; i++) { // initialize distances and predecessors
        d[i] = numeric_limits<double>::infinity();
        pi[i] = -1;
    }

    d[s] = 0; // source distance is zero
    pq.enqueue(s, 0); // start with source in queue

    while (!pq.isEmpty() && remaining > 0) { // continue until all destinations found or queue empty
        Node current = pq.dequeue(); // get vertex with smallest distance
        int u = current.index;

        visited[u] = true; // mark vertex as done

        if (target[u]) { // if current vertex is one of the destinations
            remaining--; // one less destination to find
        }

        if (remaining == 0) { // all destinations reached
            return;
        }

        vector<int> neighbors = getAdjacentVertices(u); // get all adjacent vertices

        for (int v : neighbors) {
            int weight = getEdge(u, v); // get weight between current vertex and neighbor

            if (!visited[v]) { // only check vertices not done

                if (d[u] + weight < d[v]) { // check if going through u gives a shorter path
                    d[v] = d[u] + weight; // update shortest distance
                    pi[v] = u; // update predecessor to current vertex

                    if (pq.contains(v)) { // if vertex already in queue, update its distance
                        pq.decreaseKey(v, static_cast<int>(d[v]));
                    }
                    else {
                        pq.enqueue(v, static_cast<int>(d[v])); // otherwise add it to queue
                    }
                }
            }
        }
    }
}