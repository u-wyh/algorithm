// https://www.luogu.com.cn/problem/P2634
// 题意：n 个点的带权树，两人各自随机选一个点（可重复）。
// 若两点间路径边权和为 3 的倍数则获胜，求获胜概率。
// 输出最简分数 a/b（概率为 1 输出 1/1）。
// 数据范围：n <= 2*10^4。
#include<bits/stdc++.h>
// 算法标签：点分治、深度优先搜索、最大公约数
using namespace std;
const int MAXN = 2e4+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int all[3];
int cur[3];

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

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int dis){
    cur[dis%3]++;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+w);
        }
    }
}

int calc(int u){
    int ans=1;
    all[0]=all[1]=all[2]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            cur[0]=cur[1]=cur[2]=0;
            dfs(v,u,w);
            ans+=all[0]*cur[0]*2+all[1]*cur[2]*2+all[2]*cur[1]*2+cur[0]*2;
            all[0]+=cur[0];
            all[1]+=cur[1];
            all[2]+=cur[2];
        }
    }
    return ans;
}

int compute(int u){
    int ans=0;
    vis[u]=true;
    ans+=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans+=compute(getcentroid(v,u));
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int centroid=getcentroid(1,0);
    int a=compute(centroid);
    int b=n*n;
    int c=gcd(a,b);
    a/=c,b/=c;
    cout<<a<<"/"<<b<<endl;
    return 0;
}