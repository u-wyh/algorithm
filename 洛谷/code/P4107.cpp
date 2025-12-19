#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
int ans;
int son[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int nums[MAXN];
int cntu;

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

bool cmp(int a,int b){
    return (son[a]+val[a])<(son[b]+val[b]);
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    cntu=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        nums[++cntu]=v;
    }
    sort(nums+1,nums+cntu+1,cmp);
    for(int i=1;i<=cntu;i++){
        int v=nums[i];
        if((son[u]+son[v]-1+val[u]+val[v])<=m){
            son[u]+=son[v]-1;
            val[u]+=val[v];
            ans++;
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        son[i]=read();
        for(int k=1;k<=son[i];k++){
            int u=read()+1;
            addedge(i,u);
        }
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}