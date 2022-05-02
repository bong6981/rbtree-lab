#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nill_node = (node_t *)calloc(1, sizeof(node_t));
  nill_node->color = RBTREE_BLACK;
  p->nil = nill_node;
  p->root = nill_node;
  return p;
}

//삭제예정
void print_nodes(rbtree *t, node_t *node) {
   if (node == t->nil) {
    puts("nill!");
    return;
  }

  print_nodes(t, node->left);
  printf("key : %d, color : %d\n", node->key, node->color);
  print_nodes(t, node->right);

}

//삭제예정
void print_rbtree(rbtree *t) {
  print_nodes(t, t->root);
}

void delete_nodes(rbtree *t, node_t *node) {

  if (node == t->nil) {
    return;
  }

  delete_nodes(t, node->left);
  delete_nodes(t, node->right);
  // 삭제예정
  printf("delete !! key : %d, color : %d\n", node->key, node->color);
  free(node);
}


void delete_rbtree(rbtree *t) {
  print_rbtree(t);
  delete_nodes(t, t->root);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) 
  {
    t->root = y;
  }
  else if (x == x->parent->left) 
  {
    x->parent->left = y;
  }
  else 
  {
    x->parent->right = y; 
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) 
  {
    t->root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->right = x;
  x->parent = y;
}

void rbtree_insert_fix(rbtree *t, node_t *new_node) {
  while(new_node->parent->color == RBTREE_RED) {
    if (new_node->parent == new_node->parent->parent->left)
    {
      node_t *uncle = new_node->parent->parent->right; 

      if (uncle->color == RBTREE_RED) 
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else {
        if (new_node == new_node->parent->right)
        {
          new_node = new_node->parent;
          left_rotate(t, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        right_rotate(t, new_node->parent->parent);
        } 
      }
    else {
      node_t *uncle = new_node->parent->parent->left;
      if (uncle->color == RBTREE_RED) {
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else 
      {
          if(new_node == new_node->parent->left) 
          {
            new_node = new_node->parent;
            right_rotate(t, new_node);
          }

          new_node->parent->color = RBTREE_BLACK;
          new_node->parent->parent->color = RBTREE_RED;
          left_rotate(t, new_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //데이터로 새로운 노드 생성
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;

  node_t *prev = t->nil;
  node_t *now = t->root;
  
  while(now != t->nil) 
  {
    prev = now;
    if(new_node->key < now->key)
    {
      now = now->left;
    }
    else 
    {
      now = now->right;
    }
  }

  new_node->parent = prev;
  if(prev == t->nil) 
  {
    t->root = new_node; 
  }
  else if(new_node->key < prev->key)
  {
    prev->left = new_node;
  }
  else
  {
    prev->right = new_node;
  }

  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;
  
  rbtree_insert_fix(t, new_node);
  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *now = t->root;
  while (now != t->nil)
  {
    if (key == now->key) {
      return now;
    }
    if (key < now->key) {
      now = now->left;
    }
    else 
    {
      now = now->right;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
