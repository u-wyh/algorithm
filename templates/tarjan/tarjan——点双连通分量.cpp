//https://www.luogu.com.cn/problem/P8435
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 2e6+5;

// 链式前向星存图
int head[MAXN];     // head[u] 表示节点u的第一条边的编号
int Next[MAXM<<1];  // Next[i] 表示第i条边的下一条边
int to[MAXM<<1];    // to[i] 表示第i条边指向的节点
int cnt=1;          // 边的计数器，从1开始（方便处理反向边）

// Tarjan算法相关变量
int dfn[MAXN];      // dfn[u] 表示节点u的DFS序（时间戳）
int low[MAXN];      // low[u] 表示u及其子树能追溯到的最早祖先的dfn
int st[MAXN], top;  // 栈，用于存储当前DFS路径上的节点
int color, Time;    // color记录点双的数量，Time是时间戳计数器
int n, m;           // 节点数和边数
vector<int> ans[MAXN]; // 存储每个点双的节点

// 快速读入函数（适用于大数据量）
inline int read(){
    int x=0, f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0', ch=getchar();
    return x*f;
}

// 添加边（无向图）
void addedge(int u, int v){
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// Tarjan算法求点双连通分量
void tarjan(int u, int f){
    dfn[u] = low[u] = ++Time; // 初始化dfn和low
    st[++top] = u;            // 节点u入栈
    int child = 0;            // 记录u在DFS树中的子节点数量

    // 遍历u的所有邻接节点
    for(int i = head[u]; i; i=Next[i]){
        int v = to[i];
        if(!dfn[v]){          // 如果v未被访问
            child++;
            tarjan(v, u);     // 递归访问v
            low[u] = min(low[u], low[v]); // 更新low[u]

            // 如果low[v] >= dfn[u]，说明u是割点，开始弹出点双
            if(low[v] >= dfn[u]){
                color++;      // 新的点双编号
                // 弹出栈中节点，直到v被弹出（包括v）
                while(st[top] != v){ // 注意：st[top+1]是哨兵
                    ans[color].push_back(st[top--]);
                }
                ans[color].push_back(st[top--]);//弹出 v，并显式加入 u
                
                ans[color].push_back(u); // 割点u属于当前点双
            }
        }
        else if(v != f){      // 如果v已被访问且不是父节点（处理回边）
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 特判：u是孤立点（DFS树的根且没有子节点）
    if(f == 0 && child == 0){
        ans[++color].push_back(u);
    }
}

int main(){
    n = read(), m = read();
    // 读入边并建图
    for(int i=1; i<=m; i++){
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u); // 无向图，加双向边
    }

    // 对所有未访问的节点运行Tarjan
    for(int i=1; i<=n; i++){
        if(!dfn[i]){
            tarjan(i, 0); // 0表示没有父节点（根节点）
        }
    }

    // 输出点双数量和每个点双的节点
    cout << color << endl;
    for(int i=1; i<=color; i++){
        cout << ans[i].size() << ' ';
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}