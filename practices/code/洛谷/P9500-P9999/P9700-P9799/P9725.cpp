// https://www.luogu.com.cn/problem/P9725
// 题意：多组数据（共 T 组）。
// 给定 n 个房间的树。
// 追逐游戏中 Shou 先手、Pang 后手轮流行动，
// 每次可留在原地或移动到相邻房间（双方信息完全透明），
// Pang 与 Shou 在同一房间即抓获。
// 求至少需要额外添加多少条边，
// 才能使无论初始位置 (u, v)（u != v）如何，
// Pang 都无法在有限回合内抓获 Shou；
// 若无论如何加边均无法做到，输出 -1。
// 题意：第一行输入 T，每组输入 n 及 n-1 条树边 (u, v)；
// 每组输出一行一个整数。
// 数据范围：1 <= T <= 10^4，
// 2 <= n <= 10^5，sum(n) <= 2 * 10^5，
// 1 <= u, v <= n。
//P9725
// 难度评分：1700（洛谷分级换算）
// 算法标签：树上度数统计
#include<bits/stdc++.h>
using namespace std;

int u[100005]={0},v[100005]={0},du[100005]={0};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        memset(du,0,sizeof du);//所有入度清零
        for(int i=1;i<n;i++){
            cin>>u[i]>>v[i];
            du[u[i]]++;
            du[v[i]]++;//相应入度加一
        }
        if(n<=3){
            //如果三个点都没有 一定不行
            puts("-1");
            continue;
        }
        map<int,int> q;//表示以i为中心直接连接的点中  有多少是叶子结点
        int leaf=0;
        for(int i=1;i<n;i++){
            if(du[u[i]]==1)q[v[i]]++,leaf++;
            if(du[v[i]]==1)q[u[i]]++,leaf++;//如果一个节点是叶子结点  那么与他相连的点加一
        }
        if(q.size()==1){
            //说明是菊花图   一定不行 即只有一个节点有叶子结点
            puts("-1");
            continue;
        }
        //到了这一步还没有退出  说明一定有答案
        int ans=0;
        for(auto it=q.begin();it!=q.end();it++){
            ans=max(ans,it->second);//表示一个节点最多连接多少个叶子结点
        }
        cout<<((ans>leaf/2)?ans:(leaf+1)/2)<<endl;
        //如果说有一个节点的叶子结点个数超出叶子结点总数一半  那么没办法 只能是这个数了
        //否则就是叶子结点的总数除二  向上取整
    }
    return 0;
}

