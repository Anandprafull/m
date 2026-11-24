#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 10
#define T 4
int tasks[N];

void* work(void* p) {
    int id=*(int*)p;
    for(int i=id;i<N;i+=T) {
        printf("Thread %d: Task %d\n",id,tasks[i]);
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t t[T]; int id[T];
    for(int i=0;i<N;i++) tasks[i]=i+1;
    for(int i=0;i<T;i++) {
        id[i]=i; pthread_create(&t[i],0,work,&id[i]);
    }
    for(int i=0;i<T;i++) pthread_join(t[i],0);
}
