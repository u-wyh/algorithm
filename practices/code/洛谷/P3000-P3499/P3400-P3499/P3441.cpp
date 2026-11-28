// https://www.luogu.com.cn/problem/P3441
// 题意：输入车站数 n（1..n）和可规划的地铁线路数 l，
// 以及 n-1 条构成一棵树的双向隧道 (a_i, b_i)。
// 每条地铁线路是树上的一条简单路径（不能分叉），不同线路可以共用车站或隧道；
// 求 l 条线路的并集最多能覆盖多少个不同车站。
// 输出一个整数，表示最多能被覆盖的车站数量。
// 数据范围：2 <= n <= 1000000，0 <= l <= n，
// 1 <= a_i, b_i <= n。
// 难度评分：2300（洛谷分级换算）
// 算法标签：拓扑排序、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,k;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int in[MAXN];
bool vis[MAXN];
int lay[MAXN];
int laycnt[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    in[v]++;
}

void topo(){
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(in[i]==1){
            q.push(i);
            lay[i]=1;
            vis[i]=1;
            laycnt[lay[i]]++;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!vis[v]){
                in[v]--;
                if(in[v]==1){
                    vis[v]=true;
                    lay[v]=lay[u]+1;
                    laycnt[lay[v]]++;
                    q.push(v);
                }
            }
        }
    }
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    topo();
    int ans=0;
    for(int i=1;laycnt[i];i++){
        ans+=min(k*2,laycnt[i]);
    }
    cout<<ans<<endl;
    return 0;
}