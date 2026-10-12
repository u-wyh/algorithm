// 用途：判断一组变量差值不等式是否有解。
// 时间：最坏 O(nm)。
// 空间：O(n+m)。
// 例题：https://www.luogu.com.cn/problem/P5960
// 题意：判断一组 x_i-x_j 的上界约束能否同时成立。
// 思路：将不等式转成最短路边；出现负环即矛盾。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 10005;

int n,m;

// 链式前向星建图需要
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

// 源点出发到每个节点的距离表
int dis[MAXN];

// 节点被松弛的次数
int updateCnt[MAXN];
//当前在队列中的话  就是true  否则就是false
bool enter[MAXN];
//每一轮都弹出最后面的一个  如果一个点可以被优化  那么加入队列
queue<int>q;

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool spfa() {
    dis[0] = 0;
    updateCnt[0]++;
    q.push(0) ;
    enter[0] = true;
    //这道题目中的源点都是0 保持不变   所以以上的操作都针对1
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
                    //但是我们加入了一个超级源点  所以总点数加一
                    if (++updateCnt[v] > n) {
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

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    for(int i=1;i<=n;i++){
        //超级源点建边  这个仅仅是为了维护联通性  这种形式是为了判断是否存在负环
        // 所以这里可以使用dis[i]<=dis[0]+0
        addEdge(0,i,0);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        // 形式1的连边方式  u<=v+w  即v向u连一条权值为w的边
        addEdge(v,u,w);
    }
    if(spfa()){
        cout<<"NO"<<endl;
    }else{
        for(int i=1;i<=n;i++)
            cout<<dis[i]<<' ';
    }
    return 0;
}
