#include "PQ.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    cout << "Vector Constructor Testing (initializing an integer PQ with two vectors)" << endl;
    vector<int> tasks = {45, 65, 23, 78, 90, 11, 64, 76, 27, 55};
    vector<int> prior = {3, 1, 7, 3, 2, 10, 5, 8, 6, 4};
    PQ<int> first (tasks, prior);
    first.print();
    cout << "Size of the PQ: " << first.size() << endl;
    cout << "Tasks in AVL tree store correct position of similar tasks in Binary Heap (array)" << endl;

    cout << endl << "Deleting two tasks with minimal priorities" << endl;
    cout << "First deleted: " << first.deleteMin() << endl;
    cout << "Second deleted: " << first.deleteMin() << endl;
    first.print();
    cout << "Size of the PQ: " << first.size() << endl;

    cout << endl << "Now minimal priority task is: " << first.findMin() << endl;

    cout << "Changing priority of 90 to 1" << endl;
    first.updatePriority(90, 1);
    cout << "Changing priority of 23 to 8" << endl;
    first.updatePriority(23, 8);
    first.print();

    cout << endl << "Inserting new task 24 with priority 12; 100 with priority 1; 33 with priority 5" << endl;
    first.insert(24, 12);
    first.insert(100, 1);
    first.insert(33, 5);
    first.print();
    cout << "Size of the PQ: " << first.size() << endl;

    cout << endl << "Is PQ empty: " << first.isEmpty() << endl;
    cout << "Making PQ empty" << endl;
    first.makeEmpty();
    cout << "Is PQ empty: " << first.isEmpty() << endl;


    cout << endl << "Constructing an empty character PQ and filling it by insertions:" << endl;
    PQ<char> second;
    int pr = 1;
    for (char i = 'a'; i <= 'o'; i++, pr++)
    {
        second.insert(i, pr);
    }
    second.print();
    
    cout << "Size of the PQ: " << second.size() << endl;
    cout << "Tasks in AVL tree store correct position of similar tasks in Binary Heap (array)" << endl;

    cout << endl << "Deleting three tasks with minimal priorities" << endl;
    cout << "First deleted: " << second.deleteMin() << endl;
    cout << "Second deleted: " << second.deleteMin() << endl;
    cout << "Third deleted: " << second.deleteMin() << endl;
    second.print();
    cout << "Size of the PQ: " << second.size() << endl;

    cout << endl << "Now minimal priority task is: " << second.findMin() << endl;

    cout << "Changing priority of 'n' to 25" << endl;
    second.updatePriority('n', 25);
    cout << "Changing priority of 'm' to 1" << endl;
    second.updatePriority('m', 1);
    second.print();

    cout << endl << "Is PQ empty: " << second.isEmpty() << endl;
    cout << "Making PQ empty" << endl;
    second.makeEmpty();
    cout << "Is PQ empty: " << second.isEmpty() << endl;

    return 0;
}
