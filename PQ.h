#ifndef PQ_H
#define PQ_H

#include "AvlTree.h"
#include "BinaryHeap.h"
#include <iostream>
using namespace std;

// PQ class
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, priorities ) --> constructs a new queue with a given set of task IDs and priorities 
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p 
// ID findMin( )  --> Return a task ID with smallest priority, without removing it 
// ID deleteMin( )   --> Remove and return a task ID with smallest priority 
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue 
// void makeEmpty( )  --> Remove all task IDs (and their priorities)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
// ID is the type of task IDs to be used; the type must be Comparable (i.e., have < defined), so IDs can be AVL Tree keys.
class PQ
{

  public:

    // Constructor
    // Initializes a new empty PQ
    PQ() : assignments(), precedences()
    { }

    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and priorities  
    //      priority[i] is the priority for ID task[i] 
    PQ( const std::vector<ID> & tasks, const std::vector<int> & priorities ) : precedences{tasks, priorities}
    {
      
      for (int i = 0; i < static_cast<int>(tasks.size()); i++)
      {
        ID tmp = precedences.checkTaskforIndex(i+1);
        assignments.insert(tmp, i+1);
      }

      for (long unsigned int i = 0; i < tasks.size(); i++)
      {
        ID task_tmp = precedences.checkTaskforIndex(i+1);
        AvlNode<ID>* taskTmpPointer = assignments.findTask(task_tmp);
        precedences.setTaskPointer(*taskTmpPointer, i);
      }
    }
						     
    // Emptiness check 
    bool isEmpty( ) const
    { 
      return precedences.isEmpty();
    }

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin() 
    { 
      ID task_temp = precedences.checkTaskforIndex(1);
      assignments.remove(task_temp);
      const ID& deletedMin = precedences.deleteMin();

      for (int i = 0; i < size(); i++)
      {
        ID task = precedences.checkTaskforIndex(i+1);
        assignments.setBinaryHeapPosition(task, i+1);
      }
      return deletedMin;
    }

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() const
    { 
      return precedences.findMin();
    }

    // Insert ID x with priority p.
    void insert( const ID & x, int p )
    { 
      assignments.insert (x, 0);
      AvlNode<ID>* pointer_to_x = assignments.findTask(x);
      precedences.insert (x, p, pointer_to_x);

      for (int i = 0; i < size(); i++)
      {
        ID task = precedences.checkTaskforIndex(i+1);
        assignments.setBinaryHeapPosition(task, i+1);
      }
    }

    // Update the priority of ID x to p
    //    Inserts x with p if s not already in the queue
    void updatePriority( const ID & x, int p ) 
    { 
      if (assignments.contains(x) == true)
      {
        int array_position = assignments.getBinaryHeapPosition(x);
        precedences.priorityChange(array_position, p);
        for (int i = 0; i < size(); i++)
        {
          ID task = precedences.checkTaskforIndex(i+1);
          assignments.setBinaryHeapPosition(task, i+1);
        }
      }
      else
      {
        insert(x, p);
      }
    }

    // Return the number of task IDs in the queue
    int size() const
    { 
      return precedences.size();
    } 

    // Delete all IDs from the PQ
    void makeEmpty( )
    { 
      assignments.makeEmpty();
      precedences.makeEmpty();
    }

    void print()
    {
      assignments.printTree();
      precedences.print();
    }

  private:
    AvlTree<ID> assignments;
    BinaryHeap<ID> precedences;


};
#endif
