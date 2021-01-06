
// CARON Maxime TP3A

#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_array(struct array *self){
  for(size_t i =0; i<self->size; ++i){
    printf("[%d]", self->data[i]);
  }
  printf("\n");
}

void array_create(struct array *self) {
  self-> capacity = 10;
  self-> size = 0;
  self-> data = calloc(self-> capacity, sizeof(int));
}

void array_copy(int *copy, const int *copied, size_t size){
  for(size_t i = 0; i<size; ++i){
    copy[i] = copied[i];
  }
}

void array_create_from(struct array *self, const int *other, size_t size) {
  self-> capacity = size*2;
  self-> size = size;
  self-> data = calloc(self-> capacity, sizeof(int));
  array_copy(self->data, other, size);
}

void array_destroy(struct array *self){
  if(self-> data != NULL)free(self->data);
}

bool array_empty(const struct array *self) {
  if(self-> size > 0){
    return false;
  }
  return true;
}

size_t array_size(const struct array *self) {
  return self-> size;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
  if(self-> size != size){
    return false;
  }
  for(size_t i = 0; i < size; ++i){
    if(self-> data[i] != content[i]){
      return false;
    }
  }
  return true;
}

void array_size_up(struct array *self,int *copied){
  if(self->capacity <= 1) self-> capacity = 10;
  else self-> capacity = self->size*2;
  self->data = calloc(self->capacity,sizeof(int));
  for(size_t i = 0; i<self->size; ++i){
    self->data[i] = copied[i];
  }
}

void array_push_back(struct array *self, int value) {
  if((self-> capacity-self-> size)<2) array_size_up(self, self->data);
  self->data[self->size] = value;
  self->size +=1;
}

void array_pop_back(struct array *self) {
  self-> data[self-> size-1] = 0;
  self-> size = self-> size-1;
}

void array_insert(struct array *self, int value, size_t index) {
  if((self-> capacity-self-> size)<2) array_size_up(self, self->data);
  for(size_t i = self->size; i > index; --i){
    self->data[i] = self-> data[i-1];
  }
  self->size +=1;
  self->data[index] =  value;
}

void array_remove(struct array *self, size_t index) {
  for(size_t i = index; i < self->size ; ++i){
    self->data[i] = self-> data[i+1];
  }
  self->size -=1;
}

int array_get(const struct array *self, size_t index) {
  if(index < self->size) return self-> data[index];
  return 0;
}

void array_set(struct array *self, size_t index, int value) {
  if(self-> size >= index){
    self-> data[index] = value;
  }
}

size_t array_search(const struct array *self, int value) {
  size_t i = 0;
  while (i < self-> size && self-> data[i] != value) {
    i++;
  }
  return i;
}


size_t array_search_sorted(const struct array *self, int value) {
  size_t i = 0;
  while (i < self-> size && self-> data[i] != value) {
    i++;
  }
  return i;
}

bool array_is_sorted(const struct array *self) {
  for(size_t i = 1; i < self->size; ++i){
    if(self->data[i] < self->data[i-1]) return false;
  }
  return true;
}

void array_swap(struct array *self, size_t i, size_t j){
  int stock = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = stock;
}

ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
  ptrdiff_t pivot_index = i;
  const int pivot = self->data[pivot_index];
  array_swap(self, pivot_index, j);
  ptrdiff_t l = i;
  for (ptrdiff_t k = i; k < j; ++k) {
    if (self->data[k] < pivot) {
      array_swap(self, k, l);
      ++l;
    }
  }
  array_swap(self, l, j);
  return l;
}

void array_quick_sort_partial(struct array *self,ptrdiff_t i, ptrdiff_t j) {
  if (i < j) {
    ptrdiff_t p = array_partition(self, i, j);
    array_quick_sort_partial(self, i, p - 1);
    array_quick_sort_partial(self, p + 1, j);
  }
}

void array_quick_sort(struct array *self){
  array_quick_sort_partial(self,0,self->size-1);
}

