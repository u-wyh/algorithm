#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
int val[MAXN];
bool root[MAXN];

int depval[MAXN];
int tot[MAXN];

int sz[MAXN];
int dep[MAXN];
int son[MAXN];
int mindep[MAXN];
int maxdep[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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

void dfs1(int u,int f){
    sz[u]=1;
    maxdep[u]=dep[u]=dep[f]+1;
    mindep[u]=n;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        mindep[u]=min(mindep[u],mindep[v]);
        maxdep[u]=max(maxdep[u],maxdep[v]);
        sz[u]+=sz[v];
        if(son[u]==0||sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
    if(head[u]==0){
        mindep[u]=dep[u];
    }
}

void effect(int u,int d){
    if(dep[u]>=d){
        return ;
    }
    tot[depval[dep[u]]]--;
    depval[dep[u]]^=val[u];
    tot[depval[dep[u]]]++;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        effect(v,d);
    }
}

void cancel(int u,int d){
    if(dep[u]>=d){
        return ;
    }
    tot[depval[dep[u]]]--;
    depval[dep[u]]^=val[u];
    tot[depval[dep[u]]]++;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        cancel(v,d);
    }
}

void dfs2(int u,int keep){
    // cout<<' '<<u<<' '<<keep<<endl;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,0);
        }        
    }
    if(son[u]!=0){
        dfs2(son[u],1);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            effect(v,mindep[u]+2);
        }
    }
    // for(int i=mindep[u]+2;i<=maxdep[u];i++){
    //     tot[depval[i]]--;
    //     depval[i]=0;
    //     tot[0]++;
    // }
    for(int i=(mindep[u]==maxdep[u])?1:0;i<=n;i++){
        if(tot[i]<=0){
            val[u]=i;
            break;
        }
    }
    tot[depval[dep[u]]]--;
    depval[dep[u]]^=val[u];
    tot[depval[dep[u]]]++;
    if(keep==0){
        cancel(u,mindep[u]+2);
    }
}

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        root[i]=0;
        son[i]=0;
    }
    for(int i=1;i<=n;i++){
        depval[i]=0;
        tot[i]=0;
    }
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        prepare();
        for(int i=1;i<=n;i++){
            int u;
            u=read();
            if(u==0){
                root[i]=true;
            }
            else{
                addedge(u,i);
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(root[i]){
                dfs1(i,0);
                dfs2(i,0);
                ans^=val[i];
            }
        }
        // cout<<ans<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<val[i]<<' ';
        // }
        // cout<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<": "<<mindep[i]<<' '<<maxdep[i]<<endl;
        // }
        // cout<<endl;
        if(ans){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}