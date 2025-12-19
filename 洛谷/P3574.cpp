#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
int arr[MAXN];
int sz[MAXN];
int f[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];

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
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

void dfs1(int u,int fa){
    int ans=INT_MAX;
    int cnt=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        ans=min(ans,f[v]+(sz[u]-sz[v]-1)*2);
        cnt++;
    }
    if(ans==INT_MAX)
        f[u]=arr[u];
    else
        f[u]=max(ans+(cnt==1?2:0),arr[u]);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    dfs(1,0);
    dfs1(1,0);
//    for(int i=1;i<=n;i++){
//        cout<<i<<": "<<f[i]<<endl;
//    }
    cout<<f[1]<<endl;
    return 0;
}
