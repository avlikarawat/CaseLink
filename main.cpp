
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "graph.h"
#include "hashTable.h"
#include "ranking.h"
#include "algorithms.h"

using namespace std;

// ======================================
// DISPLAY MAIN MENU
// ======================================

void displayMenu()
{
    cout << "\n";
    cout << "========================================\n";
    cout << "             CASELINK SYSTEM             \n";
    cout << "========================================\n";

    cout << "1.  Add Person\n";
    cout << "2.  Add Case\n";
    cout << "3.  Connect Person to Case\n";
    cout << "4.  Display Relationship Network\n";
    cout << "5.  Search Entity using Hash Table\n";
    cout << "6.  Display Hash Table\n";
    cout << "7.  BFS Traversal\n";
    cout << "8.  DFS Traversal\n";
    cout << "9.  Find Shortest Connection Path\n";
    cout << "10. Find Common Connections\n";
    cout << "11. Connection Depth Analysis\n";
    cout << "12. Rank Entities using Merge Sort\n";
    cout << "13. Rank Entities using Priority Queue\n";
    cout << "14. Exit\n";

    cout << "========================================\n";
    cout << "Enter your choice: ";
}


// ======================================
// RANK USING MERGE SORT
// ======================================

void rankUsingMergeSort(const Graph& graph)
{
    const int MAX = 500;

    RankedEntity entities[MAX];

    int count = loadEntitiesForRanking(
        graph, entities, MAX
    );

    if (count <= 0)
    {
        cout << "No entities available for ranking.\n";
        return;
    }

    mergeSort(entities, 0, count - 1);

    cout << "\n===== RANKING USING MERGE SORT =====\n";

    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". "
             << entities[i].name
             << " (" << entities[i].id << ")"
             << " - "
             << entities[i].connectionCount
             << " connections - ";

        if (entities[i].isPerson)
            cout << "Person";
        else
            cout << "Case";

        cout << endl;
    }
}


// ======================================
// RANK USING PRIORITY QUEUE
// ======================================

void rankUsingPriorityQueue(const Graph& graph)
{
    const int MAX = 500;

    RankedEntity entities[MAX];

    int count = loadEntitiesForRanking(
        graph, entities, MAX
    );

    if (count <= 0)
    {
        cout << "No entities available for ranking.\n";
        return;
    }

    EntityPriorityQueue pq(count);

    for (int i = 0; i < count; i++)
    {
        pq.insert(entities[i]);
    }

    int number;

    cout << "\nHow many top entities do you want to display? ";
    cin >> number;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }

    pq.displayTopEntities(number);
}
void loadData(Graph& graph, HashTable& hashTable)
{
    ifstream file("caselink_data.txt");

    if (!file.is_open())
    {
        cout << "Could not open caselink_data.txt" << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos)
            continue;

        string type = line.substr(0, first);
        string id = line.substr(first + 1, second - first - 1);
        string value = line.substr(second + 1);

        if (type == "P")
        {
            if (graph.addPerson(id, value))
                hashTable.insert(id, value, true);
        }
        else if (type == "C")
        {
            if (graph.addCase(id, value))
                hashTable.insert(id, value, false);
        }
        else if (type == "R")
        {
            graph.addRelationship(id, value);
        }
    }

    file.close();
    cout << "Sample database loaded successfully!" << endl;
}

// ======================================
// MAIN FUNCTION
// ======================================

