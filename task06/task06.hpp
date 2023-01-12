#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

// struct tree_node {
//   int id;
//   std::vector<tree_node> childs;
// };
// 
// struct ham_dist_improved {
//   int start_pos = -1;
//   int cost = -1;
// };
//
// --> defined in print_utils.hpp 

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;
typedef std::vector<tree_node> VEC_TREE;
typedef struct ham_dist_improved DIST;

VEC generate_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols);
void gen_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols,
            VEC* base_chain, VEC new_chain, int row_id, int col_id);
VEC_TREE get_clip_tree(VEC_2D clip_schemes);
void expand_clip_tree(tree_node* new_node, VEC clip_scheme, int idx);
struct tree_node get_new_node(int node_id);
struct tree_node* get_new_node_ptr(int node_id);
void find_best_clip(vector<vector<DIST>> dist_table, VEC_TREE clip_tree, VEC b_chain, 
        int clip_f, int row, int col, int* best_cost, int* best_pos);
void find_best_chain(VEC b_chain, VEC d_chain, VEC_TREE clip_tree, 
    int clip_f, int repl_f, int* start_pos, int* end_pos, int* cost);


VEC operator + (const VEC a, const VEC b) {
    VEC c = a;
    c.insert(c.end(), b.begin(), b.end());
    return c;
}


struct tree_node get_new_node(int node_id) {
  struct tree_node new_node;
  new_node.id = node_id;
  return new_node;
}


struct tree_node* get_new_node_ptr(int node_id) {
  struct tree_node new_node; // initialize the new_node
  struct tree_node* new_node_ptr = &new_node; // get its ptr
  new_node_ptr->id = node_id;
  return new_node_ptr;
}


void expand_clip_tree(tree_node* new_node, VEC clip_scheme, int idx)
{
  int exp_node_idx = -1;
  for(int i = 0; i < (int)new_node->childs.size(); i++) {
    if(new_node->childs[i].id == clip_scheme[idx]) {
      exp_node_idx = i;
      break;
    }
  }
  
  if (exp_node_idx == -1) { 
    struct tree_node child_node = get_new_node(clip_scheme[idx]);

    if (idx == 0) {
      struct tree_node end_node = get_new_node(-1);
      child_node.childs.push_back(end_node);
    }
    else {
      expand_clip_tree(&child_node, clip_scheme, idx-1);
    }

    new_node->childs.push_back(child_node);
  }
  else {
    if (idx == 0) {
      struct tree_node end_node = get_new_node(-1);
      new_node->childs.push_back(end_node);
    }
    else {
      expand_clip_tree(&new_node->childs[exp_node_idx], clip_scheme, idx-1);
    }
  }
}


std::vector<tree_node> get_clip_tree(VEC_2D clip_schemes)
{
  // min len is 1, so there are 19 different lengths
  // index 0 of clip_tree is unused
  int max_link_len = 20; 
  std::vector<tree_node> clip_tree(max_link_len);

  for(int i = 1; i < max_link_len; i++) {
    struct tree_node new_node = get_new_node(i);
    clip_tree[i] = new_node;
  }

  for(int i = 0; i < clip_schemes.size(); i++) {
    VEC clip = clip_schemes[i];
    int index = (int)clip.size()-1;
    int last_clip_link = clip[index];

    if (index == 0) {  // length of the clip is only 1
      struct tree_node new_node = get_new_node(-1);
      clip_tree[last_clip_link].childs.push_back(new_node);
    }
    else {
      expand_clip_tree(&clip_tree[last_clip_link], clip, index-1);
    }
  }
  return clip_tree;
}


void gen_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols,
            VEC* base_chain, VEC new_chain, int row_id, int col_id) 
{
  new_chain.push_back(prod_matrix[row_id][col_id]);

  if (row_id == n_rows-1) {
    *base_chain = *base_chain + new_chain;
    return;
  }

  if (col_id == 0) { 
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id+1);
  }
  else if (col_id == n_cols-1) {
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id-1);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
  }
  else {
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id-1);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id+1);
  }
}


