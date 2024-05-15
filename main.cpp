/*
  Author: Vikram Vasudevan
  Date: 4/22/2024
  Description: This code inserts numbers into a red-black tree.
 */


#include <iostream>
#include <cstring>
#include "Node.h"
#include <vector>
#include <fstream>


using namespace std;

//function prototypes
void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(int direction, Node* current, int value);
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void fixTree(Node* &root, Node* current);

//main
int main(){
  
  //creating root and bool for while loop
    Node* root = NULL;
    bool stillRunning = true;
    //while loop where code runs
    while(stillRunning == true){
      //prompting users for choice
        cout << "What would you like to do? ADD, PRINT, or QUIT " << endl;
        char choice[50];
        cin.get(choice, 50);
        cin.get();
	//called if user wants to add numbers
        if(strcmp(choice, "ADD") == 0){
            char input[50];
            char method;
	    //determining adding method
            cout << "Would you like to enter by file (f) or by console (c)? " << endl;
            cin >> method;
            cin.get();
	    //adding by console
            if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
                cout << "Enter your string of numbers: " << endl;
                for(int i = 0; i < numNums; i++){
                    int tempInt;
                    cin >> tempInt;
                    cin.get();
                    Node* newNode = new Node();
                    newNode->setInformation(tempInt);
		    //calling add
                    add(root, root, newNode);
                }  
            
            }
	  //adding by file
            else if(method == 'f'){
                vector<int> nums;
                fstream first_stream;
                first_stream.open("nums.txt");
                int num;
                while(first_stream >> num){
                    nums.push_back(num);
                }
                vector <int> ::iterator iter = nums.begin();
                for(iter = nums.begin(); iter < nums.end(); iter++){
                    Node* newNode = new Node();
                    newNode->setInformation(*iter);
		    //calling add function
		    add(root, root, newNode);
                }


            }
        }
      //calling print
        else if(strcmp(choice, "PRINT") == 0){
            print(root, 0);
        }
      //exiting while loop
        else if(strcmp(choice, "QUIT") == 0){
            stillRunning = false;
        }

    }
    
}

//this function is called when case 3 occurs, and it fixes the tree.
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //changing node colors.
  parent->setColor('b');
  uncle->setColor('b');
  grandparent->setColor('r');
  //recursively calling fixTree again.
  fixTree(root, grandparent);
}


//this function is called when case 4 occurs, and it changes the tree before case 5 is called to finally fix the tree.
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //determining which direction the child is in and fixing the tree accordingly.
  if(newNode->getInformation() >= parent->getInformation()){
    Node* tempNode = newNode->getLeft();
    newNode->setParent(grandparent);
    grandparent->setLeft(newNode);
    newNode->setLeft(parent);
    parent->setRight(tempNode);
    parent->setParent(newNode);

  }
  else{
    Node* tempNode = newNode->getRight();
    newNode->setParent(grandparent);
    grandparent->setRight(newNode);
    newNode->setRight(parent);
    parent->setLeft(tempNode);
    parent->setParent(newNode);
  }
}

