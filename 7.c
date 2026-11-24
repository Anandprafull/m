#include <stdio.h>
#include <pthread.h>

int b=1000;
pthread_mutex_t m;

void* f(void* p){
    pthread_mutex_lock(&m);
    int x=*(int*)p;
    if(b+x>=0)b+=x;
    else puts("Insufficient");
    pthread_mutex_unlock(&m);
    return 0;
}

int main(){
    pthread_t t[5];
    int a[]={-200,100,-300,150,-400};
    pthread_mutex_init(&m,0);
    for(int i=0;i<5;i++)pthread_create(t+i,0,f,a+i);
    for(int i=0;i<5;i++)pthread_join(t[i],0);
    printf("Balance: %d",b);
}
