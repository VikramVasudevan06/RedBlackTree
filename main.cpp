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
void remove(int direction, Node* &root, Node* current, int value);
void caseThree(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFour(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void caseFive(Node* &root, Node* grandparent, Node* parent, Node* uncle, Node* newNode);
void fixTree(Node* &root, Node* current);
void leftRotation(Node* &root, Node* current);
void rightRotation(Node* &root, Node* current); 
void deleteFixTree(Node* &root, Node* current, bool deleted);
Node* findNode(Node* current, int value);
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
            deleteFixTree(root, findNode(root, value), false);
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
    leftRotation(root, newNode);
  }
  else{
    rightRotation(root, newNode);
}
}

void leftRotation(Node* &root, Node* current){
  Node* tempGrandparent = current->getParent()->getParent();
  Node* tempParent = current->getParent();
  Node* tempLeft = current->getLeft();
  cout << "Parent1: " << tempParent->getInformation() << endl;
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
Node* findNode(Node* current, int value){
  if(current->getInformation() == value){
    return current;
  }
  else if(current->getInformation() > value){
    if(current->getLeft() != NULL){
      current = findNode(current->getLeft(), value);
    }
  }
  else if(current->getInformation() < value){
    if(current->getRight() != NULL){
      current = findNode(current->getRight(), value);
    }
  }
  return current;
}
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

void dCaseThree(Node* current, Node* &root){
  current->getSibling()->setColor('r');
  cout << "Made it out" << endl;
}

void dCaseFour(Node* current, Node* &root){
  current->getParent()->setColor('b');
  current->getSibling()->setColor('r');
  cout << "Made it out" << endl;
}

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
void sixCases(Node* &root, Node* current, bool deleted){
  cout << "entered this" << endl;
  cout << current->getInformation()<< endl;
      //six cases
      cout << "STILL HERE" << endl;
        if(current->getSibling()->getColor() == 'r'){
          cout << "Case 2" << endl;
          dCaseTwo(current, root);
          print(root, 0);
          sixCases(root, current, false);
          deleted = true;
          return;
        }
        cout << "STILL HERE 2" << endl;
        if(current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getLeft() == NULL ||
          current->getSibling()->getLeft()->getColor() == 'b') && (current->getSibling()->getRight() == NULL || 
          current->getSibling()->getRight()->getColor() == 'b')){
          cout << "Case 3" << endl;
          dCaseThree(current, root);
          Node* tempNode = current->getParent();
          if(deleted == false){
            cout << "ENTERED" << endl;
            cout << "Current: " << current->getInformation() << endl;
            remove(0, root, root, current->getInformation());

            deleted = true;

          }
          cout << "Is this even a thing" << endl;
          if(tempNode != root){
            sixCases(root, tempNode, true);
          }
          
          return;
        }
        cout << "STILL HERE 3" << endl;
        if(current->getParent()->getColor() == 'r' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b') && 
          (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b')){
          //case 4
          cout << "Case 4" << endl;
          dCaseFour(current, root);
          if(deleted == false){
            cout << "IN HERE" << endl;
            remove(0, root, root, current->getInformation());
          } 
          return;
        }
        cout << "Still HERE 4" << endl;
        if(current->getSibling()->getColor() == 'b'){
          cout << "STILL HERE 5" << endl;
          if(current->getSibling()->getInformation() > current->getInformation()){
            cout << "1" << endl;
            if(current->getSibling()->getLeft() != NULL && current->getSibling()->getLeft()->getColor() == 'r' && (current->getSibling()->getRight() == NULL || 
            current->getSibling()->getRight()->getColor() == 'b')){
              cout << "Case 5" << endl;
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
            cout << "2" << endl;
            if(current->getSibling()->getRight() != NULL && current->getSibling()->getRight()->getColor() == 'r' && (current->getSibling()->getLeft() == NULL || 
            current->getSibling()->getLeft()->getColor() == 'b')){
              cout << "Case 5" << endl;
              dCaseFive(current, root);
              dCaseSix(current, root);
              if(deleted == false){
                remove(0, root, root, current->getInformation());
                deleted = true;
              }
              return;
            }
          }
          cout << "STILL HERE 6" << endl;
        }
        cout << "STILL HERE 7" << endl;
        cout << current->getSibling()->getInformation() << endl;
        if(current->getSibling()->getRight() != NULL && current->getSibling()->getRight()->getColor() == 'r'){
          cout << current->getSibling()->getRight()->getInformation() << endl;
        }
        else{
          cout << "HI" << endl;
        }
        if(current->getSibling()->getInformation() > current->getInformation() && current->getSibling()->getColor() == 'b'){
          cout << "made it here too" << endl;
          if(current->getSibling()->getRight() != NULL && current->getSibling()->getRight()->getColor() == 'r'){
            cout << "Case 6" << endl;
            dCaseSix(current, root);
            if(deleted == false){
              cout << "inside v2.0" << endl;
              remove(0, root, root, current->getInformation());
            }
            return;
          }
        }
        else if(current->getSibling()->getInformation() < current->getInformation() && current->getSibling()->getColor() == 'b'){
          cout << "In here" << endl;
          if(current->getSibling()->getLeft() != NULL && current->getSibling()->getLeft()->getColor() == 'r'){
            cout << "Case 6" << endl;
            dCaseSix(current, root);
            if(deleted == false){
              cout << "inside this one" << endl;
              cout << current->getInformation() << endl;
              remove(0, root, root, current->getInformation());
            }
            return;
          }
        }
}

void deleteFixTree(Node* &root, Node* current, bool deleted){
  print(root, 0);
  cout << "WOOOOHOOOO" << endl;
  cout << "CURRENT INFORMATION: " << current->getInformation() << endl;
  if(current == root && current->getLeft() == NULL && current->getRight() == NULL){
    delete root;
    root = NULL;
    return;
  }
  if((current->getLeft() == NULL && current->getRight() != NULL) || (current->getRight() == NULL && current->getLeft() != NULL) || current->getLeft() == NULL && current->getRight() == NULL){
    cout << "HERE" << endl;
    if(current->getSuccessor() != NULL && current->getSuccessor()->getColor() == 'r'){
      cout << "IN HERE" << endl;
      current->getSuccessor()->setColor('b');
      cout << "Made it past" << endl;
      if(deleted == false){
        remove(0, root, root, current->getInformation());
        deleted = true;

      }
      return;
    }
    else if(current->getColor() == 'r' && (current->getSuccessor() == NULL || current->getSuccessor()->getColor() == 'b')){
      cout << "IN HERE 2" << endl;

      if(deleted == false){
        remove(0, root, root, current->getInformation());
        deleted = true;

      }
    }
    else if(current->getColor() == 'b' && (current->getSuccessor() == NULL || current->getSuccessor()->getColor() == 'b')){
        cout << current->getInformation() << endl;
        cout << current->getParent()->getInformation() << endl;
        cout << current->getSibling()->getInformation() << endl;
        sixCases(root, current, deleted);

        
    }
  }
  if(current->getLeft() == NULL && current->getRight() == NULL && current->getColor() == 'r'){

    remove(0, root, root, current->getInformation());
    cout << "RED + DELETED" << endl;
    
  }
  else if(current->getLeft() != NULL && current->getRight() != NULL){
    cout << "Back to the top" << endl;
    current->setInformation(current->getSuccessor()->getInformation());
    deleteFixTree(root, current->getSuccessor(), false);
  }

}


void remove(int direction, Node* &root, Node* current, int value){
  bool recolor = false;
    if(current->getInformation() == value){
      cout << "0" << endl;
      if(current->getRight() == NULL && current->getLeft() == NULL){
        cout << "-1" << endl;
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
          delete current;
      }
      else if(current->getLeft() == NULL){
          cout << "1" << endl;
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
        cout << "2" << endl;
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
      else{
        cout << "3" << endl;
          Node* tempNode = current->getRight();
          int counter = 0;
          while(tempNode->getLeft() != NULL){
              tempNode = tempNode->getLeft();
              counter++;
          }
          current->setInformation(tempNode->getInformation());
          cout << tempNode->getInformation() << "INFO" << endl;
          if(counter == 0){
            cout << "2" << endl;
              current->setRight(tempNode->getRight());
              tempNode->getParent()->setRight(tempNode->getRight());
              if(tempNode->getRight() != NULL){
                tempNode->getRight()->setParent(tempNode->getParent());
              }
              
              cout << "4" << endl;
          }
          else{
            cout << "5" << endl;
              tempNode->getParent()->setLeft(tempNode->getLeft());
              if(tempNode->getLeft() != NULL){
                tempNode->getLeft()->setParent(tempNode->getParent());
              }
              
              cout << "6" << endl;
          }
          delete tempNode;
      }
    }
    else if(current->getInformation() > value){
        remove(0, root, current->getLeft(), value);
    }
    else if(current->getInformation() < value){
        remove(1, root, current->getRight(), value);
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
