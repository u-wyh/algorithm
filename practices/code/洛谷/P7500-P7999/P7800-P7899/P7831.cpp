// https://www.luogu.com.cn/problem/P7831
// 题意：n 点 m 边有向图，
// 第 i 条边 a_i -> b_i 需当前资产 >= r_i 才可通行，
// 通过后资产 +p_i；
// 对每个起点求能无限走下去所需的最小初始资产（无解输出 -1）。
// 数据范围：2 <= n, m <= 2*10^5，
// 1 <= a_i, b_i <= n (a_i != b_i)
// 0 <= r_i, p_i <= 10^9，无自环可能有重边。
// 难度评分：2300（洛谷分级换算）
// 算法标签：拓扑排序、贪心、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9;

int n,m;

struct Edge{
    int u,v,r,p;
};
Edge edge[MAXN];

int ans[MAXN];
int vis[MAXN];
int out[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

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

bool cmp(Edge a,Edge b){
    return a.r<b.r;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        edge[i].u=read(),edge[i].v=read(),edge[i].r=read(),edge[i].p=read();
        out[edge[i].u]++;
    }
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        ans[i]=INF;
    }
    for(int i=1;i<=m;i++){
        addedge(edge[i].v,i);
    }

    queue<int>q;
    for(int i=1;i<=n;i++){
        if(out[i]==0){
            q.push(i);
        }
    }

    for(int i=m;i>=1;i--){
        while(!q.empty()){
            int u=q.front();
            q.pop();

            for(int ei=head[u];ei;ei=nxt[ei]){
                int v=to[ei];
                if(vis[v]){
                    continue;
                }
                vis[v]=true;

                int st=edge[v].u;
                out[st]--;
                if(out[st]==0){
                    q.push(st);
                }

                if(ans[u]!=INF){
                    ans[st]=min(ans[st],max(edge[v].r,ans[u]-edge[v].p));
                }
            }
        }

        if(!vis[i]){
            vis[i]=true;
            int st=edge[i].u;
            out[st]--;

            if(out[st]==0){
                q.push(st);
            }

            ans[st]=min(ans[st],edge[i].r);
        }
    }

    for(int i=1;i<=n;i++){
        if(ans[i]==INF){
            cout<<-1<<' ';
        }
        else{
            cout<<ans[i]<<' ';
        }
    }
    return 0;
}