#include <iostream>
#include "Node.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

/*Red and black tree program
  With a lot of help from the internet and some friends
 */


using namespace std;
void rotateLeft(Node*&, Node*&);
void rotateRight(Node*&, Node*&);
void addNode(Node*&, Node*);
void insert(Node*&, int);
void rule1(Node*&);
void rule2();
void rule3(Node*&, Node* &);
void rule4part1(Node*&, Node* &);
void rule4part2(Node *&, Node*&);
void applyRules(Node*&, Node*&);
void traverse(Node*, int);
void DeleteOneChild(Node*&);
void DeleteCase1(Node*&);
void DeleteCase2(Node*&);
void DeleteCase3(Node*&);
void DeleteCase4(Node*&);
void DeleteCase5(Node*&);
void DeleteCase6(Node*&);
Node* search(Node*, int);
void DeleteNode(Node*&, Node*&);
Node* getRoot(Node*);
Node* getSuc(Node*);

int main(){
	Node* head = NULL;
	char inType[100];
	char input[100];
	//ask for input type
	cout<<"Welcome to Red Black Tree, a program that creates a tree with different colored nodes that follows a particular set of rules!"<< endl;
	cout<<"Type (F) for file input and (M) for manual input"<<endl;
	cin>>inType;
	cin.ignore();
	//if file input
	if(strcmp(inType, "F") == 0){
	  //read from file
	  cout<<"Input the file name"<<endl;
	  char fileName[100];
	  cin.getline(fileName, sizeof(fileName));
	  ifstream fileStream;
	  fileStream.open(fileName);
	  if(fileStream){
	    fileStream.getline(input, sizeof(input));
	  }
	  //if file not found
	  else{
	    cout<<"File does not exist"<<endl;
	  }
	}
	//manual input	
	else if(strcmp(inType, "M") == 0){
	  cout<<"Enter the array split by spaces"<<endl;
	  cin.getline(input, 100);
	}
	//splits inputted array by spaces
	char* list = strtok(input, " ");
	while(list){
	  //inserts the node into the tree
	  insert(head, atoi(list));
	  list = strtok(NULL, " ");
	}
	while(true){
	  cout<<"Type ADD to add, PRINT to print, SEARCH to search for a value, QUIT to quit, and DELETE to delete a node"<<endl;
	  char* input = new char();
	  cin.getline(input, sizeof(input));
	  for(int i = 0; i<sizeof(input); i++){
	    input[i] = toupper(input[i]);
	  }
	  //Function to add a node into the tree
	  if(strcmp(input, "ADD") == 0){
	    int val;
	    cout<<"Enter the val you want to add: ";
	    cin>>val;
	    cin.ignore();
	    insert(head, val);
	  }	
	  //Function to visually display the tree
	  else if(strcmp(input, "PRINT") == 0){
	    traverse(head, 0);
	  }
	  //Function for the user to quit
	  else if(strcmp(input, "QUIT") == 0){
	    return 0;
	  }
	  else if(strcmp(input, "SEARCH") == 0){
	    int val;
	    cout<<"Enter the number that you want to search for: ";
	    cin>>val;
	    cin.ignore();
	    if(search(head, val) == NULL){
	      cout<<"The number was not found in the tree"<<endl;
	    }
	    else{
	      cout<<"The number was found in the tree"<<endl;
	    }
	  }
	  else if(strcmp(input, "DELETE") == 0){
	    int val;
	    cout<<"Enter the val you want to delete: ";
	    cin>>val;
	    cin.ignore();
	    Node* n = search(head, val);
	    if(n == NULL){
	      cout<<"The number to be deleted was not found in the tree"<<endl;
	    }
	    else{
	      DeleteNode(head, n);
	    }
	  }
	  
	}
}
//Function that inserts a node with a given value into the tree
void insert(Node* &head, int val){
  Node* n = new Node(val);
  addNode(head, n);
  //Repairs the tree by applying the 4 rules
  applyRules(n, head);
}
void addNode(Node* &head, Node* n){
  //If the current head is null the new node is the new head
  if(head == NULL){
    head = n;
    return;
  }
  //Adding the node from the bottom up formula
  if(head->getKey()<n->getKey()){
    if(head->getRight() == NULL){
      head->setRight(n);
      head->getRight()->setParent(head);
      return;
    }
    else{
      Node* right = head->getRight();
      addNode(right, n);
    }	
  }
  else{
    if(head->getLeft() == NULL){
      head->setLeft(n);
      head->getLeft()->setParent(head);
      return;
    }
    else{
      Node* left = head->getLeft();
      addNode(left, n);
    }
  }
}
//Function that repairs the tree based on the typical red and black tree rules
void applyRules(Node* &n, Node* &head){
  if(n->getParent() == NULL){
    rule1(n);
  }
  else if(n->getParent()->getColor() == 2){
    rule2();	
  }
  else if (n->getUncle() != NULL && n->getUncle()->getColor() == 1){
    rule3(n, head);
  }
  else{
    rule4part1(n, head);
  }
  
}
void rule1(Node* &n){
  n->setColor(2);
}
void rule2(){
  return;
}
void rule3(Node* &n, Node* &head){
  n->getParent()->setColor(2);
  n->getUncle()->setColor(2);
  n->getGrandparent()->setColor(1);
  Node* gp = n->getGrandparent();
  applyRules(gp, head);
}
void rule4part1(Node* &n, Node* &head){
  Node* p = n->getParent();
  Node* g = n->getGrandparent();
  if (n == p->getRight() && p == g->getLeft()) {
    p->rotateLeft();
    cout<<"test"<<endl;
    n = n->getLeft();
  } 
  else if (n == p->getLeft() && p == g->getRight()) {
    p->rotateRight();
    n = n->getRight();
  }
  rule4part2(n, head);
}
void rule4part2(Node* &n, Node* &head){
  Node* p = n->getParent();
  Node* g = n->getGrandparent();
  if (n == p->getLeft()) {
    g->rotateRight();
  } 
  else {
    g->rotateLeft();
  }
  if(g == head) head = p;
  p->setColor(2);
  g->setColor(1);
}

