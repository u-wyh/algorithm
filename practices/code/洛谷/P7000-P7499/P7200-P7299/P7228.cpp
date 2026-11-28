// https://www.luogu.com.cn/problem/P7228
// 题意：给定一棵 N 个点的无向树，为每条边定向，
// 使得有向图中的最长有向路径长度最小，
// 输出任意一种定向方案（1 表示 a_i -> b_i
// 0 表示 b_i -> a_i）。
// 数据范围：2 <= N <= 10^5，1 <= a_i, b_i <= N。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、构造
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int dir[MAXN<<1];
bool vis[MAXN];

int n;
int f=1;

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(!vis[v]){
            dir[i]=1^f;
            if(i<n)
                dir[i]=f;
            else
                dir[i-n+1]=f;
            vis[v]=true;
            dfs(v,1^f);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1,j=n;i<n;i++,j++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[n+cnt-2]=head[v];
        to[n+cnt-2]=u;
        head[v]=n+cnt-2;
    }
    vis[1]=true;
    dfs(1,f);
    for(int i=1;i<n;i++){
        printf("%3d",dir[i]);
    }
    cout<<endl;
    for(int i=n;i<=2*n-2;i++){
        printf("%3d",dir[i]);
    }
    cout<<endl;
    return 0;
}
