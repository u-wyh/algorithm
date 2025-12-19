#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250;
const int MAXM = 1000;
// SPFA需要
const int MAXQ = 4000001;

// 链式前向星建图需要
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m,d,k,st;
//n表示一共有多少个点  m表示一共有多少条路线
// 源点出发到每个节点的距离表
int dis[MAXN];
// 节点被松弛的次数
int updateCnt[MAXN];
bool enter[MAXN];
//当前在队列中的话  就是true  否则就是false
queue<int >q;
//每一轮都弹出最后面的一个  如果一个点可以被优化  那么加入队列

bool spfa() {
    dis[st] = -d;
    updateCnt[st]++;
    q.push(st) ;
    enter[st] = true;
    //这道题目中的源点都是1 保持不变   所以以上的操作都针对1
    //实际上应该理解为是针对源点的
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = Next[ei]) {
            v = to[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    //如果不在队列中才会加入
                    // 松弛次数超过n-1就有负环
                    if (++updateCnt[v] > n - 1) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}
//这个函数结束后  可以得到这个点到任何位置的最短路径
//这个函数是为了判断这个图中有没有从原点出发经过的负环

int main()
{
    cin>>d>>m>>n>>k>>st;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=-d;
        head[u]=cnt++;
    }
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w-d;
        head[u]=cnt++;
    }
    if(spfa()){
        cout<<-1;
        return 0;
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        ans=min(ans,dis[i]);
    }
    cout<<-ans;
    return 0;
}

