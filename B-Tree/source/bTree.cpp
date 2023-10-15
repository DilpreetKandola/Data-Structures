#include "bTree.hpp"
#include <iostream>
#include <memory>

//constructor for node
Node::Node(int _degree, bool _leaf) : degree(_degree), numKeys(0), leaf(_leaf) {
    

    // Initialize keys to some default values, if needed
    for (int i = 0; i < 2 * degree - 1; ++i) {
        keys.push_back(0);
    }

    for (int i = 0; i < 2 * degree; ++i) {
        children.push_back(nullptr);
    }

}

//destructor for node
Node::~Node() 
{
    if(!leaf)
    {
        for(int i = 0; i < numKeys + 1; i++)
        {
            delete children[i];
            children[i] = nullptr;
        }
    }

}
//bTree destructor; double free error caused cause need to set root to nullptr after deleting
bTree::~bTree()
{
    
    if(root != nullptr)
    {
        delete root;
        root = nullptr;
    }
}

//bTree constructor
bTree::bTree(int _degree) : degree(_degree) {
    root = nullptr;
}

//---------------------------------------------------------------------------------------------

//insert function
void bTree::insert(const int key)
{

    // If tree is empty
    if (root == nullptr) 
    {
        root = new Node(degree, true);
        root->keys[0] = key;
        root->numKeys = 1;
    } 

    // If tree is not empty
    else 
    {
        if (root->numKeys == 2 * degree - 1) 
        {
            // Allocate memory for new root
            Node* newRoot = new Node(degree, false);

            // Make old root as child of new root
            newRoot->children[0] = root;

            // Split the old root and move 1 key to the new root
            newRoot->splitChild(0, root);

            int i = 0;
            if (newRoot->keys[0] < key) 
            {
                i++;
            }
            // Insert the key to the appropriate child
            newRoot->children[i]->insertNonFull(key);

            // Change root
            root = newRoot;

        } 
        
        else 
        {
            root->insertNonFull(key);
        }
    }

}


