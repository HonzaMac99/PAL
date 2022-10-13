#include <iostream> 
#include <vector>

using namespace std;

struct Node {
  int id;
  vector<Node*> childs;
  Node* parent;
};


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


int main(int argc, char* argv[]) {
  
  Node* root = createNode(1);
  Node* child1 = createNode(11);
  Node* child2 = createNode(12);
  root->childs.push_back(child1);
  child1->parent = root;
  root->childs.push_back(child2);
  child2->parent = root;
  root->childs.push_back(createNode(13));
  root->childs[2]->parent = root;

  print_node(root);
  print_node(child2);
  
  return 0;
}




