/*
Author: Vikram Vasudevan
Date: 5/28/2024
Description: This code inserts numbers into a red-black tree. It also successfully deletes nodes from the red black tree and effectively rebalances the tree.
Citations: I collaborated with Ashvika Singhal throughout a lot of the creation process.
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
void remove(int direction, Node* &root, Node* current, int value);
//insert cases
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void fixTree(Node* &root, Node* current);
void leftRotation(Node* &root, Node* current);
void rightRotation(Node* &root, Node* current); 
void deleteFixTree(Node* &root, Node* current, bool deleted);
Node* findNode(Node* current, int value);
//delete cases
void dCaseTwo(Node* current, Node* &root);
void dCaseThree(Node* current, Node* &root);
void dCaseFour(Node* current, Node* &root);
void dCaseFive(Node* current, Node* &root);
void dCaseSix(Node* current, Node* &root);
void sixCases(Node* &root, Node* current, bool deleted);

//main
int main(){
  
  //creating root and bool for while loop
    Node* root = NULL;
    bool stillRunning = true;
    //while loop where code runs
    while(stillRunning == true){
      //prompting users for choice
        cout << "What would you like to do? ADD, PRINT, REMOVE, SEARCH, or QUIT " << endl;
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
            deleteFixTree(root, findNode(root, value), false);
        }
        else if(strcmp(choice, "SEARCH") == 0){
          cout << "What number are you looking for? " << endl;
          int num;
          cin >> num;
          cin.get();
          Node* test = findNode(root, num);
          if(test == NULL){
            cout << "THAT NODE DOESN'T EXIST" << endl;
          }
          else{
            cout << "THAT NODE EXISTS" << endl;
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
    leftRotation(root, newNode);
  }
  else{
    rightRotation(root, newNode);
}
}

//this function executes a left rotation, a process which is used in many of the cases for both addition and deletion.
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
}
//this function executes a right rotation, a process which is used in many of the cases for both addition and deletion.
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
    if(tempGrandparent->getInformation() > current->getInformation()){
      tempGrandparent->setLeft(current);
    }
    else{
      tempGrandparent->setRight(current);
    }
  }
  current->setRight(tempParent);
  tempParent->setParent(current);
  tempParent->setLeft(tempRight);
  if(tempRight != NULL){
    tempRight->setParent(tempParent);
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
    rightRotation(root, parent);
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  else{
    leftRotation(root, parent);
   
    //resetting colors
    parent->setColor('b');
    grandparent->setColor('r');
  }
  //changing root, and setting it's parent to NULL.

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
//this function finds a node in the red-black tree and returns it if it exists.
Node* findNode(Node* current, int value){
  if(current->getInformation() == value){
    return current;
  }
  else if(current->getInformation() > value){
    if(current->getLeft() != NULL){
      current = findNode(current->getLeft(), value);
    }
    else{
      return NULL;
    }
  }
  else if(current->getInformation() < value){
    if(current->getRight() != NULL){
      current = findNode(current->getRight(), value);
    }
    else{
      return NULL;
    }
  }
  return current;
}
//function that begins a preliminary fix on the tree if the tree matches the case 2 requirements.
void dCaseTwo(Node* current, Node* &root){
  if(current->getSibling()->getInformation() > current->getInformation()){
    current->getParent()->setColor('r');
    current->getSibling()->setColor('b');
    leftRotation(root, current->getSibling());
  }
  else{
    current->getParent()->setColor('r');
    current->getSibling()->setColor('b');
    rightRotation(root, current->getSibling());
  }
}
//function that begins a preliminary fix on the tree if the tree matches the case 3 requirements.
void dCaseThree(Node* current, Node* &root){
  current->getSibling()->setColor('r');
}
//function that completely fixes the tree if the tree matches the case 4 requirements.
void dCaseFour(Node* current, Node* &root){
  current->getParent()->setColor('b');
  current->getSibling()->setColor('r');
}
//function that begins a preliminary fix on the tree if the tree matches the case 5 requirements.
void dCaseFive(Node* current, Node* &root){
  if(current->getSibling()->getInformation() > current->getInformation()){
    current->getSibling()->getLeft()->setColor('b');
    current->getSibling()->setColor('r');
    rightRotation(root, current->getSibling()->getLeft());
  }
  else{
    current->getSibling()->getRight()->setColor('b');
    current->getSibling()->setColor('b');
    leftRotation(root, current->getSibling()->getRight());
  }
}

//function that completely fixes the tree if the tree matches the case 6 requirements.
void dCaseSix(Node* current, Node* &root){
  char tempColor = current->getParent()->getColor();
  if(current->getSibling()->getInformation() > current->getInformation()){
    current->getSibling()->setColor(tempColor);
    current->getSibling()->getRight()->setColor('b');
    current->getParent()->setColor('b');
    leftRotation(root, current->getSibling());
  }
  else{
    current->getSibling()->setColor(tempColor);
    current->getSibling()->getLeft()->setColor('b');
    current->getParent()->setColor('b');
    rightRotation(root, current->getSibling());
  }
}
//this function holds the six cases that exist if a double black node is created.
//although there are technically six cases, in reality there are only really five cases that are used.
void sixCases(Node* &root, Node* current, bool deleted){
  //each if statement corresponds to one of the five used cases.
  //case two
  if(current->getSibling()->getColor() == 'r'){
    //calling the actual case function
    dCaseTwo(current, root);
    //recursively calling the sixCases function again, since case 2 does not fully fix the tree.
    sixCases(root, current, false);
    //setting the boolean of deleted to true.
    deleted = true;
    return;
  }
  //case three
  if(current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getLeft() == NULL ||
    current->getSibling()->getLeft()->getColor() == 'b') && (current->getSibling()->getRight() == NULL || 
    current->getSibling()->getRight()->getColor() == 'b')){
    dCaseThree(current, root);
    Node* tempNode = current->getParent();
    //this is very important - the function should only delete a node if no other node has previously been deleted. This ensures that double
    //deletions don't occur.
    if(deleted == false){
      remove(0, root, root, current->getInformation());
      deleted = true;

    }
    //recursively call sixCases on the parent of current as long as the parent isn't the root.
    if(tempNode != root){
      sixCases(root, tempNode, true);
    }
    
    return;
  }
  //case 4
  if(current->getParent()->getColor() == 'r' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b') && 
    (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b')){
    dCaseFour(current, root);
    if(deleted == false){
      remove(0, root, root, current->getInformation());
    } 
    return;
  }
  //case 5: There are two case five if statements because combining the mirror image of case five into one if statement proved difficult.
  if(current->getSibling()->getColor() == 'b'){
    if(current->getSibling()->getInformation() > current->getInformation()){
      if(current->getSibling()->getLeft() != NULL && current->getSibling()->getLeft()->getColor() == 'r' && (current->getSibling()->getRight() == NULL || 
      current->getSibling()->getRight()->getColor() == 'b')){
        dCaseFive(current, root);
        dCaseSix(current, root);
        if(deleted == false){
          remove(0, root, root, current->getInformation());
          deleted = true;
        }
        return;
      }
    }
    else if(current->getSibling()->getInformation() < current->getInformation()){
      if(current->getSibling()->getRight() != NULL && current->getSibling()->getRight()->getColor() == 'r' && (current->getSibling()->getLeft() == NULL || 
      current->getSibling()->getLeft()->getColor() == 'b')){
        dCaseFive(current, root);
        dCaseSix(current, root);
        if(deleted == false){
          remove(0, root, root, current->getInformation());
          deleted = true;
        }
        return;
      }
    }
  }
  //case 6 - similarly to with case 6, there are two if statements for it to account for the mirror image.
  if(current->getSibling()->getInformation() > current->getInformation() && current->getSibling()->getColor() == 'b'){
    if(current->getSibling()->getRight() != NULL && current->getSibling()->getRight()->getColor() == 'r'){
      dCaseSix(current, root);
      if(deleted == false){
        remove(0, root, root, current->getInformation());
      }
      return;
    }
  }
  else if(current->getSibling()->getInformation() < current->getInformation() && current->getSibling()->getColor() == 'b'){
    if(current->getSibling()->getLeft() != NULL && current->getSibling()->getLeft()->getColor() == 'r'){
      dCaseSix(current, root);
      if(deleted == false){
        remove(0, root, root, current->getInformation());
      }
      return;
    }
  }
}

//this function is called the very first time the user states they'd like to delete a node. It determines whether the delete case is simple, or whether it
//requires the sixCases function.

//Ashvika helped provide the idea of having two separate functions, one with the six cases and one without. Additionally, she helped with the idea of structuring the function
//such that the deleteFixTree function calls itself twice, once when operating on the "deleted node" and once when operating on the successor.
void deleteFixTree(Node* &root, Node* current, bool deleted){
  //if the only node is the root, delete the root and return.
  if(current == root && current->getLeft() == NULL && current->getRight() == NULL){
    delete root;
    root = NULL;
    return;
  }
  //cases for if the deleted node only has one child or no children.
  if((current->getLeft() == NULL && current->getRight() != NULL) || (current->getRight() == NULL && current->getLeft() != NULL) || current->getLeft() == NULL && current->getRight() == NULL){
    //if the deleted node is black with a red child, delete the node and change the child to black.
    if(current->getSuccessor() != NULL && current->getSuccessor()->getColor() == 'r'){
      current->getSuccessor()->setColor('b');
      if(deleted == false){
        remove(0, root, root, current->getInformation());
        deleted = true;
      }
      return;
    }
    //if the deleted node is red, just delete the node.
    else if(current->getColor() == 'r' && (current->getSuccessor() == NULL || current->getSuccessor()->getColor() == 'b')){
      if(deleted == false){
        remove(0, root, root, current->getInformation());
        deleted = true;

      }
    }
    //if the deleted node is black with no children, call the six cases.
    else if(current->getColor() == 'b' && (current->getSuccessor() == NULL || current->getSuccessor()->getColor() == 'b')){
        sixCases(root, current, deleted);

        
    }
  }
  //if the node has no children and is red, delete the node.
  if(current->getLeft() == NULL && current->getRight() == NULL && current->getColor() == 'r'){

    remove(0, root, root, current->getInformation());    
  }
  //if the node has two children, swap the successor's value for the node's value then call deleteFixTree on the successor.
  else if(current->getLeft() != NULL && current->getRight() != NULL){
    current->setInformation(current->getSuccessor()->getInformation());
    deleteFixTree(root, current->getSuccessor(), false);
  }

}

//remove function, which actually deletes nodes.
void remove(int direction, Node* &root, Node* current, int value){
  bool recolor = false;
  //if current is the node we want to delete.
    if(current->getInformation() == value){
      //if current has no children, set the parent to NULL.
      if(current->getRight() == NULL && current->getLeft() == NULL){
          if(current->getParent() != NULL){
              if(direction == 0){
                if(current->getParent() != NULL){
                  current->getParent()->setLeft(NULL);
                }
                else{
                  root = NULL;
                }
              }
              else if(direction == 1){
                if(current->getParent() != NULL){
                  current->getParent()->setRight(NULL);
                }
                else{
                  root = NULL;
                }
              }
          }
          //delete
          delete current;
      }
      //if current has one child on the left/right, move it up to take the place of the deleted node.
      else if(current->getLeft() == NULL){
          if(direction == 0){
            if(current->getParent() != NULL){
              current->getParent()->setLeft(current->getRight());
            }
            else{
              root = current->getRight();
            }
          }
          else if(direction == 1){
            if(current->getParent() != NULL){
              current->getParent()->setRight(current->getRight());
            }
            else{
              root = current->getRight();
            }
          }
          current->getRight()->setParent(current->getParent());
          delete current;
      }
      else if(current->getRight() == NULL){
          if(direction == 0){
            if(current->getParent() != NULL){
              current->getParent()->setLeft(current->getLeft());
            }
            else{
              root = current->getLeft();
            }
          }
          else if(direction == 1){
            if(current->getParent() != NULL){
              current->getParent()->setRight(current->getLeft());
            }
            else{
              root = current->getLeft();
            }
          }
          current->getLeft()->setParent(current->getParent());
          delete current;
      }
      //if the node has two children, find the node's successor and replace it with the successor. Then delete the successor. 
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
              if(tempNode->getRight() != NULL){
                tempNode->getRight()->setParent(tempNode->getParent());
              }
              
            }
          else{
              tempNode->getParent()->setLeft(tempNode->getRight());
              if(tempNode->getRight() != NULL){
                tempNode->getRight()->setParent(tempNode->getParent());
              }
              
          }
          delete tempNode;
      }
    }
    //if this isn't the correct node, keep going in the tree until you find the correct node.
    else if(current->getInformation() > value){
        remove(0, root, current->getLeft(), value);
    }
    else if(current->getInformation() < value){
        remove(1, root, current->getRight(), value);
    }
}

//printing out the tree
void print(Node* current, int count){
  if(count == 0 && current == NULL){
    return;
  }
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
