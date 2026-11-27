// https://www.luogu.com.cn/problem/P1111
// 题意：给 N 个村庄和 M 条双向公路，每条路在时刻 t 修好。只用已修好的路，求整张图最早何时连通，所有路修完仍不连通则输出 -1。
// 数据范围：1 ≤ N ≤ 1000，1 ≤ M,t ≤ 10^5，端点在 [1,N]。
// 算法标签：二分答案、并查集、排序

#include<bits/stdc++.h>
using namespace std;
#define Max 100005

typedef struct{
    int x,y,t;
}road;

int n,m;
road nums[100005];

int cmp(const road &a,const road &b){
    return a.t<b.t;
}

int father[Max],sz[Max],stack1[Max];

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
        sz[i]=1;
    }
}

int find(int i){
    int sz=0;
    while(i!=father[i]){
        stack1[sz++]=i;
        i=father[i];
    }
    while(sz>0){
        father[stack1[--sz]]=i;
    }
    return i;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>=sz[fy]){
            sz[fx]+=sz[fy];
            father[fy]=fx;
        }else{
            sz[fy]+=sz[fx];
            father[fx]=fy;
        }
    }
}

bool check(int x){
    build(n);
    for(int i=1;i<=m;i++){
        if(nums[i].t>x)
            break;
        un(nums[i].x,nums[i].y);
    }
    for(int i=1;i<=n;i++){
        if(sz[i]==n)
            return true;
    }
    return false;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].x>>nums[i].y>>nums[i].t;
    }
    sort(nums+1,nums+1+m,cmp);
    int l=0,r=100005,ans=-1,mid;
    while(l<=r){
        memset(father,0,sizeof(father));
        memset(stack1,0,sizeof(stack1));
        memset(sz,0,sizeof(sz));
        mid=(l+r)/2;
        if(check(m)){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    cout<<ans;
    return 0;
}
