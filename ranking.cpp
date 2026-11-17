
#include "ranking.h"
#include "graph.h"

// Decides which entity should come first
// Higher connections get higher priority.
// If connections are equal, smaller ID comes first.

bool EntityPriorityQueue::hasHigherPriority(RankedEntity a, RankedEntity b) {

    if (a.connectionCount != b.connectionCount) {
        return a.connectionCount > b.connectionCount;
    }

    return a.id < b.id;
}


// Combines two sorted parts of an array
void merge(RankedEntity entities[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    RankedEntity* leftArray = new RankedEntity[n1];
    RankedEntity* rightArray = new RankedEntity[n2];

    // Copy the left part
    for (int i = 0; i < n1; i++) {
        leftArray[i] = entities[left + i];
    }

    // Copy the right part
    for (int j = 0; j < n2; j++) {
        rightArray[j] = entities[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // Merge both parts in descending order
    while (i < n1 && j < n2) {

        if (leftArray[i].connectionCount > rightArray[j].connectionCount ||
            (leftArray[i].connectionCount == rightArray[j].connectionCount &&
             leftArray[i].id < rightArray[j].id)) {

            entities[k] = leftArray[i];
            i++;
        }
        else {

            entities[k] = rightArray[j];
            j++;
        }

        k++;
    }

    // Copy any remaining elements
    while (i < n1) {
        entities[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        entities[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}


// Recursively divides and sorts the array
void mergeSort(RankedEntity entities[], int left, int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(entities, left, mid);
    mergeSort(entities, mid + 1, right);

    merge(entities, left, mid, right);
}


// Constructor
EntityPriorityQueue::EntityPriorityQueue(int capacity) {

    if (capacity <= 0) {
        capacity = 100;
    }

    this->capacity = capacity;
    heapSize = 0;

    heap = new RankedEntity[capacity];
}


// Destructor
EntityPriorityQueue::~EntityPriorityQueue() {

    delete[] heap;
}


// Moves an entity upwards to maintain the Max Heap
void EntityPriorityQueue::heapifyUp(int index) {

    while (index > 0) {

        int parent = (index - 1) / 2;

        if (hasHigherPriority(heap[parent], heap[index])) {
            break;
        }

        RankedEntity temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;

        index = parent;
    }
}


// Moves an entity downwards to maintain the Max Heap
void EntityPriorityQueue::heapifyDown(int index) {

    while (true) {

        int largest = index;

        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heapSize &&
            hasHigherPriority(heap[left], heap[largest])) {

            largest = left;
        }

        if (right < heapSize &&
            hasHigherPriority(heap[right], heap[largest])) {

            largest = right;
        }

        if (largest == index) {
            break;
        }

        RankedEntity temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;

        index = largest;
    }
}


// Inserts a new entity into the priority queue
bool EntityPriorityQueue::insert(RankedEntity entity) {

    if (heapSize == capacity) {
        cout << "Priority queue is full.\n";
        return false;
    }

    if (entity.connectionCount < 0) {
        return false;
    }

    heap[heapSize] = entity;

    heapifyUp(heapSize);

    heapSize++;

    return true;
}


// Returns the entity with the highest priority
bool EntityPriorityQueue::getTop(RankedEntity& result) {

    if (heapSize == 0) {
        return false;
    }

    result = heap[0];

    return true;
}


// Removes the entity with the highest priority
bool EntityPriorityQueue::removeTop() {

    if (heapSize == 0) {
        return false;
    }

    heap[0] = heap[heapSize - 1];

    heapSize--;

    if (heapSize > 0) {
        heapifyDown(0);
    }

    return true;
}


// Checks whether the queue is empty
bool EntityPriorityQueue::isEmpty() {

    return heapSize == 0;
}


// Displays the top N highly connected entities
void EntityPriorityQueue::displayTopEntities(int count) {

    if (isEmpty()) {
        cout << "No entities available for ranking.\n";
        return;
    }

    if (count <= 0) {
        cout << "Invalid number of entities.\n";
        return;
    }

    cout << "\n===== MOST CONNECTED ENTITIES =====\n";

    int limit = (count < heapSize) ? count : heapSize;

    for (int i = 0; i < limit; i++) {

        RankedEntity topEntity;

        getTop(topEntity);

        cout << i + 1 << ". "
             << topEntity.name
             << " (" << topEntity.id << ")"
             << " - "
             << topEntity.connectionCount
             << " connections - ";

        if (topEntity.isPerson) {
            cout << "Person";
        }
        else {
            cout << "Case";
        }

        cout << endl;

        removeTop();
    }
}

// Loads people and cases from the graph into the ranking array
int loadEntitiesForRanking(const Graph& graph,
                           RankedEntity entities[],
                           int capacity)
{
    const vector<Vertex>& vertices = graph.getVertices();
    const vector<vector<int>>& adjList = graph.getAdjacencyList();

    int totalVertices = vertices.size();

    if (capacity < totalVertices)
    {
        cout << "Error: Not enough space in ranking array.\n";
        return -1;
    }

    for (int i = 0; i < totalVertices; i++)
    {
        entities[i].id = vertices[i].id;
        entities[i].name = vertices[i].name;
        entities[i].connectionCount = adjList[i].size();
        entities[i].isPerson = vertices[i].isPerson;
    }

    return totalVertices;
}
