#ifndef NODE_LIB
#define NODE_LIB

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<class T> void break_point(T input);
void break_point();

struct Node {
  int id;
  int index = 0; // unique node number (>0) for scc search 
  int lowlink = 0; // ties node to others in SCC
  bool instack = false; // stack utilities
};



// -------------- stack for tarjan's algorithm -----------------
class t_stack {
  std::stack<int> t_stack;
public:
  
  void push_node(int id) {
    t_stack.push(id);
  }

  int get_top() {
    int node_id = t_stack.top();
    return node_id;
  }

  int pop_node() {
    int node_id = t_stack.top();
    t_stack.pop();
    return node_id;
  }
};
// -------------------------------------------------------------

#endif

