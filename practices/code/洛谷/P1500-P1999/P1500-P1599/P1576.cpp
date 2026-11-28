// https://www.luogu.com.cn/problem/P1576
// 题意：有 n 个人，给若干条双向转账关系，每经过一条关系会扣掉当前金额的 z%。
// 选一条从 A 到 B 的转账路线，让 B 到账 100 元，
// 输出 A 最少要付的金额，保留八位小数。
// 数据范围：1 ≤ n ≤ 2000，m ≤ 10^5，答案不超过 10000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Dijkstra、最短路、优先队列

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int MAXM = 200005;

auto compare = [](const pair<int, double>& left, const pair<int, double>& right) {
    return left.second < right.second; // 注意这里是小于，因为我们想要大根堆
};
priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(compare)> heap(compare);
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];
int cnt=1;
int n,m,t;
double dis[MAXN];
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        w=(100-w)*1.0/100;
        //printf("%.8lf\n",w);
        //cout<<w<<endl;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    int st,en;
    cin>>st>>en;
    for(int i=0;i<=n;i++){
        dis[i]=0;
    }
    dis[st]=1;
    heap.push({st,1.0});
    while(!heap.empty()){
        int cur=heap.top().first;
        double rate=heap.top().second;
        heap.pop();
        if(vis[cur]){
            continue;
        }
        vis[cur]=true;
        if(cur==en){
            break;
        }
        for(int i=head[cur];i>0;i=Next[i]){
            if(!vis[to[i]]&&dis[cur]*weight[i]>dis[to[i]]){
                dis[to[i]]=dis[cur]*weight[i];
                heap.push({to[i],dis[to[i]]});
            }
        }
    }
    //printf("%.8lf\n",dis[en]);
    //cout<<dis[en]<<endl;
    printf("%.8lf",100/dis[en]);
    return 0;
}
