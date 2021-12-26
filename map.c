#include "map.h"
struct string_t{
    char* value;
    int length;
};
void rehash(struct map_t* map,int _new_limit,struct entity_t* _map_data_ptr);
void _rehash(struct map_t* map,int _new_limit,struct entity_t* _map_data_ptr,struct entity_t* entity);
void resize_map(struct map_t* map);
void _delete(struct entity_t* entity){
    if(entity->next)_delete(entity->next);
    free(entity);
}
void dfs_delete(struct entity_t* entity){
    _delete(entity);
}
void init_map2(struct map_t* map,int(*hash)(void*),int limit)
{
    map->limit = limit;
    map->hash = hash;
    map->size = 0;
    map->factor = DEFAULT_FACTOR;
    map->map_data_ptr = (struct entity_t*)malloc(sizeof(struct entity_t)*limit);
    memset(map->map_data_ptr,0,limit*sizeof(struct entity_t));
}
void init_map(struct map_t* map,int(*hash)(void*)){
    init_map2(map,hash,DEFAULT_LIMIT);
}

void put_in_map(struct map_t* map,void* key,void * object){
    struct entity_t* entity= (struct entity_t*)malloc(sizeof(struct entity_t));
    entity->key = key;
    entity->value = object;
    entity->next = NULL;
    _rehash(map,map->limit,map->map_data_ptr,entity);
    map->size++;
    if(map->size>=(int)(map->limit*map->factor))resize_map(map);
}

void* get_from_map(struct map_t* map,void * key,int length)
{
    int _hash = map->hash(key);
    int _index = _hash&(map->limit-1);
    struct entity_t* entity = map->map_data_ptr+_index;
    while(entity){
        if(!memcmp(entity->key,key,length))return entity->value;
        entity = entity->next;
    }
    return NULL;
}

void resize_map(struct map_t* map){
    int _new_limit = map->limit<<1;
    struct entity_t* _new_data_map_ptr = (struct entity_t*)malloc(sizeof(struct entity_t)*_new_limit);
    memset(_new_data_map_ptr,0,_new_limit*sizeof(struct entity_t));
    rehash(map,_new_limit,_new_data_map_ptr);
    free(map->map_data_ptr);
    map->map_data_ptr = _new_data_map_ptr;
    map->limit = _new_limit;
}

void rehash(struct map_t* map,int _new_limit,struct entity_t* _map_data_ptr){
    struct entity_t* entity;
    for(int i=0;i<map->limit;i++){
        entity = map->map_data_ptr+i;
        while(entity&&entity->key)
        {
            struct entity_t* _entity = entity->next;
            entity->next = NULL;
            _rehash(map,_new_limit,_map_data_ptr,entity);
           
            entity = _entity;
        }
    }
}

void _rehash(struct map_t* map,int _new_limit,struct entity_t* _map_data_ptr,struct entity_t* entity){
    int hash = map->hash(entity->key);
    int _new_index = hash&(_new_limit-1);
    struct entity_t* _entity = _map_data_ptr+_new_index;
    if(_entity->key==NULL)
    {
        *_entity = *entity;
    }else {
        while(_entity->next)_entity =_entity->next;
        _entity->next = entity;
    }
}
int size_of_map(struct map_t* map)
{
    if(map==NULL)return 0;
    return map->size;
}

int is_map_empty(struct map_t* map)
{
    return map==NULL||map->size==0;
}
void delete_map(struct map_t* map){
    for(int i=0;i<map->limit;i++){
        struct entity_t* entity = map->map_data_ptr+i;
       if(entity->next)dfs_delete(entity->next);
    }
    free(map->map_data_ptr);
}
void print_map(struct map_t* map,int length){
    for(int i=0;i<map->limit;i++){
        struct entity_t* entity = map->map_data_ptr+i;
        if(entity->key){
            printf("[");
            while(entity){
                struct string_t* string = (struct string_t*) entity->key;
                printf(" %s",string->value);
                entity = entity->next;
            }
            printf("]\n");
        }
    }
}

int hash(void* arg){
    struct string_t* string = (struct sting_t*)arg;
    int result = 0;
    for(int i=0;i<string->length;i++){
        result+=string->value[i];
    }
    return result;
}
int main(int argc,char* argv[]){
    printf("start------------------\n");
    struct map_t map;
    init_map(&map,hash);
    struct string_t arg1 = {"liming",6};
    int argv1 = 22;
    struct string_t arg2 = {"p",1};
    int argv2 = 22;
    struct string_t arg3 = {"w",1};
    int argv3 = 22;
    struct string_t arg4 = {"x",1};
    int argv4 = 22;
    struct string_t arg5 = {"y",1};
    int argv5 = 22;
    struct string_t arg6 = {"A",1};
    int argv6 = 22;
    put_in_map(&map,&arg1,&argv1);
    put_in_map(&map,&arg2,&argv2);
    put_in_map(&map,&arg3,&argv3);
    put_in_map(&map,&arg4,&argv4);
    put_in_map(&map,&arg5,&argv5);
    put_in_map(&map,&arg6,&argv6);
    print_map(&map,sizeof(struct string_t));
    printf("liming is %d\n",(int*)get_from_map(&map,&arg1,sizeof(struct string_t)));
    delete_map(&map);
    printf("finish-----------------\n");
}