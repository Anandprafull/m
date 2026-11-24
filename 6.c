#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[100],t[100];

void s(int l,int r){
    if(l>=r)return;
    int m=(l+r)/2,i=l,j=m+1,k=l;
    s(l,m);s(m+1,r);
    while(i<=m&&j<=r)t[k++]=a[i]<a[j]?a[i++]:a[j++];
    while(i<=m)t[k++]=a[i++];
    while(j<=r)t[k++]=a[j++];
    for(i=l;i<=r;i++)a[i]=t[i];
}

void* f(void* p){
    int i=*(int*)p;
    s(i*25,i*25+24);
    return NULL;
}

int main(){
    pthread_t t1[4];int id[4];
    for(int i=0;i<100;i++)a[i]=rand()%1000;
    for(int i=0;i<4;i++)id[i]=i,pthread_create(t1+i,0,f,id+i);
    for(int i=0;i<4;i++)pthread_join(t1[i],0);
    s(0,99);
    for(int i=0;i<100;i++)printf("%d ",a[i]);
}

