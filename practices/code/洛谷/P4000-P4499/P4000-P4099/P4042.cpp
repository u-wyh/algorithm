// https://www.luogu.com.cn/problem/P4042
// 题意：第一行输入怪兽种类数 N
// 接下来 N 行每行输入第 i 种怪兽的普通攻击消耗 S_i、法术攻击消耗
// K_i、普通攻击杀死后裂变出的怪兽数 R_i 及这 R_i 个新怪兽编号。
// 初始村庄中有 1 只 1 号怪兽；
// 法术攻击可直接彻底消灭 1 只怪兽，
// 普通攻击使其变成对应若干新怪兽（法术攻击消耗不一定大于普通攻击）。
// 输出彻底消灭村庄中全部怪兽所需的最少总体力值。
// 数据范围：对于所有数据，2 <= N <= 2 * 10^5，
// 1 <= R_i, sum(R_i) <= 10^6
// 1 <= K_i, S_i <= 5 * 10^{14}。
// 难度评分：1800（洛谷分级换算）
// 算法标签：Dijkstra、动态规划、拓扑排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e16;
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;

int n;

int degree[MAXN];
int val1[MAXN];
int val2[MAXN];

int dp[MAXN];

int dis[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

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

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val1[i]=read(),val2[i]=read();
        heap.push({i,val2[i]});
        degree[i]=read();
        for(int j=1;j<=degree[i];j++){
            int u=read();
            addedge(u,i);
        }
    }
    while(!heap.empty()){
        int u=heap.top().first;
        if(!dp[u])
            dp[u]=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(vis[v]){
                continue;
            }
            dis[v]+=dp[u];
            degree[v]--;
            if(degree[v]==0){
                heap.push({v,dis[v]+val1[v]});
            }
        }
    }
    cout<<dp[1]<<endl;
    return 0;
}