
#pragma once

#include <stdlib.h>
#include <iostream>


//this template(generic function or class; allows use of different types of data)
//T represents a generic type
template <typename T> 
class Queue {

    private:
        struct Node{
            T data;
            Node* next; 
            Node(const T& item) : data(item), next(nullptr) {}

        };

        //holds front node and rear node
        Node* frontNode;
        Node* rearNode;

        //expresses size of an object in bytes
        //cannot represent negative values; usual use is for counting
        size_t size;

    public:
        Queue();
        ~Queue();

        bool isEmpty() const;
        size_t getSize() const;

        void emplace(const T&);
        T pop();

        T front() const;
        T back() const;

        void print() const;
        
        



};


//constructor for a queue
template <typename T>
Queue<T>::Queue(){
    
    frontNode = nullptr;
    rearNode = nullptr;
    size = 0;

}


//deconstructor for a queue
template <typename T>
Queue<T>::~Queue(){

    while(!isEmpty()){
        pop();
    }

}

//check if queue is empty; const means function does not modify queue
template <typename T>
bool Queue<T>::isEmpty() const {

    return this->size == 0;

}

//get size of queue
template <typename T>
size_t Queue<T>::getSize() const{

    return this->size;

}

//method to add to queue
template <typename T>
void Queue<T>::emplace(const T& item){

    Node* newNode = new Node(item);

    //if queue is empty new node is both front and rear.
    if(isEmpty()){
        frontNode = rearNode = newNode;
    }

    //if not empty make current rear node point to new rear node
    else {
        rearNode->next = newNode;
        rearNode = newNode;
    }

   size++; 
}

//method to pop front of queue
template <typename T>
T Queue<T>::pop() {

    //throw error if there is nothing to pop
    if(isEmpty()){
        throw std::runtime_error("Queue is empty or segmentation fault");
    }

    //pop node off queue FIFO first in first out
    T item = frontNode->data;
    Node* temporary = frontNode;
    frontNode = frontNode->next;

    delete temporary;
    size--;
    return item;


}

//method to get front of queue
template <typename T>
T Queue<T>::front() const {

    if(isEmpty()){
        throw std::runtime_error("Queue is empty or segmentation fault");
    }

    return frontNode->data;

}


//method to get back of the queue
template <typename T>
T Queue<T>::back() const {

    if(isEmpty()){
        throw std::runtime_error("Queue is empty or segmentation fault");
    }

    return rearNode->data;


}

template <typename T>
void Queue<T>::print() const {

    Node* currentNode = frontNode;

    std::cout << "{ ";

    while(currentNode != nullptr) {

        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;

    }

    std::cout << "}" << std::endl;

}


