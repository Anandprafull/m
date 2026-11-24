#include <stdio.h>
#include <pthread.h>

int a[100],f=-1;
pthread_mutex_t m;

void* s(void* p){
    int n=*(int*)p;
    for(int i=n;i<n+25;i++)if(a[i]==50){
        pthread_mutex_lock(&m);
        f=i;
        pthread_mutex_unlock(&m);
    }
    return 0;
}

int main(){
    pthread_t t[4];int id[4];
    for(int i=0;i<100;i++)a[i]=i+1;
    pthread_mutex_init(&m,0);
    for(int i=0;i<4;i++)id[i]=i*25,pthread_create(t+i,0,s,id+i);
    for(int i=0;i<4;i++)pthread_join(t[i],0);
    printf("Number: 50\nIndex: %d",f);
}
