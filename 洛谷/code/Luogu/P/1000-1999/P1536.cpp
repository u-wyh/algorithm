#include<bits/stdc++.h>
using namespace std;
#define Max 1005

int father[Max],size[Max],stac[Max];

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
        size[i]=1;
    }
}

int find(int i){
    int size=0;
    while(i!=father[i]){
        stac[size++]=i;
        i=father[i];
    }
    while(size>0){
        father[stac[--size]]=i;
    }
    return i;
}

bool issameset(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y){
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
    int n,m;
    while(scanf("%d",&n)==1&&n!=0){
        build(n);
        cin>>m;
        int a,b;
        for(int i=1;i<=m;i++){
            cin>>a>>b;
            un(a,b);
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(find(i)==i){
                ans++;
            }
        }
        printf("%d\n",ans-1);
    }
    return 0;
}

