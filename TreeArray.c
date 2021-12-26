#include "TreeArray.h"
int _lowbits(int x)
{
    return x&(-x);
}

void delete_tree_array(struct TreeArray_t* tA){
    free(tA->tree_data_ptr);
}
void init_tree_array(struct TreeArray_t* tA,int* data,int length){
    tA->length = length;
    tA->tree_data_ptr = (int *)malloc(length*sizeof(int));
    for(int i=0;i<length;i++){
        tA->tree_data_ptr[i] = data[i];
        for(int k = i;k>i+1-_lowbits(i+1);k-=_lowbits(k)){
            tA->tree_data_ptr[i] += tA->tree_data_ptr[k-1];
        }
    }
}

void _update_tree_array(struct TreeArray_t* tA,int index,int delta){
    int k = index+1;
    for(int i=k;k<=tA->length;k+=_lowbits(k)){
        tA->tree_data_ptr[k-1]+=delta;
    }
}

int  _get_sum(struct TreeArray_t* tA,int end){
    int k = end+1;
    int _result = 0;
    for(;k;k-=_lowbits(k)){
        _result+=tA->tree_data_ptr[k-1];
    }
    return _result;
}

int get_sum(struct TreeArray_t* tA,int start,int end){

    if(_check_range_in_tree_array(tA,start)<0||_check_range_in_tree_array(tA,end)<0)return -1;
    return _get_sum(tA,end) - _get_sum(tA,start);
}

int _check_range_in_tree_array(struct TreeArray_t* tA,int x){
    return (x>=0&&x<tA->length)?1:-1;
}

void set_tree_array_in_index(struct TreeArray_t* tA,int index, int value){
    if(_check_range_in_tree_array(tA,index)<0)return;
    _update_tree_array(tA,index,value-tA->tree_data_ptr[index]);
}

void print_tree(struct TreeArray_t* tA){
    printf("[");
    for(int i=0;i<tA->length;i++){
        printf(" %d",tA->tree_data_ptr[i]);
    }
    printf("]\n");
}
// int main(int argc,char* argv[]){
//     printf("start--------------------------\n");
//     int array[11] = {2,3,4,5,1,6,7,8,3,5,7};
//     //printf("%d\n",array[0]);
//     struct TreeArray_t tree;
//     init_tree_array(&tree,array,11);
//     print_tree(&tree);
//     printf("sum between 3 and 9 is %d",get_sum(&tree,3,9));
//     set_tree_array_in_index(&tree,3,11);
//     printf("sum between 4 and 9 is %d",get_sum(&tree,2,9));
//     print_tree(&tree);
//     delete_tree_array(&tree);
// }