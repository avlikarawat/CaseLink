
#include "graph.h"

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

    // Create relationships
    g.addRelationship("P101", "C201");
    g.addRelationship("P102", "C201");
    g.addRelationship("P102", "C202");
    g.addRelationship("P103", "C202");

    // Display the graph
    g.displayNetwork();

    // Test connection counts
    cout << "\nRahul's connections: "
         << g.getPersonConnectionCount("P101");

    cout << "\nCyber Fraud connections: "
         << g.getCaseConnectionCount("C201");

    cout << "\n";

    return 0;
}
