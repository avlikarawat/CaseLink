
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Stores information about a person
struct Person
{
    string id;
    string name;
};

// Stores information about a case
struct Case
{
    string id;
    string title;
};

// Represents any vertex in our graph
struct Vertex
{
    string id;
    string name;
    bool isPerson;
};

class Graph
{
private:
    vector<Person> people;
    vector<Case> cases;

    // Stores all graph vertices
    vector<Vertex> vertices;

    // Adjacency list: each vertex stores its connected vertices
    vector<vector<int>> adjList;

    // Finds the index of a vertex using its ID
    int findVertexIndex(string id);

public:
    // Add people and cases to the graph
    bool addPerson(string id, string name);
    bool addCase(string id, string title);

    // Connect a person to a case
    bool addRelationship(string personID, string caseID);

    // Display the complete relationship network
    void displayNetwork();

    // Get connection counts
    int getPersonConnectionCount(string personID);
    int getCaseConnectionCount(string caseID);

    // Allow other modules to access the graph
    const vector<Vertex>& getVertices() const;
    const vector<vector<int>>& getAdjacencyList() const;
};

#endif
