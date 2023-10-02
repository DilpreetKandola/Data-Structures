#include <iostream>
#include <string>
#include "queue.hpp"


int main() {


    Queue<int> intQueue;
    Queue<std::string> stringQueue;


    //add to int queue
    intQueue.emplace(1);
    intQueue.emplace(2);
    intQueue.emplace(3);
    intQueue.emplace(4);
    intQueue.emplace(5);

    //add to string queue
    stringQueue.emplace("This");
    stringQueue.emplace("is");
    stringQueue.emplace("a");
    stringQueue.emplace("queue");


    //print queue out before any other actions
    std::cout << "Queues before modifications: \n";

    intQueue.print();
    stringQueue.print();

    std::cout << "Queues after two nodes are dequeued: \n";

    intQueue.pop();
    intQueue.pop();

    stringQueue.pop();
    stringQueue.pop();

    intQueue.print();
    stringQueue.print();

    std::cout << "Method to check if queues are empty(return of 0 is false and return of 1 is true): \n";

    std::cout << "Int Queue: "<< intQueue.isEmpty() << " " << "String Queue: " << stringQueue.isEmpty() << "\n";

    std::cout << "Method to get queue size: \n";
    std::cout << "Int Queue: " << intQueue.getSize() << " " << "String Queue: " << stringQueue.getSize() << "\n";

    std::cout << "Method to get front or back of queue: \n";
    std::cout << "Int Queue front and back: " << intQueue.front() << " : " << intQueue.back() << "\n";


}
