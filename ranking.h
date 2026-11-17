
#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <string>
using namespace std;

// Tells the compiler that Graph is defined elsewhere
class Graph;

// Stores the information needed to rank an entity
struct RankedEntity {
    string id;
    string name;
    int connectionCount;
    bool isPerson;
};

// Merge Sort
void merge(RankedEntity entities[], int left, int mid, int right);
void mergeSort(RankedEntity entities[], int left, int right);

// Priority Queue using Max Heap
class EntityPriorityQueue {

private:

    RankedEntity* heap;
    int capacity;
    int heapSize;

    void heapifyUp(int index);
    void heapifyDown(int index);

    bool hasHigherPriority(RankedEntity a, RankedEntity b);

public:

    EntityPriorityQueue(int capacity = 100);
    ~EntityPriorityQueue();

    bool insert(RankedEntity entity);
    bool getTop(RankedEntity& result);
    bool removeTop();
    bool isEmpty();

    void displayTopEntities(int count);
};

// Loads graph data into an array for ranking
int loadEntitiesForRanking(const Graph& graph,
                           RankedEntity entities[],
                           int capacity);

#endif
