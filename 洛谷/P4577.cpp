#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;

int val[MAXN];

multiset<int>f[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

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

void merge(int u,int v){
    if(f[u].size()<f[v].size()){
        swap(f[u],f[v]);
    }
    for(int x:f[v]){
        f[u].insert(x);
    }
}

// multiset<int>f[MAXN];
void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        merge(u,v);
    }
    f[u].insert(val[u]);
    auto it=f[u].lower_bound(val[u]);
    if(it!=f[u].begin()){
        f[u].erase(prev(it));
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int u=read();
        addedge(u,i);
    }
    dfs(1);
    cout<<(f[1].size());
    return 0;
}