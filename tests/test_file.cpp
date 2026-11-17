
#include "ranking.h"

int main() {

    RankedEntity entities[6] = {

        {"P101", "Rahul", 5, true},
        {"P102", "Aman", 9, true},
        {"C201", "Theft Case", 12, false},
        {"P103", "Riya", 3, true},
        {"C202", "Fraud Case", 7, false},
        {"P104", "Karan", 10, true}

    };

    int size = 6;

    // Testing Merge Sort
    cout << "===== MERGE SORT =====\n";

    mergeSort(entities, 0, size - 1);

    for (int i = 0; i < size; i++) {

        cout << entities[i].id << " - "
             << entities[i].name << " - "
             << entities[i].connectionCount
             << " connections\n";
    }

    // Testing Max Heap
    cout << "\n===== PRIORITY QUEUE =====\n";

    EntityPriorityQueue pq(10);

    for (int i = 0; i < size; i++) {
        pq.insert(entities[i]);
    }

    pq.displayTopEntities(5);

    return 0;
}
