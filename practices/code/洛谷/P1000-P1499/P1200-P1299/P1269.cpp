// https://www.luogu.com.cn/problem/P1269
// 题意：1 号服务器沿一棵树发出初始强度的信号，每经过一条边就减去该边的衰减量。
// 在某点装放大器，可将到达的正强度信号恢复为初始强度。
// 让所有节点收到信号，求最少放大器数，无解输出 No solution.。
// 数据范围：节点数不超过 20000，节点编号在 [1,n]，
// 信号强度和每条边的衰减量由输入给出。
// 算法标签：深度优先搜索、贪心、树论

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;

int n;
int val,maxcost;
int ans=0;

int dis[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f,int w){
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u,weight[i]);
            dis[u]=max(dis[u],dis[v]+weight[i]);
        }
    }
    if(dis[u]+w>=val){
        //父亲即使安装了  这个点可以满足   但是下面的点无法满足
        //所以这个点也要安装
        ans++;
        dis[u]=0;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int v,w;
            cin>>v>>w;
            addedge(i,v,w);
            maxcost=max(maxcost,w);
        }
    }
    cin>>val;
    if(val<=maxcost){
        cout<<"No solution."<<endl;
        return 0;
    }
    dfs(1,0,0);//只要开始dfs  说明一定会有答案
    cout<<ans<<endl;
    return 0;
}
