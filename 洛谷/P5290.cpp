#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

priority_queue<int>pq[MAXN];

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

void merge(int x,int y){
    if(pq[x].size()<pq[y].size()){
        swap(pq[x],pq[y]);
    }
    vector<int>vec;
    while(!pq[y].empty()){
        vec.push_back(max(pq[y].top(),pq[x].top()));
        pq[y].pop();
        pq[x].pop();
    }
    for(int i=0;i<(int)vec.size();i++){
        int val=vec[i];
        pq[x].push(val);
    }
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        merge(u,v);
    }
    pq[u].push(val[u]);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa=read();
        addedge(fa,i);
    }
    dfs(1);
    long long ans=0;
    while(!pq[1].empty()){
        ans+=pq[1].top();
        pq[1].pop();
    }
    cout<<ans<<endl;
    return 0;
}