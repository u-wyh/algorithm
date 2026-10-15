// 用途：二分图最大匹配；输入左点数 n、右点数 m、边数 k。
// 时间：O(E√V)。
// 空间：O(V+E)。
// 注意：点编号两侧各从 1 开始；重复边允许。
// 例题：https://www.luogu.com.cn/problem/P3386
// 题意：给定二分图，求最多能配成多少对互不冲突的点。
// 思路：BFS 分层寻找最短增广路，DFS 一轮增广多条路。
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
int que[MAXN];

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

// BFS 建增广路分层，DFS 只沿相邻层增广。
bool bfs(){
    int ql=0,qr=0;
    for(int i=1;i<=n;i++){
        dislt[i]=INF;
    }
    for(int i=1;i<=m;i++){
        disrt[i]=INF;
    }
    for(int i=1;i<=n;i++){
        if(matchlt[i]==0){
            dislt[i]=0;
            que[qr++]=i;
        }
        else{
            dislt[i]=INF;
        }
    }

    bool flag=false;
    while(ql<qr){
        int u=que[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(disrt[v]==INF){
                disrt[v]=dislt[u]+1;
                if(matchrt[v]==0){
                    flag=true;
                }
                else{
                    dislt[matchrt[v]]=disrt[v]+1;
                    que[qr++]=matchrt[v];
                }
            }
        }
    }

    return flag;
}

bool dfs(int u){
    // 本轮只走 BFS 的下一层，右点失败后标 INF 防止重复尝试。
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
    // 每轮 BFS 找一批最短增广路，再从所有未匹配左点尝试增广。
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

    int maxmatch=HK();
    cout<<maxmatch<<endl;
    return 0;
}
