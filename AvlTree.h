#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename id>
struct AvlNode
{
    id element;
    AvlNode   *left;
    AvlNode   *right;
    int binaryHeapPosition;
    int       height;

    AvlNode( const id & ele, AvlNode *lt, AvlNode *rt, int BHP, int h = 0)
      : element{ ele }, left{ lt }, right{ rt }, binaryHeapPosition {BHP}, height{ h } { }
};

template <typename id>
class AvlTree
{
  public:

    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }


    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    

    const id & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }


    const id & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }


    AvlNode<id>* findTask( const id & x ) const
    {
        return findTask( x, root );
    }


    bool contains( const id & x ) const
    {
        return contains( x, root );
    }


    bool isEmpty( ) const
    {
        return root == nullptr;
    }


    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }


    void makeEmpty( )
    {
        makeEmpty( root );
    }


    void insert( const id & x, int array_position )
    {
        insert( x, array_position, root );
    }
     

    void remove( const id & x )
    {
        remove( x, root );
    }


    void setBinaryHeapPosition (const id& x, int array_position)
    {
        AvlNode<id>* tmp = this->findTask(x);
        tmp->binaryHeapPosition = array_position;
    }


    int getBinaryHeapPosition (const id& x)
    {
        AvlNode<id>* tmp = this->findTask(x);
        return tmp->binaryHeapPosition;
    }


  private:

    AvlNode<id> *root;


    void insert( const id & x, int array_position, AvlNode<id> * & t )
    {
        if( t == nullptr )
            t = new AvlNode<id>{ x, nullptr, nullptr, array_position };
        else if( x < t->element )
            insert( x, array_position, t->left );
        else if( t->element < x )
            insert( x, array_position, t->right );
        
        balance( t );
    }
     

    void remove( const id & x, AvlNode<id> * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode<id> *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }

    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode<id> * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){
            if( height( t->left->left ) >= height( t->left->right ) ){
                rotateWithLeftChild( t );
            }
            else{
                doubleWithLeftChild( t );
            }
        }
        else{
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ){
            if( height( t->right->right ) >= height( t->right->left ) ){
                rotateWithRightChild( t );
            }
            else{
                doubleWithRightChild( t );
            }
        }
        }
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    

    AvlNode<id> * findMin( AvlNode<id> *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }


    AvlNode<id> * findMax( AvlNode<id> *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    AvlNode<id>* findTask( const id & x, AvlNode<id> *t ) const
    {
        if( x < t->element )
            return findTask( x, t->left );
        else if( t->element < x )
            return findTask( x, t->right );
        else
            return t;
    }


    bool contains( const id & x, AvlNode<id> *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;
    }


    void makeEmpty( AvlNode<id> * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }


    void printTree( AvlNode<id> *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << " task (" << t->binaryHeapPosition << " position in array) " << endl;
            printTree( t->right );
        }

    }


    AvlNode<id> * clone( AvlNode<id> *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode<id>{ t->element, clone( t->left ), clone( t->right ), t->height };
    }


    // Avl manipulations

    int height( AvlNode<id> *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }


    void rotateWithLeftChild( AvlNode<id> * & k2 )
    {
        AvlNode<id> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }


    void rotateWithRightChild( AvlNode<id> * & k1 )
    {
        AvlNode<id> *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    void doubleWithLeftChild( AvlNode<id> * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }


    void doubleWithRightChild( AvlNode<id> * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
