#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

using namespace std;

class Node{
 public:
  //Constructor
  Node(int);
  //Destructor
  ~Node();
  //Getters
  int getKey();
  Node* getLeft();
  Node* getRight();
  int getColor();
  Node* getParent();
  Node* getUncle();
  Node* getSibling();
  Node* getGrandparent();
  //Setters
  void setKey(int);
  void setLeft(Node*);
  void setRight(Node*);
  void setColor(int);
  void setParent(Node*);
  //Rotations
  void rotateLeft();
  void rotateRight();
 private:
  Node* right;
  Node* left;
  Node* parent;
  int color;
  int key;
};
#endif
