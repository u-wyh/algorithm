#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 2005;

int n;
int f[MAXN][MAXM];
int val[MAXN];
bool vis[MAXN];
int tot=1;
int ans=0;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

void addedge(int u,int v,int w){
    //cout<<cnt<<": "<<u<<' '<<v<<' '<<w<<endl;
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void prepare(int fa){
    int u,v;
    scanf("%d %d",&u,&v);
    addedge(fa,tot+1,u*2);
    tot++;
    val[tot]=v;
    vis[tot]=(v!=0)?1:0;
    fa=tot;
    if(v==0){
        prepare(fa);
        prepare(fa);
    }
}

void dfs(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        dfs(v);
        val[u]+=val[v];
    }
    if(u==1){
        int v=2;//1的下一个节点一定是2
        int w=weight[head[u]];
        for(int i=val[v];i>=0;i--){
            if(f[2][i]+w<=n){
                ans=i;
                return ;
            }
        }
    }
    else if(vis[u]){
        //叶节点
        for(int i=0;i<=val[u];i++){
            f[u][i]=5*i;
        }
    }
    else{
        int v1=to[head[u]];
        int w1=weight[head[u]];
        int v2=to[Next[head[u]]];
        int w2=weight[Next[head[u]]];
        for(int i=0;i<=val[u];i++){
            for(int j=0,k=i;j<=i;j++,k--){
                if(j>val[v1]||k>val[v2]){
                    continue;
                }
                if(j!=0&&k!=0)
                    f[u][i]=min(f[u][i],f[v1][j]+f[v2][k]+w1+w2);
                else if(j!=0)
                    f[u][i]=min(f[u][i],f[v1][j]+w1);
                else if(k!=0)
                    f[u][i]=min(f[u][i],f[v2][k]+w2);
            }
        }
    }
}

int main()
{
    scanf("%d",&n);
    n--;
    int u,v;
    scanf("%d %d",&u,&v);
    addedge(tot,tot+1,u*2);
    tot++;
    val[tot]=v;
    vis[tot]=(v!=0)?1:0;
    int fa=tot;
    if(v==0){
        prepare(fa);
        prepare(fa);
    }
    for(int i=1;i<=cnt;i++){
        for(int j=0;j<=2000;j++){
            f[i][j]=INT_MAX;
        }
    }
    dfs(1);
//    for(int i=1;i<=cnt;i++){
//        cout<<i<<": "<<val[i]<<' '<<vis[i]<<endl;
//    }
    cout<<ans<<endl;
    return 0;
}