int main()
{
    Graph graph;

    HashTable hashTable(101);
    loadData(graph, hashTable);
    int choice;

    string id;
    string name;
    string firstID;
    string secondID;

    cout << "\n========================================\n";
    cout << "       WELCOME TO CASELINK SYSTEM        \n";
    cout << "========================================\n";

    do
    {
        displayMenu();

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            cout << "Invalid choice! Enter a number.\n";
            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );


        switch (choice)
        {

            // --------------------------------
            // 1. ADD PERSON
            // --------------------------------

            case 1:

                cout << "Enter Person ID: ";
                getline(cin, id);

                cout << "Enter Person Name: ";
                getline(cin, name);

                if (graph.addPerson(id, name))
                {
                    hashTable.insert(id, name, true);
                }

                break;


            // --------------------------------
            // 2. ADD CASE
            // --------------------------------

            case 2:

                cout << "Enter Case ID: ";
                getline(cin, id);

                cout << "Enter Case Title: ";
                getline(cin, name);

                if (graph.addCase(id, name))
                {
                    hashTable.insert(id, name, false);
                }

                break;


            // --------------------------------
            // 3. ADD RELATIONSHIP
            // --------------------------------

            case 3:

                cout << "Enter Person ID: ";
                getline(cin, firstID);

                cout << "Enter Case ID: ";
                getline(cin, secondID);

                graph.addRelationship(firstID, secondID);

                break;


            // --------------------------------
            // 4. DISPLAY NETWORK
            // --------------------------------

            case 4:

                graph.displayNetwork();

                break;


            // --------------------------------
            // 5. SEARCH USING HASH TABLE
            // --------------------------------

            case 5:

                cout << "Enter Entity ID to search: ";
                getline(cin, id);

                {
                    HashNode* result = hashTable.search(id);

                    if (result != nullptr)
                    {
                        cout << "\nEntity Found!\n";

                        cout << "ID: "
                             << result->id << endl;

                        cout << "Name: "
                             << result->name << endl;

                        cout << "Type: ";

                        if (result->isPerson)
                            cout << "Person\n";
                        else
                            cout << "Case\n";
                    }
                    else
                    {
                        cout << "\nEntity not found!\n";
                    }
                }

                break;


            // --------------------------------
            // 6. DISPLAY HASH TABLE
            // --------------------------------

            case 6:

                hashTable.display();

                break;


            // --------------------------------
            // 7. BFS
            // --------------------------------

            case 7:

                cout << "Enter starting Entity ID: ";
                getline(cin, id);

                BFS(graph, id);

                break;


            // --------------------------------
            // 8. DFS
            // --------------------------------

            case 8:

                cout << "Enter starting Entity ID: ";
                getline(cin, id);

                DFS(graph, id);

                break;


            // --------------------------------
            // 9. SHORTEST PATH
            // --------------------------------

            case 9:

                cout << "Enter Source ID: ";
                getline(cin, firstID);

                cout << "Enter Destination ID: ";
                getline(cin, secondID);

                findPath(graph, firstID, secondID);

                break;


            // --------------------------------
            // 10. COMMON CONNECTIONS
            // --------------------------------

            case 10:

                cout << "Enter First Entity ID: ";
                getline(cin, firstID);

                cout << "Enter Second Entity ID: ";
                getline(cin, secondID);

                findCommonConnections(
                    graph, firstID, secondID
                );

                break;


            // --------------------------------
            // 11. DEPTH ANALYSIS
            // --------------------------------

            case 11:

                {
                    int depth;

                    cout << "Enter Starting Entity ID: ";
                    getline(cin, id);

                    cout << "Enter Maximum Depth: ";
                    cin >> depth;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(),
                            '\n'
                        );

                        cout << "Invalid depth!\n";
                        break;
                    }

                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );

                    depthAnalysis(graph, id, depth);
                }

                break;


            // --------------------------------
            // 12. MERGE SORT RANKING
            // --------------------------------

            case 12:

                rankUsingMergeSort(graph);

                break;


            // --------------------------------
            // 13. PRIORITY QUEUE RANKING
            // --------------------------------

            case 13:

                rankUsingPriorityQueue(graph);

                break;


            // --------------------------------
            // 14. EXIT
            // --------------------------------

            case 14:

                cout << "\nThank you for using CASELINK!\n";
                cout << "Exiting application...\n";

                break;


            default:

                cout << "Invalid choice! Try again.\n";

        }

    } while (choice != 14);

    return 0;
}

