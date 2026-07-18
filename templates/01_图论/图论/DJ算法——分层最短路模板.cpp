// 飞行路线（语言提供的堆）
// Alice和Bob现在要乘飞机旅行，他们选择了一家相对便宜的航空公司
// 该航空公司一共在n个城市设有业务，设这些城市分别标记为0 ~ n−1
// 一共有m种航线，每种航线连接两个城市，并且航线有一定的价格
// Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机
// 航空公司对他们这次旅行也推出优惠，他们可以免费在最多k种航线上搭乘飞机
// 那么 Alice 和 Bob 这次出行最少花费多少
// 测试链接 : https://www.luogu.com.cn/problem/P4568
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 100005;
const int MAXK = 11;

struct Range {
    int cur,t,cost;
};
// 比较函数，用于小根堆，当 l 值相等时，可以通过添加额外的比较来保持稳定性
bool compare(const Range& a, const Range& b) {
    return a.cost > b.cost; // 注意这里是大于号，因为我们要使用 greater<> 来获得小根堆
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);
int n,m,k,st,en;
int head[MAXN];
int Next[MAXM];
int weight[MAXM];
int to[MAXM];
int cnt=1;
int dis[MAXN][MAXK];
bool visited[MAXN][MAXK];

int main()
{
    cin>>n>>m>>k>>st>>en;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=k;j++){
            dis[i][j]=INT_MAX;
            visited[i][j]=false;
        }
    }
    dis[st][0]=0;
    heap.push({st,0,0});
    while (!heap.empty()) {
        Range record = heap.top();
        heap.pop();
        int cur = record.cur;
        int t = record.t;
        int cost = record.cost;
        if (visited[cur][t]) {
            continue;
        }
        visited[cur][t] = true;
        if (cur == en) {
            // 常见剪枝
            // 发现终点直接返回
            // 不用等都结束
            cout<<cost;
            return 0;
        }
        for(int i=head[cur];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(t<k&&dis[v][t+1]>dis[cur][t]){
                dis[v][t+1]=dis[cur][t];
                heap.push({v,t+1,cost});
            }
            if(dis[v][t]>dis[cur][t]+w){
                dis[v][t]=dis[cur][t]+w;
                heap.push({v,t,cost+w});
            }
        }
    }
    cout<<-1;
    return 0;
}
