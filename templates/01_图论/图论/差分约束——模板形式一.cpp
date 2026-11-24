// 负环和差分约束模版题(转化成形式1进而转化成判断负环)
// 一共有n个变量，编号1~n，给定m个不等式，每个不等式的形式为
// Xi - Xj <= Ci，其中Xi和Xj为变量，Ci为常量
// 如果不等式存在矛盾导致无解，打印"NO"
// 如果有解，打印满足所有不等式的其中一组解(X1, X2...)
// 1 <= n、m <= 5 * 10^3
// -10^4 <= Ci <= +10^4
// 测试链接 : https://www.luogu.com.cn/problem/P5960
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
// 这种形式是值往小的方向更新  初始为最大值  一个式子u-v>=w   --->  v<=u-w v的权值小于等于u的权值-w
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