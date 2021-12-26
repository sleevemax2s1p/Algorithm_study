#ifndef __HASH__
#define __HASH__

#include<stdio.h>
#include<malloc.h>
#include<memory.h>
float DEFAULT_FACTOR = 0.75;
int DEFAULT_LIMIT = 8;
struct entity_t;
struct map_t
{
    int(*hash)(void* object);
    int limit;
    int size;
    float factor;
    struct entity_t* map_data_ptr;
};

struct entity_t{
    void* key;
    void* value;
    struct entity_t* next;
};
void init_map(struct map_t* map,int(*hash)(void*));

void init_map2(struct map_t* map,int(*hash)(void*),int limit);

void put_in_map(struct map_t* map,void* key,void * object);

void* get_from_map(struct map_t* map,void *,int length);

void delete_map(struct map_t* map);

int size_of_map(struct map_t* map);

int is_map_empty(struct map_t* map);


#endif