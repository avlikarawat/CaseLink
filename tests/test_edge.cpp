
#include "graph.h"

int main()
{
    Graph g;

    cout << "\n===== TEST 1: ADDING VALID DATA =====\n";

    g.addPerson("P101", "Rahul");
    g.addPerson("P102", "Priya");

    g.addCase("C201", "Cyber Fraud");
    g.addCase("C202", "Financial Fraud");


    cout << "\n===== TEST 2: DUPLICATE PERSON ID =====\n";

    g.addPerson("P101", "Aman");


    cout << "\n===== TEST 3: DUPLICATE CASE ID =====\n";

    g.addCase("C201", "Robbery");


    cout << "\n===== TEST 4: INVALID PERSON ID =====\n";

    g.addRelationship("P999", "C201");


    cout << "\n===== TEST 5: INVALID CASE ID =====\n";

    g.addRelationship("P101", "C999");


    cout << "\n===== TEST 6: DUPLICATE RELATIONSHIP =====\n";

    g.addRelationship("P101", "C201");
    g.addRelationship("P101", "C201");


    cout << "\n===== TEST 7: INVALID RELATIONSHIP =====\n";

    // Trying to connect two people
    g.addRelationship("P101", "P102");

    // Trying to connect two cases
    g.addRelationship("C201", "C202");


    cout << "\n===== FINAL GRAPH =====\n";

    g.displayNetwork();

    return 0;
}
