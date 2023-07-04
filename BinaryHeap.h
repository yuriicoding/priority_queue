#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include "AvlTree.h"
#include <vector>
#include <iostream>
using namespace std;

// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename id>
struct heapNode
{
    int priority;
    id assignment;
    AvlNode<id>* pointerToTask;
};

template <typename id>
class BinaryHeap
{
  public:

    explicit BinaryHeap<id>( int capacity = 100 )
      : array( capacity + 1 ), currentSize{ 0 }
    {
    }

    explicit BinaryHeap<id>( const vector<id> & items, const vector<int> & priorities )
      : array( items.size( ) + 10 ), currentSize{ static_cast<int>(items.size( )) }
    {
        for ( int i = 0; i < static_cast<int>(items.size()); i++)
        {
            heapNode<id> tmp;
            tmp.assignment = items [i];
            tmp.priority = priorities [i];
            tmp.pointerToTask = nullptr;
            array [i+1] = tmp;
        }
        buildHeap( );
    }


    bool isEmpty( ) const
      { return currentSize == 0; }


    const id & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return array[ 1 ].assignment;
    }
    

    void insert( const id & task_value, int priority_value, AvlNode<id>* task_pointer)
    {
        if( currentSize == static_cast<int>(array.size( )) - 1 )
            array.resize( array.size( ) * 2 );

        int hole = ++currentSize;
        heapNode<id> copy;
        copy.assignment = task_value;
        copy.priority = priority_value;
        copy.pointerToTask = task_pointer;

        array[ 0 ] = std::move( copy );
        for( ; copy.priority < array[hole/2].priority; hole /= 2 )
            array[ hole ] = std::move( array[ hole / 2 ] );
        array[ hole ] = std::move( array[ 0 ] );
    }
    

    id deleteMin( )
    {
        if( isEmpty( ) )
        {
            throw UnderflowException{ };
        }

        id temp = array[1].assignment;        

        array[ 1 ] = std::move( array [currentSize--] );
        percolateDown( 1 );
        return temp;
    }


    void makeEmpty( )
      { currentSize = 0; }

    id& checkTaskforIndex (int index)
    {
        return array[index].assignment;
    }


    void setTaskPointer ( AvlNode<id>& pointer_value, int arrayPosition)
    {
        array[arrayPosition].pointerToTask = &pointer_value;
    }


    void priorityChange (int array_position, int new_priority)
    {
        array[array_position].priority = new_priority;
        buildHeap();
    }


    int size() const
    {
        return currentSize;
    }


    void print()
    {
        cout << endl;
        for (int i = 0; i < currentSize; i++)
        {
            cout << i+1 << ") " << array[i+1].priority << " priority (" << array[i+1].assignment << " task) ";
        }
        cout << endl;
    }

  private:
    vector<heapNode<id>> array;
    int currentSize;


    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; --i )
            percolateDown( i );
    }


    void percolateDown( int hole )
    {
        int child;
        heapNode<id> tmp = std::move( array[ hole ] );

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ].priority < array[ child ].priority )
                ++child;
            if( array[ child ].priority < tmp.priority )
                array[ hole ] = std::move( array[ child ] );
            else
                break;
        }
        array[ hole ] = std::move( tmp );
    }
};

#endif
