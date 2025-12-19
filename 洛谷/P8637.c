#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 10005

int father[Max],size[Max],stack[Max];

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
        size[i]=1;
    }
}

int find(int i){
    int size=0;
    while(i!=father[i]){
        stack[size++]=i;
        i=father[i];
    }
    while(size>0){
        father[stack[--size]]=i;
    }
    return i;
}

bool issameset(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(size[fx]>=size[fy]){
            size[fx]+=size[fy];
            father[fy]=fx;
        }else{
            size[fy]+=size[fx];
            father[fx]=fy;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    build(n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        un(i,nums[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(i==find(i)){
            ans+=size[i]-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

