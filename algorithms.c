#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
  return self-> data[index];
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
  for(size_t i = 0; i < self->size; ++i){
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


void array_heap_sort(struct array *self) {
}

bool array_is_heap(const struct array *self) {
  return false;
}

void array_heap_add(struct array *self, int value) {
}

int array_heap_top(const struct array *self) {
  return 42;
}

void array_heap_remove_top(struct array *self) {
}

/*
 * list
 */

void list_create(struct list *self) {
  self -> first =  NULL;
}


void list_copy(struct list *self,const int *other, size_t size){
  for(size_t i = 0; i<size;++i){
    struct list_node *new = malloc(sizeof(struct list_node));
    new->data = other[i];
    if(self->first == NULL){
      self->first = new;
      self->first->next = NULL;
    }
    else{
      new->next = self->first;
      self->first = new;
    }
  }
}

void list_create_from(struct list *self, const int *other, size_t size) {
  self -> first =  NULL;
  list_copy(self, other, size);
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
  if(self == NULL)return true;
  if(self->first == NULL) return true;
  return false;
}

size_t list_size(const struct list *self) {
  if(list_empty(self))return 0;
  struct list_node *curr = self->first;
  size_t size = 0;
  while (curr != NULL) {
    ++size;
    curr = curr->next;
  }
  return size;
}

bool list_equals(const struct list *self, const int *data, size_t size){
  if(!list_empty(self)){
    struct list_node *curr = self->first;
    size_t pos = 0;
    while((pos<size)&&(curr->next!=NULL)){
      if(curr->data != data[pos])return false;
      curr = curr->next;
      ++pos;
    }
  }
  return true;
}

void list_push_front(struct list *self, int value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->data = value;
  if(self->first != NULL){
    new->next = self->first;
  }
  self->first = new;
}

void list_pop_front(struct list *self) {
  struct list_node *curr = self->first;
  self->first =self->first->next;
  free(curr);
}

void list_push_back(struct list *self, int value) {
}

void list_pop_back(struct list *self) {
}


void list_insert(struct list *self, int value, size_t index) {
}


void list_remove(struct list *self, size_t index) {
}

int list_get(const struct list *self, size_t index) {
  struct list_node *curr = malloc(sizeof(struct list_node));
  curr = self->first;
  size_t pos = 0;
  while(pos<index){
    curr = curr->next;
    ++pos;
  }
  return curr->data;
}

void list_set(struct list *self, size_t index, int value) {
}

size_t list_search(const struct list *self, int value) {
  return -1;
}

bool list_is_sorted(const struct list *self) {
  return false;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
}

void list_merge_sort(struct list *self) {
}


/*
 * tree
 */

void tree_create(struct tree *self) {
}


void tree_destroy(struct tree *self) {
}


bool tree_contains(const struct tree *self, int value) {
  return false;
}


bool tree_insert(struct tree *self, int value) {
  return false;
}


bool tree_remove(struct tree *self, int value) {
  return false;
}

bool tree_empty(const struct tree *self) {
  return true;
}


size_t tree_size(const struct tree *self) {
  return -1;
}


size_t tree_height(const struct tree *self) {
  return -1;
}


void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
}
