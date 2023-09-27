#include <iostream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {

    //stores value
    int value; 

    //determines if on left or right of tree
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : value(x), left(NULL), right(NULL) {} ;

};



TreeNode* makeBST(int[], int, int);
TreeNode* findElement(TreeNode*, int&);
void printBST(TreeNode*);



int main() {

    //bool for input loop and var to store user entered x
    bool inputLoop = false;

    //userinput is K
    int userInput = 0;
    

    //start of an array index(0) and in this case a set known value of the end of the array(14)
    int start = 0, end = 14;

    int numbers[] = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};

    while(!inputLoop){

        std::cout << "{ ";
        //for loop to print array
        for(int i = 0; i < 15; i++){ 

            std::cout << numbers[i] << " ";

        }

        std::cout << "}" << "\n";

        std::cout << "Enter K in order to find K-th smallest Element in array above: ";
        std::cin >> userInput;


        //checks if cin fail flag is set, then clears and ignores inputted characters
        if(std::cin.fail()){

            std::cout << "|Something went wrong, try again" << " (CIN INPUT FAIL)| " << std::endl;                                              

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        //else if to make sure input fits criteria
        else if(userInput <= 15){
            inputLoop = true;
        }
        
    }
    //function that makes the BST and returns root
    TreeNode* root = makeBST(numbers, start, end);

    //function that takes the root and finds the K-th element user wants
    TreeNode* foundElement = findElement(root, userInput);

    //if statement to catch it the node returns null for some reason
    if(foundElement == NULL){

        std::cout << "Looks like something went wrong" << std::endl;

    }
    //prints out the k-th element
    else {

        std::cout << "(" << userInput << ")-th smallest element is " << foundElement->value << std::endl;

    }

    printBST(root);


    return 0;

}


//function converts array to a Balanced BST using recursion
TreeNode* makeBST(int numbers[], int startOfArray, int endOfArray){

    //if start is greater than end then there are no elements in current subarray that can/should be used to construct subtree
    if(startOfArray > endOfArray){
        return NULL;
    }

    //calculates the index of middle element in sub array
    int mid = (startOfArray + endOfArray) / 2 ;

    //pointer to newly created node with specificed value (MAKE SURE TO FREE MEMORY)
    TreeNode* root = new TreeNode(numbers[mid]);

    //recursively constructs left subtree
    root->left = makeBST(numbers, startOfArray, mid - 1);

    //recuresively contructs right subtree
    root->right = makeBST(numbers, mid + 1, endOfArray);

    return root;

}

//global var to keep track of checked nodes
int count = 0;

//function to find k-th smallest element
TreeNode* findElement(TreeNode* root, int& userInput) {

    //base case if root is NULL
    if(root == NULL){
        return NULL;
    }

    //recursive call on left subtree if it is not null then we found the k-th element
    TreeNode* left = findElement(root->left, userInput);

    if(left != NULL){
        return left;
    }


    //count is incremented, if count becomes user input then thats the k-th smallest element
    count++;
    if(count == userInput){
        return root;
    }

    //otherwise find k-th element in right subtree and return it
    return findElement(root->right, userInput);


}



void printBST(TreeNode* root){
    if (root == nullptr) {
        return;
    }

    // Recursively print left subtree
    printBST(root->left);

    // Print the current node
    std::cout << root->value << " \n";

    // Recursively print right subtree
    printBST(root->right);
}