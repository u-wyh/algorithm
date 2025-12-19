#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e4+5;

int n,q;

struct QUERY{
    int t,id;
};
QUERY query[MAXM];
int ans[MAXM];

struct node{
    int t,pos;
};
struct compare{
    bool operator()(node a,node b){
        return a.t>b.t;
    }
};
priority_queue<node,vector<node>,compare>heap;

int fa[MAXN];
int f[MAXN];
int val[MAXN];
int pass[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(QUERY a,QUERY b){
    return a.t<b.t;
}

signed main()
{
    n=read(),q=read();
    for(int i=2;i<=n;i++){
        f[i]=read();
        val[i]=read();
        int limit=read();
        pass[f[i]]-=limit;
        pass[i]+=limit;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=q;i++){
        query[i].t=read();
        query[i].id=i;
    }
    sort(query+1,query+q+1,cmp);
    for(int i=2;i<=n;i++){
        if(pass[i]>0){
            heap.push({val[i]/pass[i],i});
        }
    }
    int lt=1;
    while(!heap.empty()&&lt<=q){
        node u=heap.top();
        heap.pop();
        while(lt<=q&&query[lt].t<=u.t){
            ans[query[lt].id]=val[1]-pass[1]*query[lt].t;
            lt++;
        }
        if(u.pos!=find(u.pos)){
            continue;
        }
        int fx=find(f[u.pos]);
        val[fx]+=val[u.pos];
        pass[fx]+=pass[u.pos];
        fa[u.pos]=fx;
        if(pass[fx]>0){
            heap.push({val[fx]/pass[fx],fx});
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}