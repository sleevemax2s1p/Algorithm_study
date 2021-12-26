#include"KmpMarch.h"
void cal_next(char* data,int* next,int length){
    int k=-1;
    next[0] = -1;
    for(int i = 1;i<length;i++){
        while(k>-1&&data[i]!=data[k+1]){
            k = next[k];
        }
        if(data[i]==data[k+1]){
            k++;
        }
        next[i] = k;
    }
}
int KmpSearch(char* array,char* march){
    int length = strlen(march);
    int length2 = strlen(array);
    int* _next = (int *)malloc(length*sizeof(int));
    cal_next(march,_next,length);
    int k = -1;
    for(int i = 0;i<length2;i++){
        while(k>-1&&array[i]!=march[k+1])
        {
            k = _next[k];
        }
        if(array[i] == march[k+1])
        {
            k++;
        }
        if(k==length-1)
        {
            free(_next);
            return i-length+1;
        }
    }
    free(_next);
    return -1;

}
// int main(int argc,char* argv[]){
//     printf("start march---------------------------\n");
//     char* _array = "ABABABABABCABD";
//     char* _march = "ABC";
//     printf("march position in %d\n",KmpSearch(_array,_march)); 
// }