#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,k;

long long val[MAXN];
long long sum[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt = 1;

int top[MAXN];
int son[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
        if(son[u]==0||sum[son[u]]<sum[v]){
            son[u]=v;
        }
    }
    sum[u]=val[u]+sum[son[u]];
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        if(to[i]!=son[u]){
            dfs2(to[i],to[i]);
        }
    }
}

bool cmp(long long a,long long b){
    return a>b;
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
    }
    dfs1(1);
    dfs2(1,1);
    vector<long long>vec;
    for(int u=1;u<=n;u++){
        if(top[u]==u){
            vec.push_back(sum[u]);
        }
    }
    sort(vec.begin(),vec.end(),cmp);
    if((int)vec.size()<k){
        k=(int)vec.size();
    }
    long long ans=0;
    for(int i=0;i<k;i++){
        ans+=vec[i];
    }
    cout<<ans<<endl;
    return 0;
}