#ifndef  __TREE_ARRAY__
#define  __TREE_ARRAY__

#include<stdio.h>
#include<malloc.h>
#include<math.h>
struct TreeArray_t{
    int* tree_data_ptr;
    int length;
};


void init_tree_array(struct TreeArray_t* tA,int* data,int length);
void _update_tree_array(struct TreeArray_t* tA,int index,int delta);
int  _get_sum(struct TreeArray_t* tA,int end);
int get_sum(struct TreeArray_t* tA,int start,int end);
int _check_range_in_tree_array(struct TreeArray_t* tA,int x);
int _lowbits(int x);
void delete_tree_array(struct TreeArray_t* tA);
void set_tree_array_in_index(struct TreeArray_t* tA,int index, int value);
void print_tree(struct TreeArray_t* tA);

#endif