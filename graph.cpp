
#include "graph.h"

// Finds a vertex using its ID
int Graph::findVertexIndex(string id)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// Adds a person to the graph
bool Graph::addPerson(string id, string name)
{
    // Check whether this ID already exists
    if (findVertexIndex(id) != -1)
    {
        cout << "Error: ID already exists!" << endl;
        return false;
    }

    Person newPerson;
    newPerson.id = id;
    newPerson.name = name;

    people.push_back(newPerson);

    Vertex newVertex;
    newVertex.id = id;
    newVertex.name = name;
    newVertex.isPerson = true;

    vertices.push_back(newVertex);
    adjList.push_back(vector<int>());

    cout << "Person added successfully!" << endl;
    return true;
}

// Adds a case to the graph
bool Graph::addCase(string id, string title)
{
    if (findVertexIndex(id) != -1)
    {
        cout << "Error: ID already exists!" << endl;
        return false;
    }

    Case newCase;
    newCase.id = id;
    newCase.title = title;

    cases.push_back(newCase);

    Vertex newVertex;
    newVertex.id = id;
    newVertex.name = title;
    newVertex.isPerson = false;

    vertices.push_back(newVertex);
    adjList.push_back(vector<int>());

    cout << "Case added successfully!" << endl;
    return true;
}

// Connects a person with a case
bool Graph::addRelationship(string personID, string caseID)
{
    int personIndex = findVertexIndex(personID);
    int caseIndex = findVertexIndex(caseID);

    // Check whether both IDs exist
    if (personIndex == -1 || caseIndex == -1)
    {
        cout << "Error: Person or Case not found!" << endl;
        return false;
    }

    // Make sure the first vertex is a person
    // and the second vertex is a case
    if (!vertices[personIndex].isPerson ||
        vertices[caseIndex].isPerson)
    {
        cout << "Error: Invalid relationship!" << endl;
        return false;
    }

    // Check whether the relationship already exists
    for (int i = 0; i < adjList[personIndex].size(); i++)
    {
        if (adjList[personIndex][i] == caseIndex)
        {
            cout << "Error: Relationship already exists!" << endl;
            return false;
        }
    }

    // Add an undirected edge
    adjList[personIndex].push_back(caseIndex);
    adjList[caseIndex].push_back(personIndex);

    cout << "Relationship added successfully!" << endl;
    return true;
}

// Displays the entire relationship network
void Graph::displayNetwork()
{
    cout << "\n===== CASELINK RELATIONSHIP NETWORK =====\n";

    for (int i = 0; i < vertices.size(); i++)
    {
        cout << "\n";

        if (vertices[i].isPerson)
        {
            cout << "Person: ";
        }
        else
        {
            cout << "Case: ";
        }

        cout << vertices[i].name << " (" << vertices[i].id << ")";

        cout << "\nConnected to: ";

        if (adjList[i].empty())
        {
            cout << "No connections";
        }
        else
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                int neighbourIndex = adjList[i][j];

                cout << vertices[neighbourIndex].name
                     << " (" << vertices[neighbourIndex].id << ")";

                if (j != adjList[i].size() - 1)
                {
                    cout << ", ";
                }
            }
        }

        cout << endl;
    }
}

// Returns the number of cases connected to a person
int Graph::getPersonConnectionCount(string personID)
{
    int index = findVertexIndex(personID);

    if (index == -1 || !vertices[index].isPerson)
    {
        return -1;
    }

    return adjList[index].size();
}

// Returns the number of people connected to a case
int Graph::getCaseConnectionCount(string caseID)
{
    int index = findVertexIndex(caseID);

    if (index == -1 || vertices[index].isPerson)
    {
        return -1;
    }

    return adjList[index].size();
}

// Gives access to the vertices
const vector<Vertex>& Graph::getVertices() const
{
    return vertices;
}

// Gives access to the adjacency list
const vector<vector<int>>& Graph::getAdjacencyList() const
{
    return adjList;
}
