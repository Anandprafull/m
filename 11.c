#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t l1,l2;

void* fun(void* p) {
    int i=*(int*)p;
    pthread_mutex_t *a=i?&l2:&l1, *b=i?&l1:&l2;

    pthread_mutex_lock(a);
    sleep(1);
    printf("T%d waiting\n",i);

    if(pthread_mutex_trylock(b))
        printf("T%d failed, releasing lock\n",i);
    else pthread_mutex_unlock(b);

    pthread_mutex_unlock(a);
    return NULL;
}

int main() {
    pthread_t t[2];
    int a=0,b=1;

    pthread_mutex_init(&l1,0);
    pthread_mutex_init(&l2,0);

    pthread_create(&t[0],0,fun,&a);
    pthread_create(&t[1],0,fun,&b);

    pthread_join(t[0],0);
    pthread_join(t[1],0);
}
