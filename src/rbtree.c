#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>


#include <assert.h>
#include <stdbool.h>


rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nill_node = (node_t *)calloc(1, sizeof(node_t));
  nill_node->color = RBTREE_BLACK;
  p->nil = nill_node;
  p->root = nill_node;
  return p;
}

//삭제예정
void print_nodes(rbtree *t, node_t *node) {
   if (node == t->nil) {
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
  free(node);
}

void delete_rbtree(rbtree *t) {
  delete_nodes(t, t->root);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
  if( x->right == t->nil) 
  {
    return;
  }
  
  node_t *y = x->right;
  x->right = y->left;
  
  if(y->left != t->nil) 
  {
    y->left->parent = x;
  }
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
  if( x->left == t->nil) 
  {
    return;
  }
  
  node_t *y = x->left;
  x->left = y->right;
  
  if(y->right != t->nil)
  {
    y->right->parent = x;
  } 
  y->parent = x->parent;
  if (x->parent == t->nil) 
  {
    t->root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void rbtree_insert_fix(rbtree *t, node_t *p) {
  while(p->parent->color == RBTREE_RED) {
    if (p->parent == p->parent->parent->left)
    {
      node_t *q = p->parent->parent->right; 

      if (q->color == RBTREE_RED) 
      {
        p->parent->color = RBTREE_BLACK;
        q->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        p = p->parent->parent;
      }
      else {
        if (p == p->parent->right)
        {
          p = p->parent;
          left_rotate(t, p);
        }
        p->parent->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        right_rotate(t, p->parent->parent);
        } 
      }
    else {
      node_t *q = p->parent->parent->left;
      if (q->color == RBTREE_RED) {
        p->parent->color = RBTREE_BLACK;
        q->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        p = p->parent->parent;
      }
      else 
      {   
          if(p == p->parent->left) 
          {
            p = p->parent;
            right_rotate(t, p);
          }

          p->parent->color = RBTREE_BLACK;
          p->parent->parent->color = RBTREE_RED;
          left_rotate(t, p->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;

  node_t *prev = t->nil;
  node_t *cur = t->root;
  
  while(cur != t->nil) 
  {
    prev = cur;
    if(new_node->key < cur->key)
    {
      cur = cur->left;
    }
    else 
    {
      cur = cur->right;
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
  node_t *cur = t->root;
  while (cur != t->nil)
  {
    if (key == cur->key) {
      return cur;
    }
    if (key < cur->key) {
      cur = cur->left;
    }
    else 
    {
      cur = cur->right;
    }
  }
  return NULL;
}

node_t *rbtree_min_from_node(const rbtree *t, node_t *p)
{
  node_t *prev = p;
  node_t *cur = p->right;
  while(cur != t->nil)
  {
    prev = cur;
    cur = cur->left;
  }
  return prev;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;
  while(cur->left != t->nil) 
  {
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;
  while(cur->right != t->nil) 
  {
    cur = cur->right;
  }
  return cur;
}

void rbtree_erase_fix(rbtree *t, node_t *p) {
  while (p != t->root && p->color == RBTREE_BLACK) 
  {
    if(p == p->parent->left) 
    {
      node_t *w = p->parent->right;
      if(w->color == RBTREE_RED) 
      {
        w->color = RBTREE_BLACK;
        p->parent->color = RBTREE_RED;
        left_rotate(t, p->parent);
        w = p->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK ){
        w->color = RBTREE_RED;
        p = p->parent;
      }
      else {
        if(w->right->color == RBTREE_BLACK) 
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = p->parent->right;
        }
        w->color = p->parent->color;
        p->parent->color = RBTREE_BLACK;

        w->right->color = RBTREE_BLACK;
        left_rotate(t, p->parent);
        p = t->root;
      }
    }
    else //오른쪽 자식일 때 
    {
      node_t *w = p->parent->left;
      if(w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        p->parent->color = RBTREE_RED;
        right_rotate(t, p->parent);
        w = p->parent->left;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        p = p->parent;
      }
      else 
      {
        if(w->left->color == RBTREE_BLACK) 
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = p->parent->left;
        }
        w->color = p->parent->color;
        p->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, p->parent);
        p = t->root;
      }
    }
  }
  p->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *q;
  node_t *r;
  if (p->left == t->nil || p->right == t->nil) 
  {
    q = p; 
  }
  else
  {
    q =  rbtree_min_from_node(t, p);
  }

  if (q->left != t->nil) 
  {
    r = q->left;
  }
  else
  {
    r = q->right;
  }

  r->parent = q->parent;

  if (q->parent == t->nil)
  {
    t->root = r;
  }
  else if(q == q->parent->left) 
  {
    q->parent->left = r;
  }
  else
  {
    q->parent->right = r;
  }

  if (q != p)
  {
    p->key = q->key;
  }

  if (q->color == RBTREE_BLACK)
  { 
    rbtree_erase_fix(t, r);
  }
  free(q);
  return 0;
}

// void travel_in_order(rbtree *t, key_t *ret, node_t *node, int* idx) {
//    if (node == t->nil) {
//     return;
//   }
  
//   // print_nodes(t, node->left);
//   // printf("key : %d, color : %d\n", node->key, node->color);
//   // print_nodes(t, node->right);
// }

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // travel_in_order(t, arr, t->root, 0);
  return 0;
}
