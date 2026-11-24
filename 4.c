#include <stdio.h>
#include <pthread.h>

int a[]={38,27,43,3,9,82,10,29,42,2,1,8,5,6,7,4};

void* s(void* p){
    int l=((int*)p)[0],r=((int*)p)[1],m=(l+r)/2,t[16],i=l,j=m+1,k=l;
    if(l>=r)return 0;
    int x[]={l,m},y[]={m+1,r};
    pthread_t u,v;
    pthread_create(&u,0,s,x);pthread_create(&v,0,s,y);
    pthread_join(u,0);pthread_join(v,0);
    while(i<=m&&j<=r)t[k++]=a[i]<a[j]?a[i++]:a[j++];
    while(i<=m)t[k++]=a[i++];
    while(j<=r)t[k++]=a[j++];
    for(i=l;i<=r;i++)a[i]=t[i];
    return 0;
}

int main(){
    int d[]={0,15};pthread_t t;
    pthread_create(&t,0,s,d);pthread_join(t,0);
    for(int i=0;i<16;i++)printf("%d ",a[i]);
}
