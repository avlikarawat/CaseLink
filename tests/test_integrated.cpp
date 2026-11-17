
#include "graph.h"
#include "ranking.h"

int main()
{
    Graph g;

    // Add people
    g.addPerson("P101", "Rahul");
    g.addPerson("P102", "Priya");
    g.addPerson("P103", "Aman");
    g.addPerson("P104", "Neha");

    // Add cases
    g.addCase("C201", "Cyber Fraud");
    g.addCase("C202", "Financial Fraud");
    g.addCase("C203", "Identity Theft");

    // Add relationships
    g.addRelationship("P101", "C201");
    g.addRelationship("P101", "C202");

    g.addRelationship("P102", "C201");
    g.addRelationship("P102", "C202");
    g.addRelationship("P102", "C203");

    g.addRelationship("P103", "C201");

    g.addRelationship("P104", "C203");

    cout << "\n===== GRAPH NETWORK =====\n";

    g.displayNetwork();

    // Create an array for ranking
    RankedEntity entities[100];

    // Load graph data into the array
    int total = loadEntitiesForRanking(g, entities, 100);

    if (total == -1)
    {
        return 1;
    }

    // Display connection counts using Merge Sort
    mergeSort(entities, 0, total - 1);

    cout << "\n===== MERGE SORT RANKING =====\n";

    for (int i = 0; i < total; i++)
    {
        cout << entities[i].name
             << " - "
             << entities[i].connectionCount
             << " connections\n";
    }

    // Create a priority queue
    EntityPriorityQueue pq(100);

    for (int i = 0; i < total; i++)
    {
        pq.insert(entities[i]);
    }

    // Display top 5 entities
    pq.displayTopEntities(5);

    return 0;
}
