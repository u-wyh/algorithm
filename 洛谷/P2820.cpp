#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

//int fa[MAXN],sz[MAXN];//建立连通关系的并查集
int n,k;
int fa1[MAXN],cnt[MAXN];
struct node{
    int st,en,cost;
}edge[10005];

void build(){
    for(int i=1;i<=n;i++){
        //fa[i]=i;
        fa1[i]=i;
        //sz[i]=1;
        cnt[i]=1;
    }
}

//int find(int i){
//    if (i != fa[i]){
//        fa[i] = find(fa[i]);
//    }
//    return fa[i];
//}
//
//void un(int x,int y){
//    int fx=find(x);
//    int fy=find(y);
//    if(fx!=fy){
//        sz[fx]+=sz[fy];
//        fa[fy]=fx;
//    }
//}

int find1(int i){
    if (i != fa1[i]){
        fa1[i] = find1(fa1[i]);
    }
    return fa1[i];
}

void un1(int x,int y){
    int fx=find1(x);
    int fy=find1(y);
    if(fx!=fy){
        cnt[fx]+=cnt[fy];
        fa1[fy]=fx;
    }
}

bool cmp(node a,node b){
    return a.cost<b.cost;
}

int main()
{
    cin>>n>>k;
    build();
    int sum=0;
    for(int i=1;i<=k;i++){
        cin>>edge[i].st>>edge[i].en>>edge[i].cost;
        //un(edge[i].st,edge[i].en);
        sum+=edge[i].cost;
    }
    sort(edge+1,edge+k+1,cmp);
    int ans=0;
    for(int i=1;i<=k;i++){
        int fx=find1(edge[i].st);
        int fy=find1(edge[i].en);
        if(fx!=fy){
            un1(fx,fy);
            ans+=edge[i].cost;
        }
    }
    cout<<(sum-ans);
    return 0;
}
