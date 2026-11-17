#include "hashTable.h"
#include "graph.h"

// Constructor
HashTable::HashTable(int size)
{
    // Ensure capacity is positive
    if (size <= 0)
    {
        size = 101;
    }

    capacity = size;

    // Create an array of linked-list pointers
    table = new HashNode*[capacity];

    // Initially, every bucket is empty
    for (int i = 0; i < capacity; i++)
    {
        table[i] = nullptr;
    }
}

// Hash function
int HashTable::hashFunction(string id)
{
    unsigned long hashValue = 0;

    for (int i = 0; i < id.length(); i++)
    {
        hashValue = (hashValue * 31 + id[i]) % capacity;
    }

    return hashValue;
}

// Insert an entity into the hash table
bool HashTable::insert(string id, string name, bool isPerson)
{
    // Do not allow duplicate IDs
    if (search(id) != nullptr)
    {
        cout << "Error: ID already exists in Hash Table!\n";
        return false;
    }

    int index = hashFunction(id);

    // Create a new node
    HashNode* newNode = new HashNode;

    newNode->id = id;
    newNode->name = name;
    newNode->isPerson = isPerson;

    // Insert at the beginning of the linked list
    newNode->next = table[index];
    table[index] = newNode;

    cout << "Entity inserted successfully!\n";

    return true;
}

// Search for an entity using its ID
HashNode* HashTable::search(string id)
{
    int index = hashFunction(id);

    HashNode* current = table[index];

    // Traverse the linked list at this bucket
    while (current != nullptr)
    {
        if (current->id == id)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// Display only occupied buckets
void HashTable::display()
{
    cout << "\n===== HASH TABLE =====\n";

    bool found = false;

    for (int i = 0; i < capacity; i++)
    {
        // Display only non-empty buckets
        if (table[i] != nullptr)
        {
            found = true;

            cout << "Bucket " << i << ": ";

            HashNode* current = table[i];

            while (current != nullptr)
            {
                cout << current->id
                     << " (" << current->name << ")";

                if (current->next != nullptr)
                {
                    cout << " -> ";
                }

                current = current->next;
            }

            cout << endl;
        }
    }

    if (!found)
    {
        cout << "Hash Table is empty!\n";
    }
}

// Destructor
HashTable::~HashTable()
{
    // Delete every linked list
    for (int i = 0; i < capacity; i++)
    {
        HashNode* current = table[i];

        while (current != nullptr)
        {
            HashNode* temp = current;
            current = current->next;

            delete temp;
        }
    }

    // Delete the array itself
    delete[] table;
}

// Loads all people and cases from Graph into Hash Table
int HashTable::loadFromGraph(const Graph& graph)
{
    const vector<Vertex>& vertices = graph.getVertices();

    int insertedCount = 0;

    for (int i = 0; i < vertices.size(); i++)
    {
        bool success = insert(
            vertices[i].id,
            vertices[i].name,
            vertices[i].isPerson
        );

        if (success)
        {
            insertedCount++;
        }
    }

    return insertedCount;
}