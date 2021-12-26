#include"Heap.h"
void init_heap(struct heap_t* hp,int (*comparator)(void* arg,void* arg1),int type,int data_length){
    hp->comparator = comparator;
    hp->type = type;
    hp->data_length = data_length;
    hp->limit = 8;
    hp->heap_data_ptr = (void**)malloc(hp->limit*sizeof(void*));
}
int _up_heap(struct heap_t* hp,int index){
    if(index==0)return 0;
    void* _index = _get_index_heap(hp,index);
    void* _parent = _get_index_heap(hp,(index-1)>>1);
    if((hp->type*hp->comparator(_index,_parent))>0){
        _swap_heap(hp,index,(index-1)>>1);
        return 1;
    }
    return 0;
}
void up_heap(struct heap_t* hp,int index){
    while(_up_heap(hp,index)){
        index = (index-1)>>1;
        printf("%d\n",index);
    }
}
int put_heap(struct heap_t* hp,void *value){
    hp->heap_data_ptr[hp->size++] = value; 
    up_heap(hp,hp->size-1);
    if(hp->limit == hp->size)resize_heap(hp);
    return hp->size;
}
void* poll_heap(struct heap_t* hp){
    if(hp->size==0)return NULL;
    void* result = hp->heap_data_ptr[0];
    hp->heap_data_ptr[0] = hp->heap_data_ptr[--hp->size];
    sink_heap(hp,0);
    return result;
}
int _sink_heap(struct heap_t* hp,int index){
    int k = index;
    int _son = (k+1)<<1;
    void *_self = _get_index_heap(hp,index);
    void *_son_r = _get_index_heap(hp,_son);
    void *_son_l = _get_index_heap(hp,_son-1);
    int swap = 0;
    void* _swap_ptr;
    if(_son_l==NULL&&_son_r==NULL)return 0;
    else if(_son_r==NULL){
        swap = _son-1;
        _swap_ptr = _son_l;
    }else 
    {
        if((hp->type*hp->comparator(_son_l,_son_r))>0){
            swap = _son-1;
            _swap_ptr = _son_l;
        }else{
            swap = _son;
            _swap_ptr = _son_r;
        }
    }
    if((hp->type*hp->comparator(_self,_swap_ptr))<0){
            _swap_heap(hp,k,swap);
            k = swap;
        }
    return k-index;
}
void sink_heap(struct heap_t* hp,int index){
    int k = index;
    while(k=_sink_heap(hp,k));
}
void _swap_heap(struct heap_t* hp,int start,int end){
    void* mid = hp->heap_data_ptr[start];
    hp->heap_data_ptr[start] = hp->heap_data_ptr[end];
    hp->heap_data_ptr[end] = mid;
}
void resize_heap(struct heap_t* hp){
    int _new_limit = hp->limit<<1;
    void** _new_heap_data_ptr = (void**)malloc(_new_limit*sizeof(void*));
    memcpy(_new_heap_data_ptr,hp->heap_data_ptr,hp->size*sizeof(void*));
    hp->limit = _new_limit;
    free(hp->heap_data_ptr);
    hp->heap_data_ptr = _new_heap_data_ptr;
}

void* _get_index_heap(struct heap_t* hp,int index){
    if(index>=hp->size)return NULL;
    return hp->heap_data_ptr[index];
}

int _check_range_in_heap(struct heap_t* hp,int index){
    return (index>=0&&index<hp->size)?1:-1;
}

struct Entity{
    char* name;
    int age;
};
int compare(void* arg1,void* arg2){
   
   struct Entity* entity1 = (struct Entity*)arg1;
   struct Entity* entity2 = (struct Entity*)arg2;
   //printf("compare\n");
   int result = (entity1->age)-(entity2->age);
   return result;
}
void delete_heap(struct heap_t* hp){
    free(hp->heap_data_ptr);
}
int main(int argc,char* argv[]){
    printf("start----------------------------\n");
    struct heap_t heap;
    init_heap(&heap,compare,-1,sizeof(struct Entity));
    struct Entity entity1 = {"liming",23};
    printf("name:%s",entity1.name);
    struct Entity entity2 = {"wangsan",19};
    struct Entity entity3 = {"tongce",17};
    struct Entity entity4 = {"java",10};
    struct Entity entity5 = {"cpp",20};
    struct Entity entity6 = {"py",15};
    struct Entity entity7 = {"py",14};
    struct Entity entity8 = {"py",12};
    struct Entity entity9 = {"py1",12};
    put_heap(&heap,(void*)&entity1);
    put_heap(&heap,(void*)&entity2);
    put_heap(&heap,(void*)&entity3);
    put_heap(&heap,(void*)&entity4);
    put_heap(&heap,(void*)&entity5);
    put_heap(&heap,(void*)&entity6);
    // put_heap(&heap,(void*)&entity7);
    // put_heap(&heap,(void*)&entity8);
    // put_heap(&heap,(void*)&entity9);
    struct Entity* entity;
    for(int i=0;heap.size>0;i++){
        entity = (struct Entity*)poll_heap(&heap);
        printf("name:%s  age:%d\n",entity->name,entity->age);
    }
    printf("finish-----------%d\n",heap.limit);
    delete_heap(&heap);
}