//this function is called when case 5 occurs, and it fixes the tree.
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //checking to see if the root needs to be altered.
  bool changeRoot = false;
  if(grandparent == root){
    changeRoot = true;
  }
  //checking to see which direction the node is in.
  if(parent->getInformation() > newNode->getInformation()){
    Node* tempNode = parent->getRight();
    //tree rotation
    if(grandparent->getParent() != NULL){
      parent->setParent(grandparent->getParent());
      if(grandparent->getParent()->getInformation() > grandparent->getInformation()){
	grandparent->getParent()->setLeft(parent);
      }
      else{
	grandparent->getParent()->setRight(parent);
      }
    }
    //resetting links
    parent->setRight(grandparent);
    grandparent->setParent(parent);
    grandparent->setLeft(tempNode);
    if(tempNode != NULL){
      tempNode->setParent(grandparent);
    }
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  else{
    //tree rotation
    Node* tempNode = parent->getLeft();
    if(grandparent->getParent() != NULL){
      parent->setParent(grandparent->getParent());
      if(grandparent->getParent()->getInformation() > grandparent->getInformation()){
        grandparent->getParent()->setLeft(parent);
      }
      else{
        grandparent->getParent()->setRight(parent);
      }
    }
    //resetting links
    parent->setLeft(grandparent);
    grandparent->setParent(parent);
    grandparent->setRight(tempNode);
    if(tempNode != NULL){
      tempNode->setParent(grandparent);
    }
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  //changing root, and setting it's parent to NULL.
  if(changeRoot == true){
    root = parent;
    root->setParent(NULL);
  }
}

//overarching function that calls each case to fix the tree.
void fixTree(Node* &root, Node* current){
  //case 1, after adding root, set its color to black.
  if(root != NULL){
    if(root->getColor() == 'r'){
      root->setColor('b');
    }
    //case 2, if parent is black just add new node.
    if(current->getParent() != NULL){
      if(current->getParent()->getColor() == 'b'){
	return;
      }
      //case three
      if(current->getParent()->getParent() != NULL){
	if(current->getParent()->getColor() == 'r' && (current->getParent()->getUncle() != NULL && current->getParent()->getUncle()->getColor() == 'r')){
	  caseThree(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	}
	//the color conditions for case 4 and case 5 are the same so they are all nested in the same color-checking if statement.
/*
  Author: Vikram Vasudevan
  Date: 4/22/2024
  Description: This code inserts numbers into a red-black tree.
 */


#include <iostream>
#include <cstring>
#include "Node.h"
#include <vector>
#include <fstream>


using namespace std;

//function prototypes
void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(int direction, Node* current, int value);
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void fixTree(Node* &root, Node* current);
void leftRotation(Node* &root, Node* current);
 void rightRotation(Node* &root, Node* current); 

//main
int main(){
  
  //creating root and bool for while loop
    Node* root = NULL;
    bool stillRunning = true;
    //while loop where code runs
    while(stillRunning == true){
      //prompting users for choice
        cout << "What would you like to do? ADD, PRINT, or QUIT " << endl;
        char choice[50];
        cin.get(choice, 50);
        cin.get();
	//called if user wants to add numbers
        if(strcmp(choice, "ADD") == 0){
	  char input[50];
	  char method;
	    //determining adding method
	  cout << "Would you like to enter by file (f) or by console (c)? " << endl;
          cin >> method;
	  cin.get();
	    //adding by console
	  if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
		cout << "Enter your string of numbers: " << endl;
                for(int i = 0; i < numNums; i++){
                    int tempInt;
                    cin >> tempInt;
                    cin.get();
                    Node* newNode = new Node();
                    newNode->setInformation(tempInt);
		    //calling add
                    add(root, root, newNode);
                }  
            
            }
	  //adding by file
            else if(method == 'f'){
                vector<int> nums;
                fstream first_stream;
                first_stream.open("nums.txt");
                int num;
                while(first_stream >> num){
                    nums.push_back(num);
                }
                vector <int> ::iterator iter = nums.begin();
                for(iter = nums.begin(); iter < nums.end(); iter++){
                    Node* newNode = new Node();
                    newNode->setInformation(*iter);
		    //calling add function
		    add(root, root, newNode);
                }


            }
        }
      //calling print
        else if(strcmp(choice, "PRINT") == 0){
            print(root, 0);
        }
      //exiting while loop
        else if(strcmp(choice, "QUIT") == 0){
            stillRunning = false;
        }

    }
    
}

//this function is called when case 3 occurs, and it fixes the tree.
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //changing node colors.
  parent->setColor('b');
  uncle->setColor('b');
  grandparent->setColor('r');
  //recursively calling fixTree again.
  fixTree(root, grandparent);
}


//this function is called when case 4 occurs, and it changes the tree before case 5 is called to finally fix the tree.
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //determining which direction the child is in and fixing the tree accordingly.
  if(newNode->getInformation() >= parent->getInformation()){
    Node* tempNode = newNode->getLeft();
    newNode->setParent(grandparent);
    grandparent->setLeft(newNode);
    newNode->setLeft(parent);
    parent->setRight(tempNode);
    parent->setParent(newNode);

  }
  else{
    Node* tempNode = newNode->getRight();
    newNode->setParent(grandparent);
    grandparent->setRight(newNode);
    newNode->setRight(parent);
    parent->setLeft(tempNode);
    parent->setParent(newNode);
  }
}

void leftRotation(Node* &root, Node* current){
  Node* tempGrandparent = current->getParent()->getParent();
  Node* tempParent = current->getParent();
  Node* tempLeft = current->getLeft();
  if(current->getParent() == root){
    root = current;
    current->setParent(NULL);
  }
  else{
    current->setParent(tempGrandparent);
  }
  
  current->setLeft(tempParent);
  tempParent->setParent(current);
  tempParent->setRight(tempLeft);
  tempLeft->setParent(tempParent);

}
     
void rightRotation(Node* &root, Node* current){
  Node* tempParent = current->getParent();
  Node* tempGrandparent = current->getParent()->getParent();
  Node* tempRight = current->getRight();

  if(current->getParent() == root){
    root = current;
    current->setParent(NULL);
  }
  else{
    current->setParent(tempGrandparent);
  }

  current->setRight(tempParent);
  tempParent->setParent(current);
  tempParent->setLeft(tempRight);
  tempRight->setParent(tempParent);
  
}
 
//this function is called when case 5 occurs, and it fixes the tree.
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode){
  //checking to see if the root needs to be altered.
  bool changeRoot = false;
  if(grandparent == root){
    changeRoot = true;
  }
  //checking to see which direction the node is in.
  if(parent->getInformation() > newNode->getInformation()){
    Node* tempNode = parent->getRight();
    //tree rotation
    if(grandparent->getParent() != NULL){
      parent->setParent(grandparent->getParent());
      if(grandparent->getParent()->getInformation() > grandparent->getInformation()){
	grandparent->getParent()->setLeft(parent);
      }
      else{
	grandparent->getParent()->setRight(parent);
      }
    }
    //resetting links
    parent->setRight(grandparent);
    grandparent->setParent(parent);
    grandparent->setLeft(tempNode);
    if(tempNode != NULL){
      tempNode->setParent(grandparent);
    }
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  else{
    //tree rotation
    Node* tempNode = parent->getLeft();
    if(grandparent->getParent() != NULL){
      parent->setParent(grandparent->getParent());
      if(grandparent->getParent()->getInformation() > grandparent->getInformation()){
        grandparent->getParent()->setLeft(parent);
      }
      else{
        grandparent->getParent()->setRight(parent);
      }
    }
    //resetting links
    parent->setLeft(grandparent);
    grandparent->setParent(parent);
    grandparent->setRight(tempNode);
    if(tempNode != NULL){
      tempNode->setParent(grandparent);
    }
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  //changing root, and setting it's parent to NULL.
  if(changeRoot == true){
    root = parent;
    root->setParent(NULL);
  }
}

//overarching function that calls each case to fix the tree.
void fixTree(Node* &root, Node* current){
  //case 1, after adding root, set its color to black.
  if(root != NULL){
    if(root->getColor() == 'r'){
      root->setColor('b');
    }
    //case 2, if parent is black just add new node.
    if(current->getParent() != NULL){
      if(current->getParent()->getColor() == 'b'){
	return;
      }
      //case three
      if(current->getParent()->getParent() != NULL){
	if(current->getParent()->getColor() == 'r' && (current->getParent()->getUncle() != NULL && current->getParent()->getUncle()->getColor() == 'r')){
	  caseThree(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	}
	//the color conditions for case 4 and case 5 are the same so they are all nested in the same color-checking if statement.
	if(current->getParent()->getColor() == 'r' && (current->getParent()->getUncle() == NULL || current->getParent()->getUncle()->getColor() == 'b')){
	  //case 4
	  if(current->getParent()->getInformation() < current->getParent()->getParent()->getInformation() && current->getParent()->getInformation() < current->getInformation()){
	    caseFour(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    current = current->getLeft();
	  }
	  else if(current->getParent()->getInformation() >= current->getParent()->getParent()->getInformation() && current->getParent()->getInformation() >= current->getInformation()){
	    caseFour(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    current = current->getRight();
	  }
	  //case 5 is called immediately after case 4.
	  if(current->getParent()->getInformation() < current->getParent()->getParent()->getInformation() && current->getInformation() < current->getParent()->getInformation()){
	    caseFive(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	    }
	  else if(current->getParent()->getInformation() >= current->getParent()->getParent()->getInformation() && current->getInformation() >= current->getParent()->getInformation()){
	    caseFive(root, current->getParent()->getParent(), current->getParent(), current->getParent()->getUncle(), current);
	  }
	  
	}
    }
  }
  
    }

}

//regular add function from binary search tree. Adds values to the tree
void add(Node* &root, Node* current, Node* newNode){
  //setting the root
    if(root == NULL){
        root = newNode;
    }
    //if the current node is greater than the new node, the new node goes to the left of the current node.
    else if(current->getInformation() >= newNode->getInformation()){
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
            newNode->setParent(current);
        }
        else{
            add(root, current->getLeft(), newNode);
	    return;
        }
    }
    //otherwise the new node goes to the right.
    else if(current->getInformation() < newNode->getInformation()){
        if(current->getRight() == NULL){
            current->setRight(newNode);
            newNode->setParent(current);
        }
        else{
            add(root, current->getRight(), newNode);
	    return;
        }
    }
    //fixing the tree after every new node is added.
    fixTree(root, newNode);

}
//printing out the tree
void print(Node* current, int count){
    if(current->getRight() != NULL){
        print(current->getRight(), count + 1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }
    cout << current->getInformation() << " " << current->getColor() << endl;
    if(current->getLeft() != NULL){
        print(current->getLeft(), count + 1);
    }

}
