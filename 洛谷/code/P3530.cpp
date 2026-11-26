// https://www.luogu.com.cn/problem/P3530
// 题意：输入选手数 n，第一类关系数 m_1 和第二类关系数 m_2，每条关系给出两个选手编号。
// 要求所有选手的整型成绩 t_i 满足：对 m_1 个数对 (a_i, b_i) 有 t_{a_i} = t_{b_i} - 1；
// 对 m_2 个数对 (c_i, d_i) 有 t_{c_i} <= t_{d_i}。
// 若无解输出 NIE；否则输出所有选手最多能出现多少种不同的成绩值。
// 数据范围：2 <= n <= 600，1 <= m_1 + m_2 <= 10^5，a_i != b_i，c_i != d_i。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 605;
const int MAXM = 1e5+5;
const int INF = 1e9;

int n,m1,m2;

int sta[MAXN];
int top;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int vol[MAXN];

int dis[MAXN][MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int weight[MAXM<<1];
int to[MAXM<<1];

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

int main()
{
    n=read(),m1=read(),m2=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INF;
        }
        dis[i][i]=0;
    }
    for(int i=1;i<=m1;i++){
        int u,v;
        u=read(),v=read();
        dis[u][v]=1,dis[v][u]=-1;
        addedge(u,v,1);
        addedge(v,u,-1);
    }
    for(int i=1;i<=m2;i++){
        int u,v;
        u=read(),v=read();
        
    }
    return 0;
}