//insert non full function
void Node::insertNonFull(const int k)
{
    //get index of rightmost element
    int i = numKeys - 1;

    if(leaf)
    {

        //move all elements greater than k one space to the right; find index to insert k
        while(i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        //insert k
        keys[i + 1] = k;

        //increment number of keys
        numKeys += 1;

    }

    //if not leaf
    else
    {
        //find child to insert k
        while(i >= 0 && keys[i] > k)
        {
            i--;
        }

        //if child is full
        if(children[i + 1]->numKeys == 2 * degree - 1)
        {
            //split child
            splitChild(i + 1, children[i + 1]);

            //check which of the two children is now the correct one to insert k
            if(keys[i + 1] < k)
            {
                i++;
            }
        }

        //insert k
        children[i + 1]->insertNonFull(k);
    }

}

//split child function
void Node::splitChild(const int i, Node* y)
{ 
    //new node
    Node* z = new Node(y->degree, y->leaf);
    z->numKeys = degree - 1;

    //copy last degree - 1 keys of y to z
    for(int j = 0; j < degree - 1; j++)
    {
        z->keys[j] = y->keys[j + degree];
    }

    //copy last degree children of y to z
    if(y->leaf == false)
    {
        for(int j = 0; j < degree; j++)
        {
            z->children[j] = y->children[j + degree];
        }
    }

    //reduce number of keys in y
    y->numKeys = degree - 1;

    //move children of this node one space to the right
    for(int j = numKeys; j >= i + 1; j--)
    {
        children[j + 1] = children[j];
    }

    //link new child to this node
    children[i + 1] = z;    

    //move keys of this node one space to the right
    for(int j = numKeys - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
    }

    //copy middle key of y to this node
    keys[i] = y->keys[degree - 1];

    //increment number of keys in this node
    numKeys += 1;



}

//---------------------------------------------------------------------------------------------

//call delete key function
void bTree::remove(const int k)
{

    //if tree is empty
    if(root == nullptr)
    {
        return;
    }

    //call node remove function
    root->remove(k);

    //if root has 0 keys, make its first child the new root if it has a child, otherwise set root to nullptr
    if(root->numKeys == 0)
    {
        Node* temp = root;
        if(root->leaf)
        {
            root = nullptr;
        }
        else
        {
            root = root->children[0];
        }

        delete temp;
    }

    return;

}

//delete key function
void Node::remove(const int k)
{
    //find index of first key greater than or equal to k
    int foundIndex = 0;
    while(foundIndex < numKeys && keys[foundIndex] < k)
    {
        ++foundIndex;
    }

    //key is present in this node
    if(foundIndex < numKeys && keys[foundIndex] == k)
    {

        //if node is leaf
        if(leaf)
        {
            removeIsLeaf(foundIndex);
        }

        //if node is not leaf
        else
        {
            removeFromNonLeaf(foundIndex);
        }

    }
    //key not present in this node
    else 
    {
        //if node is leaf, not present in tree
        if(leaf)
        {
            //key not present in tree
            return;
        }

        //flag to check if key present in subtree
        bool flag = ((foundIndex == numKeys) ? true : false);

        //if child has less than degree keys, fill it
        if(children[foundIndex]->numKeys < degree)
        {
            fill(foundIndex);
        }

        //if last child needs to be merged, merge with previous child
        if(flag && foundIndex > numKeys)
        {
            children[foundIndex - 1]->remove(k);
        }
        //child does not need to be merged, recursively call delete on child
        else
        {
            children[foundIndex]->remove(k);
        }
    }

    return;
}

//merge function
void Node::merge(const int index)
{
    //get child[index] and child[index + 1]
    Node* child = children[index];
    Node* sibling = children[index + 1];

    //copy keys from sibling to child
    for(int i = 0; i < sibling->numKeys; ++i)
    {
        child->keys[i + degree] = sibling->keys[i];
    }

    //copy children from sibling to child
    if(!child->leaf)
    {
        for(int i = 0; i <= sibling->numKeys; ++i)
        {
            child->children[i + degree] = sibling->children[i];
        }
    }

    //fill gap left by moving keys and children
    for(int i = index + 1; i < numKeys; ++i)
    {
        keys[i - 1] = keys[i];
    }

    //fill gap left by moving children; index + 2 because child before is being deleted
    for(int i = index + 2; i <= numKeys; ++i)
    {
        children[i - 1] = children[i];
    }
    
    //update number of keys
    child->numKeys += sibling->numKeys + 1;

    //update number of keys in this node
    numKeys -= 1;

    return;

}

//remove if node is leaf
void Node::removeIsLeaf(const int index)
{
    //move keys after index one space to the back
    for(int i = index + 1; i < numKeys; i++)
    {
        keys[i - 1] = keys[i];
    }

    //decrement number of keys
    numKeys--;

    return;

}

void Node::removeFromNonLeaf(const int index)
{
    //variable to store key to be deleted
    int k = keys[index];

    //if child that precedes k has at least degree key; recursively call delete on it
    if(children[index]->numKeys >= degree)
    {
        //get predecessor of k
        int pred = getPred(index);

        //replace k with pred
        keys[index] = pred;

        //delete pred from child
        children[index]->remove(pred);
    }

    //if child that succeeds k has atleast degree keys; find successor of k,
    //replace k with successor, recursively delete successor 
    else if(children[index + 1]->numKeys == degree)
    {
        //get successor of k 
        int succ = getSucc(index);

        //replace k with succ
        keys[index] = succ;

        //delete succ
        children[index + 1]->remove(succ);
    }

    //both child before and after k have less than degree keys
    //merge k and all of child[index + 1] into child[index]
    else 
    {
        //merge child[index + 1] into child[index]
        merge(index);

        //delete k from child[index]
        children[index]->remove(k);
    }

    return;

}

//get predecessor method
int Node::getPred(const int index)
{

    //move right till leaf
    Node* current = children[index];
    while(!current->leaf)
    {
        current = current->children[current->numKeys];
    }

    //return last key of leaf
    return current->keys[current->numKeys - 1];

}

//get successor method
int Node::getSucc(const int index)
{
    ////move left till leaf
    Node* current = children[index + 1];

    while(!current->leaf)
    {   
        //get leftmost child
        current = current->children[0];
    }

    //return first key of leftmost leaf
    return current->keys[0];

}

//fill function
void Node::fill(const int index)
{
    //if previous child has more than degree - 1 keys, borrow from it
    if(index != 0 && children[index - 1]->numKeys >= degree)
    {
        borrowPrev(index);
    }

    //if next child has more than degree - 1 keys, borrow from it
    else if(index != numKeys && children[index + 1]->numKeys >= degree)
    {
        borrowNext(index);
    }

    //if both previous and next child have less than degree keys, merge with next child
    else
    {
        if(index != numKeys)
        {
            merge(index);
        }
        else
        {
            merge(index - 1);
        }
    }

    return;

}

//borrow from previous child
void Node::borrowPrev(const int index)
{
    //get child[index] and child[index - 1]
    Node* child = children[index];
    Node* sibling = children[index - 1];

    //move all keys in child one space ahead
    for(int i = child->numKeys - 1; i >= 0; --i)
    {
        child->keys[i + 1] = child->keys[i];
    }

    //if child is not leaf, move children one space ahead
    if(!child->leaf)
    {
        for(int i = child->numKeys; i >= 0; --i)
        {
            child->children[i + 1] = child->children[i];
        }
    }

    //set child's first key to parent's key[index - 1]
    child->keys[0] = keys[index - 1];

    //move sibling's last child as child's first child
    if(!child->leaf)
    {
        child->children[0] = sibling->children[sibling->numKeys];
    }

    //move sibling's last key to parent's key[index - 1]
    keys[index - 1] = sibling->keys[sibling->numKeys - 1];

    //increment number of keys in child
    child->numKeys += 1;

    //decrement number of keys in sibling
    sibling->numKeys -= 1;

    return;

}

//borrow from next child
void Node::borrowNext(const int index)
{
    //get child[index] and child[index + 1]
    Node* child = children[index];
    Node* sibling = children[index + 1];

    //set child's last key to parent's key[index]
    child->keys[child->numKeys] = keys[index];

    //if child is not leaf, move sibling's first child as child's last child
    if(!child->leaf)
    {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    //set parent's key[index] to sibling's first key
    keys[index] = sibling->keys[0];

    //move all keys in sibling one space ahead
    for(int i = 1; i < sibling->numKeys; ++i)
    {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    //if sibling is not leaf, move all children one space ahead
    if(!sibling->leaf)
    {
        for(int i = 1; i <= sibling->numKeys; ++i)
        {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    //increment number of keys in child
    child->numKeys += 1;

    //decrement number of keys in sibling
    sibling->numKeys -= 1;

    return;

}

std::vector<int> bTree::getInRange(int min, int max)
{

    int count = 0;

    //if tree is empty
    if(root == nullptr)
    {
        return std::vector<int>();
    }

    //call node get in range function
    return root->getInRange(min, max, false, count);

}


std::vector<int> Node::getInRange(int min, int max, bool print, int& count) {
    // Vector to store found keys
    std::vector<int> foundKeys;

    // Traverse all keys and subtrees
    for (int i = 0; i < numKeys; i++) 
    {
        // If node is not leaf, traverse the subtree rooted with child children[i].
        if (!leaf) 
        {
            
            std::vector<int> childKeys = children[i]->getInRange(min, max, print, count);
            foundKeys.insert(foundKeys.end(), childKeys.begin(), childKeys.end());

        }

        // If key is in range, add it to vector
        if (keys[i] >= min && keys[i] <= max) 
        {
            foundKeys.push_back(keys[i]);

            if (print) 
            {
                std::cout << " " << keys[i];
                count++;
            }

        }
    }

    // Traverse the subtree rooted with the last child
    if (!leaf) 
    {
        
        std::vector<int> childKeys = children[numKeys]->getInRange(min, max, print, count);
        foundKeys.insert(foundKeys.end(), childKeys.begin(), childKeys.end());

    }

    //print number of elements in range

    return (print ? std::vector<int>() : foundKeys);

}

//------------------------------------------------------------------------------------------------------------------------------------

void bTree::printInRange(const int min, const int max) 
{

    int count = 0;
    //root is not null
    if(root != nullptr)
    {
        //call node print in range function
        root->getInRange(min, max, true, count);
    }

    std::cout << "\n" << count << " elements in range [" << min << ", " << max << "]" << std::endl;

}

//traverse method to print whole tree
void bTree::traverse() 
{
    int count = 0;

    // If tree not empty
    if (root != nullptr) 
    {
        // Call the traverse function on the root
        root->traverse(count);
    }

    // Print the number of elements in the tree
    std::cout << "\n" << count << " elements in tree total." << std::endl;
  
}

//node traverse method
void Node::traverse(int& count) 
{ 
    int i; 

    // Traverse through all keys in the current node
    for (i = 0; i < numKeys; i++) 
    { 
        // If this is not leaf, then before printing key[i], traverse the subtree rooted with child children[i].
        if (leaf == false) 
        {
            children[i]->traverse(count); 
        }

        // Print the key
        std::cout << " " << keys[i]; 
        count++;
    } 

    // Print the subtree rooted with last child
    if (leaf == false) 
    {
        children[i]->traverse(count); 
    }
}


//search function; node return is not necessary, until we implement delete or replace
Node* bTree::search(const int k)
{
    //if tree is empty
    if(root == nullptr)
    {
        return nullptr;
    }
    //if tree is not empty
    else
    {
        return root->search(k);
    }
}

//search function; node return is not necessary, until we implement delete or replace
Node* Node::search(const int k)
{
    //find first key greater than or equal to k
    int i = 0;
    while(i < numKeys && k > keys[i])
    {
        i++;
    }

    //if key is found
    if(keys[i] == k)
    {
        return this;
    }

    //if key is not found and node is leaf
    if(leaf == true)
    {
        return nullptr;
    }

    //if key is not found and node is not leaf
    return children[i]->search(k);
}

