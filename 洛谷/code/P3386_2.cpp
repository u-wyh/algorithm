// https://www.luogu.com.cn/problem/P3386
// 题意：给一个二分图，左边 n 个点，右边 m 个点，一共有 e 条边。
// 每条边 (u, v) 连接左边的 u 和右边的 v。两边分别从 1 编号，输入可能有重边。
// 选尽量多的边，使任意两条选中的边都不共享端点，输出选中的边数。
// 数据范围：1 ≤ n, m ≤ 500，1 ≤ e ≤ 5 × 10^4，1 ≤ u ≤ n，1 ≤ v ≤ m。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 5e4+5;
const int INF = 1e9;

int n,m,k;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int matchlt[MAXN];
int matchrt[MAXN];
int dislt[MAXN];
int disrt[MAXN];
bool vis[MAXN];

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

bool bfs(){
    queue<int>q;
    for(int i=1;i<=n;i++){
        dislt[i]=INF;
    }
    for(int i=1;i<=m;i++){
        disrt[i]=INF;
    }
    for(int i=1;i<=n;i++){
        if(matchlt[i]==0){
            dislt[i]=0;
            q.push(i);
        }
        else{
            dislt[i]=INF;
        }
    }

    bool flag=false;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(disrt[v]==INF){
                disrt[v]=dislt[u]+1;
                if(matchrt[v]==0){
                    flag=true;
                }
                else{
                    dislt[matchrt[v]]=disrt[v]+1;
                    q.push(matchrt[v]);
                }
            }
        }
    }

    return flag;
}

bool dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(disrt[v]==dislt[u]+1){
            disrt[v]=INF;
            if(matchrt[v]==0||dfs(matchrt[v])){
                matchlt[u]=v;
                matchrt[v]=u;
                return true;
            }
        }
    }
    return false;
}

int HK(){
    int match=0;
    while(bfs()){
        for(int i=1;i<=n;i++){
            if(matchlt[i]==0&&dfs(i)){
                match++;
            }
        }
    }
    return match;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=k;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
    }

    for(int i=1;i<=n;i++){
        dislt[i]=INF;
    }
    for(int i=1;i<=m;i++){
        disrt[i]=INF;
    }
    int maxmatch=HK();
    cout<<maxmatch<<endl;
    return 0;
}