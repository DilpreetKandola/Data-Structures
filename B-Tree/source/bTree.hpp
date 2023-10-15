#pragma once

#include <iostream>
#include <vector>

class Node 
{
    private:
    //key vector
    std::vector<int> keys;
    
    //degree of tree
    int degree;

    //vector of children
    std::vector<Node *> children;

    //number of keys in node
    int numKeys;

    //bool to check if node is leaf
    bool leaf;

    //constructor
    Node(int _degree, bool _leaf);

    //destructor
    ~Node();

    //delete key
    void remove(const int k);

    //remove non leaf
    void removeFromNonLeaf(const int index);

    //remove  is leaf
    void removeIsLeaf(const int index);

    //borrow from prev
    void borrowPrev(const int index);

    //borrow from next
    void borrowNext(const int index);

    //merge
    void merge(const int index);

    //fill node
    void fill(const int index);

    //get predecessor
    int getPred(const int index);

    //get successor
    int getSucc(const int index);

    //split child node
    void splitChild(const int i, Node *y);

    //non full insert
    void insertNonFull(const int k);

    //traverse
    void traverse(int& count);

    //search tree
    Node* search(const int k);

    //get in range
    std::vector<int> getInRange(const int min,const int max, bool print, int& count);

    //friend class
    friend class bTree;

};


class bTree 
{

    private:
    //root node
    Node *root;

    //degree of tree
    int degree;


    public:
    //constructor
    bTree(const int _degree);

    //destructor
    ~bTree();

    //insert
    void insert(const int k);

    //delete
    void remove(const int k);

    //traverse whole tree
    void traverse();

    //search
    Node* search(const int k);

    //print tree
    void printInRange(const int min, const int max);

    std::vector<int> getInRange(const int min, const int max);

};