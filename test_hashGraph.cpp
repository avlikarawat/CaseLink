#include "graph.h"
#include "hashTable.h"

int main()
{
    Graph g;

    // Add people
    g.addPerson("P101", "Rahul");
    g.addPerson("P102", "Priya");
    g.addPerson("P103", "Aman");

    // Add cases
    g.addCase("C201", "Cyber Fraud");
    g.addCase("C202", "Financial Fraud");

    // Add relationships
    g.addRelationship("P101", "C201");
    g.addRelationship("P102", "C201");
    g.addRelationship("P102", "C202");
    g.addRelationship("P103", "C202");

    // Create Hash Table
    HashTable ht(101);

    cout << "\n===== LOADING GRAPH INTO HASH TABLE =====\n";

    int count = ht.loadFromGraph(g);

    cout << "Total entities loaded: " << count << endl;

    // Display Hash Table
    ht.display();

    // Search for a person
    cout << "\n===== SEARCHING PERSON =====\n";

    HashNode* result = ht.search("P102");

    if (result != nullptr)
    {
        cout << "Found: " << result->name << endl;
    }
    else
    {
        cout << "Person not found!\n";
    }

    // Search for a case
    cout << "\n===== SEARCHING CASE =====\n";

    result = ht.search("C201");

    if (result != nullptr)
    {
        cout << "Found: " << result->name << endl;
    }
    else
    {
        cout << "Case not found!\n";
    }

    // Search for invalid ID
    cout << "\n===== SEARCHING INVALID ID =====\n";

    result = ht.search("P999");

    if (result == nullptr)
    {
        cout << "Entity not found!\n";
    }

    return 0;
}