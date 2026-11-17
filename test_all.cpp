#include "graph.h"
#include "hashTable.h"
#include "ranking.h"

int main()
{
    Graph g;

    // ===== ADD PEOPLE =====
    g.addPerson("P101", "Rahul");
    g.addPerson("P102", "Priya");
    g.addPerson("P103", "Aman");
    g.addPerson("P104", "Neha");

    // ===== ADD CASES =====
    g.addCase("C201", "Cyber Fraud");
    g.addCase("C202", "Financial Fraud");
    g.addCase("C203", "Identity Theft");

    // ===== ADD RELATIONSHIPS =====
    g.addRelationship("P101", "C201");
    g.addRelationship("P101", "C202");

    g.addRelationship("P102", "C201");
    g.addRelationship("P102", "C202");
    g.addRelationship("P102", "C203");

    g.addRelationship("P103", "C201");

    g.addRelationship("P104", "C203");

    // ===== GRAPH DISPLAY =====
    cout << "\n===== GRAPH NETWORK =====\n";
    g.displayNetwork();

    // ===== HASH TABLE =====
    cout << "\n===== HASH TABLE INTEGRATION =====\n";

    HashTable ht(101);

    int loaded = ht.loadFromGraph(g);

    cout << "Entities loaded: " << loaded << endl;

    ht.display();

    // Search for an entity
    cout << "\n===== HASH SEARCH =====\n";

    HashNode* result = ht.search("P102");

    if (result != nullptr)
    {
        cout << "Entity found: " << result->name << endl;
    }
    else
    {
        cout << "Entity not found!\n";
    }

    // ===== RANKING MODULE =====
    cout << "\n===== RANKING MODULE =====\n";

    RankedEntity entities[100];

    int total = loadEntitiesForRanking(g, entities, 100);

    if (total == -1)
    {
        return 1;
    }

    // Sort using Merge Sort
    mergeSort(entities, 0, total - 1);

    cout << "\n===== MERGE SORT RANKING =====\n";

    for (int i = 0; i < total; i++)
    {
        cout << entities[i].name
             << " - "
             << entities[i].connectionCount
             << " connections\n";
    }

    // Priority Queue
    cout << "\n===== PRIORITY QUEUE =====\n";

    EntityPriorityQueue pq(100);

    for (int i = 0; i < total; i++)
    {
        pq.insert(entities[i]);
    }

    pq.displayTopEntities(5);

    return 0;
}