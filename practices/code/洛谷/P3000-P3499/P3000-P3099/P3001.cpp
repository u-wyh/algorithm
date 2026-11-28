// https://www.luogu.com.cn/problem/P3001
// 题意：输入国家数 N、单向汇率数 M、起始价格 V、起点国 A、终点国 B，
// 以及 M 条单向兑换关系 (i -> j, 汇率 e_{ij})。
// 拿着 A 国价值为 V 的商品，
// 通过一系列单向货币汇率兑换到 B 国（每次兑换价格乘以对应汇率）。
// 求在 B 国能得到的最低价格
// （若存在负环/可无限压低价格等无最小值情况则输出 0）。
// 输出一行一个浮点数，表示最低价格（精确到 10^-6），无最小值输出 0。
// 数据范围：对于 100% 的数据，1 <= N <= 2000，
// 1 <= M <= 25000，0.1 <= e_{ij} <= 10
// 1 <= V <= 10^12（保证答案小于 10^15）。
// 难度评分：1300（洛谷分级换算）
// 算法标签：SPFA、最短路
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int MAXM = 25005;

int n,m;
double val;
int st,en;

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
long double weight[MAXM];

long double dis[MAXN];
int updatecnt[MAXN];
bool enter[MAXN];
queue<int>q;

void addedge(int u,int v,long double w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool spfa(){
    dis[st]=val;
    updatecnt[st]=1;
    enter[st]=1;
    q.push(st);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        enter[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            long double w=weight[i];
            if(dis[v]>dis[u]*w){
                dis[v]=dis[u]*w;
                if(!enter[v]){
                    enter[v]=1;
                    updatecnt[v]++;
                    q.push(v);
                    if(updatecnt[v]>=n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

signed main()
{
    cin>>n>>m>>val>>st>>en;
    for(int i=1;i<=m;i++){
        int u,v;
        long double w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    for(int i=1;i<=n;i++){
        dis[i]=1e18;
    }
    if(spfa()){
        printf("%.6Lf",dis[en]);
    }
    else{
        cout<<0<<endl;
    }
    return 0;
}