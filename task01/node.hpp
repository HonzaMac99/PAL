#ifndef NODE_LIB
#define NODE_LIB

#include <vector>

struct Node {
  int id;
  std::vector<Node*> childs;
  Node* parent;
};

Node* createNode(int id) {
  Node* newNode = new Node();
  newNode->id = id;
  newNode->parent = NULL;
  return newNode;
}
#endif
