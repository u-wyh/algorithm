#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int nums[MAXN];
int sz[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

int ans;

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
        sz[u]+=sz[v];
    }
    if(head[u]==0){
        sz[u]=1;
    }
}

int dfs(int u){
    if(head[u]==0){
        return 1;
    }
    int ans=0;
    if(nums[u]==1){
        ans=INT_MAX;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            ans=min(ans,dfs(v));
        }
    }
    else{
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            ans+=dfs(v);
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=2;i<=n;i++){
        int u;
        u=read();
        addedge(u,i);
    }
    dfs1(1);
    printf("%d\n",sz[1]+1-dfs(1));
    return 0;
}