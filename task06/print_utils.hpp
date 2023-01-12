#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct tree_node {
  int id;
  vector<tree_node> childs;
};

struct ham_dist_improved {
  int start_pos = -1;
  int cost = -1;
};

typedef vector<int> VEC;
typedef vector<int>* VEC_P;
typedef vector<vector<int>> VEC_2D;
typedef struct ham_dist_improved DIST;

template<class T> 
  void break_point(T input);
void break_point();

int break_point_n = 0;
char break_point_arr[1000];

template<class T> 
void break_point(T input) {
  cout << "==BP== value: " << input << endl; // print the input
  cin >> break_point_arr[break_point_n]; // pauses the programm here 
  break_point_n = min(break_point_n+1, 1000-1);
}

void break_point() {
  cout << "==BP==" << endl;
  cin >> break_point_arr[break_point_n]; // pauses the programm here 
}

void print_chain(VEC base_chain) {
  for(int i = 0; i < base_chain.size(); i++) {
    std::cout << base_chain[i] << " ";
  }
  std::cout << std::endl << std::endl;;
}

void print_ct(tree_node new_node, int idx)
{
  for(int i = 0; i < idx; i++)
    std::cout << ". ";
  std::cout << new_node.id << std::endl;

  for(int i = 0; i < (int)new_node.childs.size(); i++) 
    print_ct(new_node.childs[i], idx+1);
}

void print_clip_tree(std::vector<tree_node> clip_tree)
{
  for(int i = 1; i < (int)clip_tree.size(); i++) {
    if(clip_tree[i].childs.size() > 0) 
      print_ct(clip_tree[i], 0);
  }
  std::cout << std::endl;
}

void print_dist_table(vector<vector<DIST>> dist_table) {
  int n_rows = dist_table.size();
  int n_cols = dist_table[0].size();

  int n_txt_len = 3; 

  for(int i = 0; i < n_rows; i++) {
    for(int j = 0; j < n_cols; j++) {
      stringstream ss;
      std::string p_str;
      ss << dist_table[i][j].cost;
      ss >> p_str;
      for(int i = 0; i < n_txt_len-p_str.size(); i++)
        std::cout << " ";
      std::cout << p_str;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
#endif