VEC generate_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols) 
{
  VEC base_chain, new_chain;
  for(int col_id = 0; col_id < n_cols; col_id++) {
    gen_base_chain(prod_matrix, n_rows, n_cols, &base_chain, new_chain, 0, col_id); 
  }
  return base_chain;
}


void find_best_clip(vector<vector<DIST>> dist_table, VEC_TREE clip_tree, VEC b_chain, 
        int clip_f, int row, int col, int* best_cost, int* best_pos)
{
  std::queue<tree_node> clip_q;
  int end_link = b_chain[col-1];
  int clip_cost, new_cost;
  clip_q.push(clip_tree[end_link]);

  int steps_back = 1;
  int picked_childs = 0;
  while (not clip_q.empty() and col-steps_back >= row) 
  {
    int start_link = b_chain[col-steps_back];
    struct tree_node new_node = clip_q.back();
    clip_q.pop();

    for(int i = 0; i < new_node.childs.size(); i++) 
    {
      // id 0 signals the final state (end) of the clip_tree
      if (new_node.childs[i].id == -1) 
      {
        clip_cost = (steps_back == 1) ? end_link*clip_f : (start_link + end_link)*clip_f; 
        new_cost = dist_table[row][col-steps_back].cost + clip_cost;
        if (new_cost < *best_cost) {
          *best_cost = new_cost;
          *best_pos = dist_table[row][col-steps_back].start_pos;
#if PRINT_INFO 
          std::cout << "Found new best: " << *best_cost
                    << " from [" << row << "][" << col-steps_back << "]: "
                    << dist_table[row][col-steps_back].cost << std::endl;
          std::cout << " new_node.id: " << new_node.id 
                    << " steps_back: " << steps_back << std::endl;
#endif
        }
        picked_childs++;
      }
      else if (new_node.childs[i].id == b_chain[col-steps_back-1]) 
      {
        clip_q.push(new_node.childs[i]);
        picked_childs++;
      }

      if (picked_childs == 2) {
        picked_childs = 0; 
        break;
      }
    }
    steps_back++;
  }
}


void find_best_chain(VEC b_chain, VEC d_chain, VEC_TREE clip_tree, 
    int clip_f, int repl_f, int* start_pos, int* end_pos, int* cost)
{
  int b_ch_len = b_chain.size();
  int d_ch_len = d_chain.size();
  vector<vector<DIST>> dist_table(d_ch_len+1, vector<DIST>(b_ch_len+1));

  int repl_cost, best_cost, best_pose;
  
  for(int j = 0; j < b_ch_len+1; j++) {
    dist_table[0][j].cost = 0;
    dist_table[0][j].start_pos = j+1;
  }

  for(int i = 1; i < d_ch_len+1; i++) {
    repl_cost = abs(b_chain[i-1] - d_chain[i-1])*repl_f;
    dist_table[i][i].cost = dist_table[i-1][i-1].cost + repl_cost;
    dist_table[i][i].start_pos = dist_table[i-1][i-1].start_pos;
  }

  for(int i = 1; i < d_ch_len+1; i++) {
    for(int j = i+1; j < b_ch_len+1; j++) {
      repl_cost = abs(b_chain[j-1] - d_chain[i-1])*repl_f;

      best_cost = dist_table[i-1][j-1].cost + repl_cost;
      best_pose = dist_table[i-1][j-1].start_pos;

      find_best_clip(dist_table, clip_tree, b_chain, clip_f, i, j, &best_cost, &best_pose);

      dist_table[i][j].cost = best_cost;
      dist_table[i][j].start_pos = best_pose;

    }
  }

#if PRINT_INFO
  print_dist_table(dist_table);
#endif

  int new_cost, new_len, old_len;
  *start_pos = 0;
  *end_pos = 0;
  *cost = 10000000;
  for(int j = d_ch_len; j < b_ch_len+1; j++) 
  {
    new_cost = dist_table[d_ch_len][j].cost;
    new_len = j - dist_table[d_ch_len][j].start_pos + 1;
    old_len = *end_pos - *start_pos + 1; 

    if(new_cost < *cost or (new_cost == *cost and new_len < old_len)) 
    {
      *cost = new_cost;
      *start_pos = dist_table[d_ch_len][j].start_pos;
      *end_pos = j; 
    }
  }
}
#endif

