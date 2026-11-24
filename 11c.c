#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t a,b;

void* work(void* p) {
    int id=*(int*)p;
    pthread_mutex_t *x=id?&b:&a,*y=id?&a:&b;
    pthread_mutex_lock(x);
    sleep(1);
    if(pthread_mutex_trylock(y)==0) {
        pthread_mutex_unlock(y);
    }
    pthread_mutex_unlock(x);
    return NULL;
}
int main() {
    pthread_t t[2]; int id[]={0,1};
    pthread_mutex_init(&a,0);
    pthread_mutex_init(&b,0);
    for(int i=0;i<2;i++) pthread_create(&t[i],0,work,&id[i]);
    for(int i=0;i<2;i++) pthread_join(t[i],0);
    pthread_mutex_destroy(&a);
    pthread_mutex_destroy(&b);
}
