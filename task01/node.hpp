#ifndef NODE_LIB
#define NODE_LIB

#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int id;
  std::vector<Node*> childs;
  Node* parent;
};

Node* createNode(int id);
void print_node(Node* node);


Node* createNode(int id) {
  Node* newNode = new Node();
  newNode->id = id;
  newNode->parent = NULL;
  return newNode;
}


void print_node(Node* node) {
  cout << "Node id is: " << node->id << endl;
  if (node->parent != NULL) {
    cout << "Parent id is: " << node->parent->id << endl;
  }
  else {
    cout << "The node is a root" << endl;
  }

  if (!node->childs.empty()) {
    for (int i = 0; i < (int)node->childs.size(); i++) {
      cout << "Child " << i << " id is: " << node->childs[i]->id << endl;
    }
  } 
  else {
    cout << "The node has no children!" << endl;
  }
  cout << "-------------------------" << endl << endl;
}
#endif
