#include <stdio.h>
#include <pthread.h>
int a[3][3]={{1,2,3},{4,5,6},{7,8,9}},
b[3][3]={{9,8,7},{6,5,4},{3,2,1}},c[3][3];

void* add(void* x) {
    int i=*(int*)x;
    for(int j=0;j<3;j++) c[i][j]=a[i][j]+b[i][j];
    return NULL;
}
int main() {
    pthread_t t[3]; int id[3];
    for(int i=0;i<3;i++) {
        id[i]=i; pthread_create(&t[i],0,add,&id[i]);
    }
    for(int i=0;i<3;i++) pthread_join(t[i],0);
    for(int i=0;i<3;i++)
        printf("%d %d %d\n",c[i][0],c[i][1],c[i][2]);
}