void heapify(struct array *self, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && self->data[l] > self->data[largest])largest = l;
    if (r < n && self->data[r] > self->data[largest])largest = r;
    if (largest != i) {
        array_swap(self,i,largest);
         heapify(self, n, largest);
    }
}

void array_heap_sort(struct array *self){
  int n = (int)(self->size);
  for (int i = n / 2 - 1; i >= 0; i--) heapify(self, n, i);
  for (int i = n - 1; i > 0; i--){
      array_swap(self,0,i);
      heapify(self, i, 0);
  }
}

bool array_is_heap(const struct array *self) {
  for(size_t i=0; i<self->size;++i){
    if(2*i+1<self->size){
      if(self->data[i]<self->data[2*i+1])return false;
      if(2*i+2<self->size){
        if(self->data[i]<self->data[2*i+2])return false;
      }
    }
  }
  return true;
}

void array_heap_add(struct array *self, int value) {
  size_t i = self->size;
  array_push_back(self,value);
  while (i > 0) {
    size_t j = (i - 1) / 2;
    if (self->data[i] < self->data[j]) {
      break;
    }
    array_swap(self, i, j);
    i = j;
  }
}

int array_heap_top(const struct array *self) {
  return self->data[0];
}

void array_heap_remove_top(struct array *self) {
  size_t n = (int)(self->size);
  self->data[0] = self->data[n-1];
  size_t i =0;
  while (i < ((n)/2)){
    size_t lt = 2 * i + 1;
    size_t rt = 2 * i + 2;
    if (self->data[i] > self->data[lt] && self->data[i] > self->data[rt]) {
      break;
    }
    size_t j = (self->data[lt] > self->data[rt]) ? lt : rt;
    array_swap(self, i, j);
    i = j;
  }
  array_pop_back(self);
}

/*
 * list
 */

void list_create(struct list *self) {
  self -> first =  NULL;
}

