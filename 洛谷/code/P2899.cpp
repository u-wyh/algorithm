// https://www.luogu.com.cn/problem/P2899
// 题意：输入草地数 N，以及 N - 1 条草地之间的无向邻接边 (A, B)（构成一棵树）。
// 在某块草地建一座信号塔后，该草地及与其直接相邻的草地都能收到信号。
// 选择尽量少的草地建造信号塔，使得全部 N 块草地都有信号。
// 输出一个整数，表示需要安装的最少信号塔数量。
// 数据范围：对于 100% 的数据，1 <= N <= 10^4，1 <= A, B <= N，A != B。
#include<bits/stdc++.h>
// 算法标签：贪心、深度优先搜索
using namespace std;
const int MAXN = 10005;

int ans;
int n;
int edges[MAXN][2];
vector<vector<int>>graph;

int f(int x,int p){
    bool k1=false,k2=false,k3=false;
    for(int i=0;i<graph[x].size();i++){
        int v=graph[x][i];
        if(v!=p){
            int k=f(v,x);
            if(k==0){
                k1=true;
            }else if(k==1){
                k2=true;
            }else if(k==2){
                k3=true;
            }
        }
    }
    if(k1){
        ans++;
        return 2;
    }else if(k3){
        return 1;
    }else{
        return 0;
    }
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<n;i++){
        cin>>edges[i][0]>>edges[i][1];
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    if(f(1,0)==0){
        ans++;
    }
    cout<<ans;
    return 0;
}
