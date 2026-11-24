#include <stdio.h>
#include <pthread.h>

pthread_mutex_t l[2];
pthread_barrier_t bar;

void* fun(void* p) {
    int i=*(int*)p;
    pthread_mutex_lock(&l[i]);
    pthread_barrier_wait(&bar);
    printf("T%d waiting\n",i);

    if(pthread_mutex_trylock(&l[1-i]))
        printf("T%d failed, releasing\n",i);
    else pthread_mutex_unlock(&l[1-i]);

    pthread_mutex_unlock(&l[i]);
    return NULL;
}

int main() {
    pthread_t t[2];
    int a[2]={0,1};

    pthread_barrier_init(&bar,0,2);
    for(int i=0;i<2;i++)
        pthread_mutex_init(&l[i],0);

    for(int i=0;i<2;i++)
        pthread_create(&t[i],0,fun,&a[i]);

    for(int i=0;i<2;i++)
        pthread_join(t[i],0);
}
