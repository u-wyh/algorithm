#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n;
int val[MAXN];
int f[MAXN];
bool leaf[MAXN];//是否是叶节点
int son[MAXN];
int flag;

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

void dfs1(int u,int fa){
    int tot=0;
    son[u]=0;
    f[u]=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        tot++;
        dfs1(v,u);
        son[u]+=son[v];
        f[u]+=f[v];
    }
    if(tot==0){
        leaf[u]=true;
        son[u]=1;
    }
    if(tot==1&&u==1){
        flag=1;
    }
    f[u]+=val[u]*son[u];
}

void dfs2(int u,int fa){
    if(fa!=0)
        f[u]=f[fa]-son[u]*val[fa]-val[u]*son[u]+val[u]*son[1]-(leaf[u]?val[u]:0);
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    int maxans=LLONG_MIN;
    int sum=0;
    for(int i=1;i<=n;i++){
        val[i]=read();
        sum+=val[i];
        maxans=max(maxans,val[i]);
    }
    dfs1(1,0);
    dfs2(1,0);
    double ans=LLONG_MIN;
    if(flag==1&&son[1]==1){
        ans=max(sum,(sum+maxans)/2);
        printf("%.4lf",ans);
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(leaf[i]){
            ans=max(ans,1.0*f[i]/(son[1]-1+flag));
        }
        else{
            ans=max(ans,1.0*f[i]/son[1]);
        }
    }
    printf("%.4lf",ans);
    return 0;
}
