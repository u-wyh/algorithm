// 布局奶牛
// 编号1到编号n的奶牛从左往右站成一排，你可以决定任意相邻奶牛之间的距离
// 有m1条好友信息，有m2条情敌信息，好友间希望距离更近，情敌间希望距离更远
// 每条好友信息为 : u v w，表示希望u和v之间的距离 <= w，输入保证u < v
// 每条情敌信息为 : u v w，表示希望u和v之间的距离 >= w，输入保证u < v
// 你需要安排奶牛的布局，满足所有的好友信息和情敌信息
// 如果不存在合法方案，返回-1
// 如果存在合法方案，返回1号奶牛和n号奶牛之间的最大距离
// 如果存在合法方案，并且1号奶牛和n号奶牛之间的距离可以无穷远，返回-2
// 测试链接 : https://www.luogu.com.cn/problem/P4878
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
// 这道题的输入有两种格式  但是我们必须将它改成同一种
// 这道题的关键是维护本身位置的相对顺序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 20005;

int n,m,k;

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
queue<int >q;

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

int spfa(int s) {
    fill(dis+ 1,dis+ n + 1, INT_MAX);
    dis[s] = 0;
    updateCnt[s]++;
    q.push(s) ;
    enter[s] = true;
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
                    if (++updateCnt[v] > n) {
                        return -1;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    if(dis[n]==INT_MAX)
        return -2;
    return dis[n];
}


int main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        addEdge(i,i-1,0);//保证从左到右一次站  即（i-1）<=（i）-0  这是容易忘记的
    }
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);//和超级源点连边
    }
    // 将两种不同的输入形式全都改成 统一的格式
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(v,u,-w);
    }
    int ans=spfa(0);//判断是否存在矛盾  是否存在负环
    if(ans==-1){
        cout<<ans;
    }
    else{
        ans=spfa(1);
        cout<<ans<<endl;
    }
    return 0;
}