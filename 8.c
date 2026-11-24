#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int n=0;
pthread_mutex_t m;
pthread_cond_t c;

void* f(void* x) {
    int p=*(int*)x;
    while(1) {
        pthread_mutex_lock(&m);
        while(p?n==0:n==10) pthread_cond_wait(&c,&m);
        printf("%s %d\n",p?"Consumed":"Produced",p?--n:++n);
        pthread_cond_broadcast(&c);
        pthread_mutex_unlock(&m);
        sleep(1);
    }
}

int main() {
    pthread_t a,b;
    int x=0,y=1;
    pthread_mutex_init(&m,0);
    pthread_cond_init(&c,0);
    pthread_create(&a,0,f,&x);
    pthread_create(&b,0,f,&y);
    pthread_join(a,0);
    pthread_join(b,0);
}
