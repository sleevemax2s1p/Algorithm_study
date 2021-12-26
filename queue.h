#ifndef __QUEUE__
#define __QUEUE__
struct queue_t{
    int limit;
    int size;
    void** queue_data_ptr;
};

struct Entity{

};
void init_queue(struct queue_t* queue);
int size_of_queue(struct queue_t* queue);
void* get_in_queue(struct queue_t* queue,int index);
void set_in_queue(struct queue_t* queue,int index,void* value);
int isEmpty_queue(struct queue_t* queue);

#endif