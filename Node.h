#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;


class Node{
 public:
  Node();
  ~Node();
  //initializing variables
  char color = 'r';
  Node* parent;
  Node* left;
  Node* right;
  int data;
  //function prototypes
  void setColor(char newColor);
  char getColor();
  Node* getUncle();
  void setRight(Node* newRight);
  void setLeft(Node* newLeft);
  Node* getRight();
  Node* getLeft();
  void setParent(Node* newparent);
  Node* getParent();
  void setInformation(int value);
  int getInformation();
 
};


#endif
