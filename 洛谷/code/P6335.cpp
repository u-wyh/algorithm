// 仙人掌最长路线，C++版
// 给定n个点、m条边的无向连通图，输入保证图是仙人掌
// 路线可以从任何城市开始，但必须在1号点结束
// 路线可以重复经过同一个点，但不能重复经过同一条边
// 计算最长路线的边数
// 1 <= n <= 10^4
// 1 <= m <= 2 * 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P6335
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这个dp设置是非常巧妙的
// 尤其是f和g g=f+delta
// 这里的delta 对于割边而言，就是完全可以实现f之后  
// 直接去往割边方向，相当于割边方向就是完全的可以多走的
// 对于环而言  可以是先把其他环走完  这个环尽量看看有没有最大值
// 对于一个节点而言，f就是所有环的长度
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 4e4+5;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cntg=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

// 用于收集环上的节点
int cycle[MAXN];
// 在以u为头的子仙人掌树下
// 表示从这个出发，最终回到这个点的最长距离
int f[MAXN];
// 表示从这个出发，最终不需要回到这个点的最长距离
int g[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int dponcycle(int u,int v){
    int sz=0;
    int pop;
    do{
        pop=sta[top--];
        cycle[++sz]=pop;
    }while(pop!=v);
    int best=0;
    int sum=1;
    for(int i=1;i<=sz;i++){
        best=max(best,sum+g[cycle[i]]);
        sum+=f[cycle[i]]+1;
    }
    f[u]+=sum;
    int oth=sum;
    for(int i=1;i<=sz;i++){
        oth-=f[cycle[i]]+1;
        best=max(best,oth+g[cycle[i]]);
    }
    return best-sum;
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    int delta=0;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                top--;
                delta=max(delta,g[v]+1);
            }
            else{
                delta=max(delta,dponcycle(u,v));
            }
        }
        else if(dfn[v]<dfn[u]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    g[u]=f[u]+delta;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    tarjan(1,0);
    cout<<g[1]<<endl;
    return 0;
}