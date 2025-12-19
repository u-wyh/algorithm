#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int son[MAXN];
int dep[MAXN];
int need[MAXN];

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

void dfs(int u,int f){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        son[u]++;
        dfs(v,u);
    }
}

void dfs1(int u,int fa){
    if(!son[u]){
        return ;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            if(need[v]<0){
                need[u]+=need[v];
            }
        }
    }
    need[u]-=son[u];
}

bool check(int k){
    for(int i=1;i<=n;i++){
        if(son[i]){
            need[i]=k;
        }
    }
    dfs1(1,0);
    return need[1]>=0;
}

int main()
{
    n=read();
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}