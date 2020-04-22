#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;
//Constructor
Node::Node(int newKey) {
  key = newKey;
  right = NULL;
  left = NULL;
  parent = NULL;
  color = 1; //Use black for true red for false
}

//Destructor
Node::~Node() {

}

//Getters
int Node::getKey() {
  return key;
}
Node* Node::getLeft() {
  return left;
}
Node* Node::getRight() {
  return right;
}
Node* Node::getParent() {
  return parent;
}
Node* Node::getGrandparent() {
  return parent->getParent();
}
Node* Node::getUncle() {
  if (parent == NULL) {
    return NULL;
  }
  else {
    return parent->getSibling();
  }
}
Node* Node::getSibling() {
  if (parent == NULL) {
    return NULL;
  }
  else {
    if (this == parent->getLeft()) {
      return parent->getRight();
    } else {
      return parent->getLeft();
    }
  }
}
int Node::getColor() {
  return color;
}

//Setters
void Node::setKey(int newKey) {
  key = newKey;
}
void Node::setLeft(Node* newLeft) {
  left = newLeft;
}
void Node::setRight(Node* newRight) {
  right = newRight;
}
 void Node::setParent(Node* newParent) {
  parent = newParent;
}
void Node::setColor(int newColor) {
  color = newColor;
}

//Left and Right rotations modified from GeeksForGeeks
void Node::rotateLeft(){
	Node* r = right;
	Node* p = parent;
	if(r == NULL) return;
	right = r->getLeft();
	r->setLeft(this);
	parent = r;
	if(right != NULL){
		right->setParent(this);
	}
	if (p != NULL) {
		if (this == p->getLeft()) {
			p->setLeft(r);
		} else if (this == p->getRight()) {
			p->setRight(r);
		}
	}
	r->setParent(p);
}
void Node::rotateRight() {
	Node* l = left;
	Node* p = parent;
	if(l == NULL) return;
	left = l->getRight();
	l->setRight(this);
	parent = l;

	if (left != NULL) {
		left->setParent(this);
	}

	if (p != NULL) {
		if (this == p->getLeft()) {
			p->setLeft(l);
		} else if (this == p->getRight()) {
			p->setRight(l);
		}
	}
	l->setParent(p);
}




