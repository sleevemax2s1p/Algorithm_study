#ifndef __HEAP__
#define __HEAP__

#include<stdio.h>
#include<malloc.h>
#include<memory.h>
#define MAX_HEAP 1;
#define MIN_HEAP -1;
#define DEFAULT_SIZE 8;

struct heap_t{
    int (*comparator)(void* arg,void* arg1);
    int type;
    void** heap_data_ptr;
    int data_length;
    int size;
    int limit;
};

void init_heap(struct heap_t* hp,int (*comparator)(void* arg,void* arg1),int type,int data_length);
int _up_heap(struct heap_t* hp,int index);
void up_heap(struct heap_t* hp,int index);
int put_heap(struct heap_t* hp,void *value);
void* poll_heap(struct heap_t* hp);
int _sink_heap(struct heap_t* hp,int index);
void sink_heap(struct heap_t* hp,int index);
void _swap_heap(struct heap_t* hp,int start,int end);
void resize_heap(struct heap_t* hp);

void* _get_index_heap(struct heap_t* hp,int index);

int _check_range_in_heap(struct heap_t* hp,int index);
void delete_heap(struct heap_t* hp);
#endif