//Traversing the tree and print
void traverse(Node* head, int depth){
  //recursively go down the right branch
  if(head == NULL) {
    return;
  }
  if(head->getRight() != NULL) {
    traverse(head->getRight(), depth+1);
  }
  //spacing
  for (int i = 0; i < depth; i++) {
    cout << "      ";
  }
  //depending on the color, print the node color
  if(head->getColor() == 1) {
    cout <<head->getKey()<<"(Red)"<<endl;
  }
  else {
    cout<<head->getKey()<<"(Black)"<<endl;
  }
  //recursively go down the left branch
  if(head->getLeft() != NULL) {
    traverse(head->getLeft(), depth+1);
  }
}

void replaceNode(Node* &n, Node* &child){
  //Function that replaces nodes for deleting a child node
  child->setParent(n->getParent());
  if(n->getParent() == NULL){
    n = child;
  }
  else if(n == n->getParent()->getLeft()){
    n->getParent()->setLeft(child);
	} else{
    n->getParent()->setRight(child);
  }
}

Node* search(Node* h, int num){
  //if we found the number in the tree then return the node
  if(h == NULL || h->getKey() == num){
    return h;
  }
  //if the number is less then the current number recursively go left
  if(num<h->getKey()){
    Node* l = h->getLeft();
    return search(l, num);
  }
  //if the number is greater then the curret number recursively go right
  else if(num > h->getKey()){
    Node* r = h->getRight();
    return search(r, num);
  }
  
}
void DeleteNode(Node*& h, Node* &n){
  //if it the user wants to delete the root
  if(h == n && n->getLeft() == NULL && n->getRight() == NULL){
    delete n;
    n = NULL;
    return;
  }
  //if there are 2 children for the node to be deleted
  else if(n->getLeft() != NULL && n->getRight() != NULL){
    Node* left = n->getLeft();
    left = getSuc(left);
    n->setKey(left->getKey());
    DeleteOneChild(left);
    return;
    
  }
  DeleteOneChild(n);
  
}
void DeleteOneChild(Node* &n){
  //If the user wants to delete a child node
  Node* child;
  if(n->getRight() == NULL){
    child = n->getLeft();
  }
  else{
    child = n->getRight();
  }
  if(child == NULL){
    child = new Node(-1);
    child->setColor(2);
  }
  replaceNode(n, child);
  if(n->getColor() == 2){
    if(child->getColor() == 1){
      child->setColor(2);
    }
    else{
      DeleteCase1(child);
    }
  }
  if(child->getKey() == -1){
    if(child->getParent() != NULL){
      if(child == child->getParent()->getLeft()){
	child->getParent()->setLeft(NULL);
      }
      else{
	child->getParent()->setRight(NULL);
      }
    }
  }
}
Node* getRoot(Node* n){
  //Get root function to help with efficiency
  if(n->getParent() != NULL){
    getRoot(n->getParent());
  }
  return n;
}
void DeleteCase1(Node* &n){
  //First delete case
  if(n->getParent() != NULL){
    DeleteCase2(n); //If the node to be deleted has no parent, move on to case 2
  }
}
void DeleteCase2(Node* &n){
  //Second delete case
  Node* s = n->getSibling();
  if(s->getColor() == 1){
    n->getParent()->setColor(1);
    s->setColor(2);
    Node* p = n->getParent();
    if(n == n->getParent()->getLeft()){
      n->getParent()->rotateLeft();
    }
    else{
      n->getParent()->rotateRight();
    }
  }
  DeleteCase3(n); //Goes through each of the deleting rules for each node that is to be deleted from the tree.
}
void DeleteCase3(Node* &n){
  //Third delete case
  Node* s = n->getSibling();
  if((n->getParent()->getColor() == 2) && (s->getColor() == 2) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)) {
    s->setColor(1);
    Node* p = n->getParent();
    DeleteCase1(p);
  }
  else{
    DeleteCase4(n);
  }
}
void DeleteCase4(Node* &n){
  //Fourth delete case
  Node* s = n->getSibling();
  if((n->getParent()->getColor() == 1) && (s->getColor() == 2) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)){
    s->setColor(1);
    n->getParent()->setColor(2);
  }
  else{
    DeleteCase5(n);
  }
}
void DeleteCase5(Node* &n){
  //Fifth delete case
  Node* s = n->getSibling();
  if(s->getColor() == 2){
    if((n == n->getParent()->getLeft()) && (s->getRight()->getColor() == 2) && s->getLeft()->getColor() == 1){
      s->setColor(1);
      s->getLeft()->setColor(2);
      s->rotateRight();
    }
    else if((n==n->getParent()->getRight()) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)){
      s->setColor(1);
      s->getRight()->setColor(2);
      s->rotateLeft();
    }
  }	
  DeleteCase6(n);
}
void DeleteCase6(Node* &n){
  //Sixth delete case
  Node* s = n->getSibling();
  s->setColor(n->getParent()->getColor());
  n->getParent()->setColor(2);
  if(n == n->getParent()->getLeft()){
    s->getRight()->setColor(2);
    n->getParent()->rotateLeft();
    
  }
  else{
    s->getLeft()->setColor(2);
    n->getParent()->rotateRight();
  }
  
}
Node* getSuc(Node* head){
  //Used for efficiency for deleting nodes
  if(head->getRight() == NULL){
    return head;
  }
  getSuc(head->getRight());
}
