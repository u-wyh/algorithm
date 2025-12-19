#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;
const int MAXM = 14005;
const int INF = 0x3f3f3f3f;

int st,en,n,m;

int col[MAXN];      // 0:蓝色, 1:紫色
int remain[MAXN];   // 初始颜色剩余时间
int blue[MAXN];     // 蓝色持续时间
int pruple[MAXN];   // 紫色持续时间
int all[MAXN];      // 总周期时间

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];  // 修正：应该是MAXM而不是MAXN
int cnt=1;

// 距离数组，存储到达每个节点的最短时间
int dist[MAXN];

// 优先队列元素
struct Node {
    int id, time;
    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int getcolor(int x,int t){
    // 如果还在初始颜色的剩余时间内
    if(t < remain[x]){
        return col[x];
    }
    
    // 计算进入周期循环后的时间
    int cyc = t - remain[x];
    int res = cyc % all[x];
    
    if(col[x] == 0){ // 初始为蓝色
        // 蓝色 -> 紫色 -> 蓝色循环
        if(res < pruple[x]){
            return 1; // 紫色时间段
        } else {
            return 0; // 蓝色时间段
        }
    } else { // 初始为紫色
        // 紫色 -> 蓝色 -> 紫色循环
        if(res < blue[x]){
            return 0; // 蓝色时间段
        } else {
            return 1; // 紫色时间段
        }
    }
}

int gettime(int x,int y,int t){
    int maxwait = 2 * max(all[x], all[y]);
    
    // 遍历所有可能的等待时间
    for(int wait = 0; wait <= maxwait; wait++){
        int current_time = t + wait;
        if(getcolor(x, current_time) == getcolor(y, current_time)){
            return wait;
        }
    }
    
    return INF; // 无法等到相同颜色
}

void dijkstra(){
    // 初始化距离数组
    memset(dist, 0x3f, sizeof(dist));
    dist[st] = 0;
    
    // 优先队列（最小堆）
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({st, 0});
    
    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();
        
        int u = current.id;
        int current_time = current.time;
        
        // 如果当前时间不是最短时间，跳过
        if(current_time > dist[u]){
            continue;
        }
        
        // 如果到达终点，可以提前结束
        if(u == en){
            break;
        }
        
        // 遍历所有邻接边
        for(int i = head[u]; i; i = nxt[i]){
            int v = to[i];
            int travel_time = weight[i];
            
            // 计算等待时间
            int wait_time = gettime(u, v, current_time);
            
            if(wait_time != INF){
                int new_time = current_time + wait_time + travel_time;
                
                if(new_time < dist[v]){
                    dist[v] = new_time;
                    pq.push({v, new_time});
                }
            }
        }
    }
}

int main()
{
    cin >> st >> en >> n >> m;
    
    // 读取节点信息
    for(int i = 1; i <= n; i++){
        char c;
        cin >> c >> remain[i] >> blue[i] >> pruple[i];
        col[i] = (c == 'B') ? 0 : 1;  // B->0, P->1
        all[i] = blue[i] + pruple[i];
    }
    
    // 读取边信息并建图
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
        addedge(v, u, w);  // 无向图，双向添加
    }
    
    // 运行Dijkstra算法
    dijkstra();
    
    // 输出结果
    if(dist[en] == INF){
        cout << 0 << endl;
    } else {
        cout << dist[en] << endl;
    }
    
    return 0;
}