void list_print(struct list *self){
  struct list_node *curr = self->first;
  while(curr != NULL){
    printf("%d,",curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void list_create_from(struct list *self, const int *other, size_t size) {
  self->first = malloc(sizeof(struct list_node));
  struct list_node *curr = self-> first;
  curr->data = other[0];
  for(size_t i=1; i<size; ++i){
   struct list_node *new = malloc(sizeof(struct list_node));
   new->data = other[i];
   curr->next = new;
   curr = curr->next;
  }
  curr->next = NULL;
}

void node_destroy(struct list_node *curr){
  if(curr->next == NULL){
    free(curr);
    return;
  }
  node_destroy(curr->next);
}

void list_destroy(struct list *self) {
  if(list_empty(self) != true)node_destroy(self->first);
}

bool list_empty(const struct list *self) {
  return(self == NULL || self->first == NULL);
}

size_t list_size(const struct list *self) {
  struct list_node *curr = self->first;
  size_t size = 0;
  while (curr != NULL) {
    ++size;
    curr = curr->next;
  }
  return size;
}

bool list_equals(const struct list *self, const int *data, size_t size){
  if(list_empty(self) && size!=0) return false;
  if(list_size(self)!=size)return false;
  struct list_node *curr = self->first;
  for(size_t i=0; i<size; ++i){
    if(curr->data != data[i]) return false;
    curr = curr->next;
  }
  return true;
}

void list_push_front(struct list *self, int value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->data = value;
  new->next = self->first;
  self->first = new;
}

void list_pop_front(struct list *self) {
  if(list_size(self)>0){
    self->first = self->first->next;
  }
}

void list_push_back(struct list *self, int value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->data = value;
  new->next = NULL;
  if(self->first == NULL){
    self->first = new;
  }
  else{
    struct list_node *curr = self->first;
    while(curr->next != NULL){
      curr = curr->next;
    }
    curr->next = new;
  }
}

void list_pop_back(struct list *self) {
  struct list_node *curr =self->first;
  if(curr->next == NULL){
    free(curr);
    self->first = NULL;
  }
  else{
    struct list_node *theNext =curr->next;
    while(theNext->next != NULL){
      theNext = theNext->next;
      curr = curr->next;
    }
    free(theNext);
    curr->next = NULL;
  }
}


void list_insert(struct list *self, int value, size_t index) {
  if(index == 0)list_push_front(self,value);
  else{
    struct list_node *curr = self->first;
    struct list_node *new = malloc(sizeof(struct list_node));
    new->data = value;
    for(size_t i=0; i<index-1;++i){
      curr = curr->next;
    }
    new->next = curr->next;
    curr->next = new;
  }
}


void list_remove(struct list *self, size_t index) {
  if(index == 0)list_pop_front(self);
  else{
    struct list_node *buffer = malloc(sizeof(struct list_node));
    struct list_node *curr = self->first;
    for(size_t i=0; i<index-1;++i){
      curr = curr->next;
    }
    buffer = curr->next;
    curr->next = buffer->next;
    free(buffer);
  }
}

int list_get(const struct list *self, size_t index) {
  if(index<list_size(self)){
    struct list_node *curr = self->first;
    for(size_t i=0; i<index; ++i){
      curr=curr->next;
    }
    return curr->data;
  }
  else return 0;
}

void list_set(struct list *self, size_t index, int value) {
  if(index<list_size(self)){
    struct list_node *curr = self->first;
    for(size_t i=0; i<index; ++i){
      curr=curr->next;
    }
    curr->data = value;
  }
}

size_t list_search(const struct list *self, int value) {
  struct list_node *curr = self->first;
  for(size_t i=0; i<list_size(self);++i){
    if(curr->data == value) return i;
    curr = curr->next;
  }
  return list_size(self);
}

bool list_is_sorted(const struct list *self) {
  if(list_empty(self))return true;
  struct list_node *curr = self->first;
  while(curr->next!=NULL){
    if(curr->data > curr->next->data) return false;
    curr =curr->next;
  }
  return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
  struct list_node *curr = self->first;
  for(size_t i=0; i<list_size(self);++i){
    if(i<list_size(self)/2)list_push_back(out1,curr->data);
    else list_push_back(out2,curr->data);
    curr=curr->next;
  }
  list_destroy(self);
  self->first = NULL;
}


void list_merge(struct list *self, struct list *in1, struct list *in2) {
  while(in1->first!=NULL && in2->first!=NULL){
    if(in1->first->data<in2->first->data){
      list_push_back(self,in1->first->data);
      list_pop_front(in1);
    }
    else{
      list_push_back(self,in2->first->data);
      list_pop_front(in2);
    }
  }
  if(in2->first!=NULL){
    while(in2->first!=NULL){
      list_push_back(self,in2->first->data);
      list_pop_front(in2);
    }
  }
  else if(in1->first!=NULL){
    while(in1->first!=NULL){
      list_push_back(self,in1->first->data);
      list_pop_front(in1);
    }
  }
}

void list_merge_sort(struct list *self) {
  if(list_size(self) == 1){
    return;
  }
  struct list *part1 = malloc(sizeof(struct list));
  struct list *part2 = malloc(sizeof(struct list));
  list_create(part1);
  list_create(part2);
  list_split(self, part1, part2);
  list_merge_sort(part1);
  list_merge_sort(part2);
  list_merge(self, part1, part2);
  free(part1);
  free(part2);
}


/*
 * tree
 */

void tree_create(struct tree *self) {
  self->root = NULL;
}

struct tree_node *tree_del_min(struct tree_node *node, struct tree_node **min){
  if(node->left == NULL){
    struct tree_node *right =node->right;
    node->right = NULL;
    *min = node;
    return right;
  }
  node->left = tree_del_min(node->left,min);
  return node;
}

struct tree_node *tree_destroy_partial(struct tree_node *node){
  struct tree_node *left = node->left;
  struct tree_node *right = node->right;
  free(node);
  node =NULL;
  if((left == NULL)&&(right ==NULL)){
    return NULL;
  }
  if(left == NULL){
    return right;
  }
  if(right == NULL){
    return left;
  }
  right = tree_del_min(right,&node);
  node->left = left;
  node->right = right;
  return node;
}

void tree_destroy(struct tree *self) {
  struct tree_node *node;
  size_t size = tree_size(self);
  for(size_t i=0; i<size; ++i){
    node= self->root;
    self->root = tree_destroy_partial(node);
  }
}

bool tree_node_search(const struct tree_node *self, int value){
  if (self == NULL) {
    return false;
  }
  if (value < self->data) {
    return tree_node_search(self->left, value);
  }
  if (value > self->data) {
    return tree_node_search(self->right, value);
  }
  return true;
}

bool tree_contains(const struct tree *self, int value) {
  return tree_node_search(self->root,value);
}

struct tree_node *add_node(struct tree_node *node, int value){
    if (node == NULL){
      struct tree_node *new= malloc(sizeof(struct tree_node));
      new->left = new->right = NULL;
      new->data = value;
      return new;
    }
    if (value < node->data){
      node->left = add_node(node->left, value);
    }
    else if (value > node->data){
      node->right = add_node(node->right, value);
    }
    return node;
}

bool tree_insert(struct tree *self, int value) {
  if(tree_contains(self,value)) return false;
  struct tree_node *curr = self->root;
  self->root = add_node(curr,value);
  return true;
}

struct tree_node *tree_remove_partial(struct tree_node *node, int value){
  if(node == NULL){
    return NULL;
  }
  if(value < node->data){
    node->left = tree_remove_partial(node->left, value);
    return node;
  }
  if(value > node->data){
    node->right = tree_remove_partial(node->right, value);
    return node;
  }
  return tree_destroy_partial(node);
}

bool tree_remove(struct tree *self, int value) {
  if((tree_empty(self))||(!tree_contains(self,value))){
    return false;
  }
  struct tree_node *node = self->root;
  self->root = tree_remove_partial(node,value);
  return true;
}

bool tree_empty(const struct tree *self) {
  return (self->root == NULL);
}

size_t tree_node_nb(const struct tree_node *node){
  if(node == NULL){
    return 0;
  }
  return (tree_node_nb(node->left)+1+tree_node_nb(node->right));
}

size_t tree_size(const struct tree *self) {
  return tree_node_nb(self->root);
}

size_t tree_node_height(const struct tree_node *node){
  size_t  sizeL = 0;
  size_t sizeR = 0;
  if(node->left != NULL){
    sizeL = tree_node_nb(node->left);
  }
  if(node->right != NULL){
    sizeR = tree_node_nb(node->right);
  }
  return (sizeL>=sizeR) ? (1+sizeL):(1+sizeR);
}

size_t tree_height(const struct tree *self) {
  if(tree_empty(self)) return 0;
  else return tree_node_height(self->root);
}

void pre_order_partial(struct tree_node *node, tree_func_t func, void *user_data){
  func(node->data,user_data);
  if(node->left != NULL){
    pre_order_partial(node->left,func,user_data);
  }
  if(node->right != NULL){
    pre_order_partial(node->right,func,user_data);
  }
}

void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data){
  if(tree_empty(self))return;
  else{
    pre_order_partial(self->root,func,user_data);
  }
}

void in_order_partial(struct tree_node *node, tree_func_t func, void *user_data){
  if(node->left != NULL){
    in_order_partial(node->left,func,user_data);
  }
  func(node->data,user_data);
  if(node->right != NULL){
    in_order_partial(node->right,func,user_data);
  }
}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
  if(tree_empty(self))return;
  else{
    in_order_partial(self->root,func,user_data);
  }
}

void post_order_partial(struct tree_node *node, tree_func_t func, void *user_data){
  if(node->left != NULL){
    post_order_partial(node->left,func,user_data);
  }
  if(node->right != NULL){
    post_order_partial(node->right,func,user_data);
  }
  func(node->data,user_data);
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
  if(tree_empty(self))return;
  else{
    post_order_partial(self->root,func,user_data);
  }
}
