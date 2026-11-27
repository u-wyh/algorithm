// https://www.luogu.com.cn/problem/P8312
// 题意：给定 n 点 m 边的有向图，
// 第 i 条边从 a_i 到 b_i 耗时 t_i 分钟。
// q 次询问从 c_j 到 d_j 最多乘坐 k 条边（公交线路）的最短时间；
// 由样例可知若无法到达则输出 -1（起点终点相同为 0）。
// 数据范围：100% 数据满足 2 <= n <= 70，
// 1 <= m, t_i <= 10^6，
// 1 <= a_i, b_i, c_j, d_j <= n
// 1 <= k <= 10^9，1 <= q <= n^2。
// 算法标签：Bellman-Ford、最短路
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 75;
const int MAXM = 1000005;

int n,m,k,q;
int cur[MAXN],Next[MAXN];
int edge[MAXM][3];

void bellman(int st,int en){
    for(int i=1;i<=n;i++){
        cur[i]=INT_MAX;
    }
    cur[st]=0;
    for(int i=0;i<=k-1;i++){
        for(int j=1;j<=n;j++){
            Next[j]=cur[j];
        }
        //我们要建立Next数组  因为存在一种可能性  就是在一轮优化中  同时实现了两个点  这样不利于我们统计k
        for(int j=1;j<=m;j++){
            if (cur[edge[j][0]] != INT_MAX) {
                //如果不是正无穷  说明可以到达edge[j][0]  那么可以继续尝试优化下一个edge[j][1]
                Next[edge[j][1]] = min(Next[edge[j][1]], cur[edge[j][0]] + edge[j][2]);
                //这一轮到达edge[j][1] 的距离是原来的值  和  到达edge[j][0]的值加上从edge[j][0]到edge[j][1]
            }
        }
        //如果修改值的话，从cur数组中拿数字
        for(int j=1;j<=n;j++){
            cur[j]=Next[j];
        }
        //将cur更新为Next数组
    }
    if(cur[en]==INT_MAX){
        cur[en]=-1;
    }
    cout<<cur[en]<<endl;
}

signed main()
{
    cin>>n>>m;
    //cur数组记录的是每个点到st的距离  初始化为正无穷
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
    }
    cin>>k>>q;
    for(int i=1,st,en;i<=q;i++){
        cin>>st>>en;
        bellman(st,en);
    }
    return 0;
}


