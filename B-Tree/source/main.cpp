#include <iostream>
#include <algorithm>
#include <random>
#include <limits>
#include "bTree.hpp"

//clears input buffer declaration
void clearInput();

int main() 
{

    int userInput;
    bool inputLoop = false;


    do
    {
        std::cout << "Enter an N >= 400 to build B-tree: ";
        std::cin >> userInput;

        if (std::cin.fail())
        {
            std::cout << "|Something went wrong, try again" << " (CIN INPUT FAIL)| " << std::endl;
            clearInput();
        }
        else if (userInput < 400)
        {
            std::cout << "|Invalid input, try again" << " (INPUT OUT OF RANGE)| " << std::endl;
        }
        else
        {
            inputLoop = true;
        }
    } while (!inputLoop);

    //initialize a 5 way tree
    bTree newTree(3);

    //create instance of hardware/software based random number gnerator
    std::random_device rd;

    //creates instance of mersenne twister random number using a seed from rd()
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> number(0, 3 * userInput);

    //inserts random numbers into tree  
    int i = 0;
    for(i = 0; i < userInput; i++)
    {
        newTree.insert(number(gen));
    }

    //print in range
    newTree.printInRange(userInput, 2 * userInput);

    //ask user if they want to traverse tree
    std::cout << "\nWould you like to traverse(print it) the tree? (y/n): ";
    std::string userChoice;

    try
    {
        std::cin >> userChoice;
    }
    catch(std::exception& e)
    {
        std::cout << "Something went wrong, defaulting answer to n" << std::endl;
        userChoice = "n";
    }


    //converts user input to lowercase
    std::transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);

    //if user wants to traverse tree
    if(userChoice == "y")
    {
        newTree.traverse();
    }

    //std::cout << "searcing for key -1: (debugging purposes)" << std::endl;
    //ternirary operator to print out if key was found or not
    //std::cout << "Key " << (newTree.search(-1) != nullptr ? "found" : "not found") << std::endl;


}



void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}