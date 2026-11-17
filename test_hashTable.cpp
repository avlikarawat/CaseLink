#include "hashTable.h"

int main()
{
    // Create a hash table with 5 buckets
    HashTable ht(5);

    cout << "\n===== INSERTING ENTITIES =====\n";

    ht.insert("P101", "Rahul", true);
    ht.insert("P102", "Priya", true);
    ht.insert("P103", "Aman", true);

    ht.insert("C201", "Cyber Fraud", false);
    ht.insert("C202", "Financial Fraud", false);

    cout << "\n===== DISPLAYING HASH TABLE =====\n";

    ht.display();

    cout << "\n===== SEARCHING ENTITIES =====\n";

    HashNode* result = ht.search("P102");

    if (result != nullptr)
    {
        cout << "Entity found!\n";
        cout << "ID: " << result->id << endl;
        cout << "Name: " << result->name << endl;
    }
    else
    {
        cout << "Entity not found!\n";
    }

    cout << "\n===== SEARCHING INVALID ID =====\n";

    result = ht.search("P999");

    if (result == nullptr)
    {
        cout << "Entity not found!\n";
    }

        cout << "\n===== TESTING DUPLICATE ID =====\n";

    ht.insert("P101", "Another Rahul", true);

    cout << "\n===== TESTING COLLISION HANDLING =====\n";

    HashTable collisionTest(1);

    collisionTest.insert("P201", "Karan", true);
    collisionTest.insert("P202", "Meera", true);

    collisionTest.display();

    return 0;
}