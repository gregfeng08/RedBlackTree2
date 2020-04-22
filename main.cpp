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
