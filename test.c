#include <stdio.h>

void p(int y){
    printf("%d\n",y);
}

 void p(int y,int u){
     p(y+u);
 }
int main(int argc, char *argv[])
{
    int y=0;
    void* p1 = &y;
    printf("%p\n", 1<<1);
    p(1);
    // p(1);
     p(1,2);
    if(NULL==0)printf("success\n");
}