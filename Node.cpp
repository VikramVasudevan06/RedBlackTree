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
char Node :: getColor(){
  return color;

}
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
