// https://www.luogu.com.cn/problem/P3806
// 题意：第一行输入树点数 n 和询问数 m，
// 接下来 n-1 行每行输入 u, v, w 表示一条边权为 w 的无向树边。
// 随后 m 行每行输入一个整数 k，询问树上是否存在距离恰好为 k 的点对。
// 每次询问输出一行字符串：存在输出 AYE，否则输出 NAY。
// 数据范围：对于 100% 的数据，1 <= n <= 10^4，
// 1 <= m <= 100，1 <= k <= 10^7，
// 1 <= u, v <= n
// 1 <= w <= 10^4。
// 算法标签：点分治、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 105;
const int MAXV = 1e7+5;

int n,m;
int query[MAXM];
int maxk;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int cur[MAXN];
int cntc;

int all[MAXN];
int cnta;

bool exist[MAXV];

bool ans[MAXM];

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
    if(dis>maxk){
        return ;
    }
    cur[++cntc]=dis;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+w);
        }
    }
}

void calc(int u){
    cnta=0;
    exist[0]=true;
    for(int ei=head[u];ei;ei=nxt[ei]){
        int v=to[ei];
        int w=weight[ei];
        if(!vis[v]){
            cntc=0;
            dfs(v,u,w);
            for(int i=1;i<=m;i++){
                for(int j=1;!ans[i]&&j<=cntc;j++){
                    if(query[i]-cur[j]>=0){
                        ans[i]|=exist[query[i]-cur[j]];
                    }
                }
            }
        }
        for(int i=1;i<=cntc;i++){
            all[++cnta]=cur[i];
            exist[cur[i]]=true;
        }
    }
    for(int i=1;i<=cnta;i++){
        exist[all[i]]=0;
    }
}

void compute(int u){
    vis[u]=true;
    calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            compute(getcentroid(v,u));
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=m;i++){
        query[i]=read();
        maxk=max(maxk,query[i]);
    }
    compute(getcentroid(1,0));
    for(int i=1;i<=m;i++){
        if(ans[i]){
            cout<<"AYE"<<endl;
        }
        else{
            cout<<"NAY"<<endl;
        }
    }
    return 0;
}