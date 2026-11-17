
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
using namespace std;

class Graph; 

// Each node stores one entity
struct HashNode
{
    string id;
    string name;
    bool isPerson;

    HashNode* next;
};

class HashTable
{
private:

    HashNode** table;
    int capacity;

    // Converts an ID into a valid array index
    int hashFunction(string id);

public:

    HashTable(int size = 101);
    ~HashTable();

    // Inserts a person or case
    bool insert(string id, string name, bool isPerson);

    // Searches for an entity using its ID
    HashNode* search(string id);

    // Displays the complete hash table
    void display();
    int loadFromGraph(const Graph& graph);
};

#endif
