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
        cout << "What would you like to do? ADD, PRINT, REMOVE, or QUIT " << endl;
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
	else if(strcmp(choice, "REMOVE") == 0){
            int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            remove(0, root, value);
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
  cout << "HI" << endl;
  if(newNode->getInformation() >= parent->getInformation()){
    /*
    Node* tempNode = newNode->getLeft();
    newNode->setParent(grandparent);
    grandparent->setLeft(newNode);
    newNode->setLeft(parent);
    parent->setRight(tempNode);
    parent->setParent(newNode);
    */
    leftRotation(root, newNode);

  }
  else{
    /*
    Node* tempNode = newNode->getRight();
    newNode->setParent(grandparent);
    grandparent->setRight(newNode);
    newNode->setRight(parent);
    parent->setLeft(tempNode);
    parent->setParent(newNode);
    */
    rightRotation(root, newNode);
  
}
}

void leftRotation(Node* &root, Node* current){
  Node* tempGrandparent = current->getParent()->getParent();
  Node* tempParent = current->getParent();
  Node* tempLeft = current->getLeft();
  cout << "Parent1: " << tempParent->getInformation() << endl;
  //cout << "Grandparent1: " << tempGrandparent->getInformation() << endl;
  if(current->getParent() == root){
    root = current;
    current->setParent(NULL);
  }
  else{
    current->setParent(tempGrandparent);
    cout << "In here" << endl;
    cout << current->getParent()->getInformation() << endl;
    if(tempGrandparent->getInformation() > current->getInformation()){
      tempGrandparent->setLeft(current);
    }
    else{
      tempGrandparent->setRight(current);
    }
  }
  
  current->setLeft(tempParent);
  tempParent->setParent(current);
  tempParent->setRight(tempLeft);
  if(tempLeft != NULL){
    tempLeft->setParent(tempParent);
  }
  cout << "Exited1" << endl;

}
     
void rightRotation(Node* &root, Node* current){
  Node* tempParent = current->getParent();
  Node* tempGrandparent = current->getParent()->getParent();
  Node* tempRight = current->getRight();

  cout << "Parent: " << tempParent->getInformation() << endl;
  //cout << "Grandparent: " << tempGrandparent->getInformation() << endl;
  if(current->getParent() == root){
    root = current;
    current->setParent(NULL);
  }
  else{
    current->setParent(tempGrandparent);
    if(tempGrandparent->getInformation() > current->getInformation()){
      tempGrandparent->setLeft(current);
    }
    else{
      tempGrandparent->setRight(current);
    }
  }
  cout << "1" << endl;
  current->setRight(tempParent);
  cout << "2" << endl;
  tempParent->setParent(current);
  cout << "3" << endl;
  tempParent->setLeft(tempRight);
  cout << "4" << endl;
  if(tempRight != NULL){
    tempRight->setParent(tempParent);
  }
  cout << "Exited" << endl;
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
    rightRotation(root, parent);

    /*
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
    */
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  else{
    leftRotation(root, parent);
    /*
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
    */
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  //changing root, and setting it's parent to NULL.
  /*
  if(changeRoot == true){
    root = parent;
    root->setParent(NULL);
  }
  */
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

void remove(int direction, Node* current, int value){
    if(current->getInformation() == value){
        if(current->getRight() == NULL && current->getLeft() == NULL){
            if(current->getParent() != NULL){
                if(direction == 0){
                    current->getParent()->setLeft(NULL);
                }
                else if(direction == 1){
                    current->getParent()->setRight(NULL);
                }
            }
            delete current;
        }
        else if(current->getLeft() == NULL){
            cout << "1" << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getRight());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getRight());
            }
            current->getRight()->setParent(current->getParent());
            delete current;
        }
        else if(current->getRight() == NULL){
            cout << current->getParent()->getInformation() << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getLeft());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getLeft());
            }
            current->getLeft()->setParent(current->getParent());
            delete current;
        }
        else{
            Node* tempNode = current->getRight();
            int counter = 0;
            while(tempNode->getLeft() != NULL){
                tempNode = tempNode->getLeft();
                counter++;
            }
            current->setInformation(tempNode->getInformation());
            if(counter == 0){
                current->setRight(tempNode->getRight());
                tempNode->getParent()->setRight(tempNode->getRight());
            }
            else{
                tempNode->getParent()->setLeft(tempNode->getLeft());
            }
            delete tempNode;
        }
    }
    else if(current->getInformation() > value){
        remove(0, current->getLeft(), value);
    }
    else if(current->getInformation() < value){
        remove(1, current->getRight(), value);
    }

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
