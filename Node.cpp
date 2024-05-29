#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

//constructor
Node:: Node(){
  left = NULL;
  right = NULL;
  parent = NULL;
  color = 'r';
}

//destructor
Node :: ~Node(){
  parent = NULL;
}
//function that gets the color of the node.
char Node :: getColor(){
  return color;

}

//function that gets the successor of the node.
Node* Node :: getSuccessor(){
  if(this->getRight() == NULL && this->getLeft() != NULL){
    return this->getLeft();
  }
  else if(this->getLeft() == NULL && this->getRight() != NULL){
    return this->getRight();
  }
  else if(this->getLeft() != NULL && this->getRight() != NULL){
    Node* tempNode = this->getRight();
    if(this->getRight()->getLeft() != NULL){
      while(tempNode->getLeft() != NULL){
        tempNode = tempNode->getLeft();
      }
    }
    return tempNode;
  }
  else if(this->getLeft() == NULL && this->getRight() == NULL){
    return NULL;
  }
  return NULL;


}
//function that gets the sibling of the node.
Node* Node :: getSibling(){
  if(this->getParent()->getRight() != this){
    return this->getParent()->getRight();
  }
  return this->getParent()->getLeft();
  

}
//function that gets the uncle of the node.
Node* Node::getUncle(){
  Node* uncle = new Node();
  if(this->getParent()->getInformation() <= this->getInformation()){
    uncle = this->getParent()->getLeft();
  }
  else if(this->getParent()->getInformation() > this->getInformation()){
    uncle = this->getParent()->getRight();
  }
  return uncle;
}
//function that sets the color of the node.
void Node :: setColor(char newColor){
    color = newColor;
}
//sets the current node's right node.
void Node :: setRight(Node* newRight){
  right = newRight;

}
//sets the current node's left node.
void Node :: setLeft(Node* newLeft){
  left = newLeft;

}

//sets the current node's next.
void Node :: setParent(Node* newparent){
  parent = newparent;
}

//returns the current node's next
Node* Node:: getParent(){
  return parent;
}

//returns the current node's right node.
Node* Node :: getRight(){
  return right;
}

//returns the current node's left node.
Node* Node :: getLeft(){
  return left;
}

//sets the char stored by the node.
void Node :: setInformation(int value){
  data = value;
}

//returns the char stored by the node.
int Node :: getInformation(){
  return data;

}
