// https://www.luogu.com.cn/problem/P3125
// 题意：输入草皮数 N、相邻移动耗能 E，
// 以及每块草皮的质量 Q 和邻接表（每块最多连 10 条双向边）。
// 从任意草皮出发吃草可获其能量 Q，也可路过不吃；
// 但之后只能吃质量严格高于此前吃过的所有草的草皮，且每走一条边消耗 E 能量。
// 求最终能积累的最大净能量值。
// 输出一个整数表示最大净能量。
// 数据范围：1 <= N <= 1000，1 <= E, Q <= 10^6，
// 每块草皮度数为 D <= 10。
// 难度评分：1800（洛谷分级换算）
// 算法标签：广度优先搜索、最短路、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1005;
const int MAXM = 10005;

int n,m;
struct node{
    int sub,val;
}nums[MAXN];
int f[MAXN];

int dis[MAXN][MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];

queue<int>q;
bool vis[MAXN];

void addedge(int u,int v){
    // cout<<u<<' '<<v<<endl;
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool cmp(node a,node b){
    return a.val>b.val;
}

void bfs(int st){
    while(!q.empty()){
        q.pop();
    }
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    dis[st][st]=0;
    vis[st]=true;
    q.push(st);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!vis[v]){
                vis[v]=true;
                q.push(v);
                dis[st][v]=dis[st][u]+m;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     if(!vis[i]){
    //         cout<<666<<endl;
    //     }
    // }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        nums[i].sub=i;
        cin>>nums[i].val;
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            addedge(i,v);
        }
    }
    nums[0].sub=0;
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=n;i++){
        dis[0][i]=0;
    }
    for(int i=1;i<=n;i++){
        bfs(i);
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<dis[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    int ans=0;
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            f[i]=max(f[i],nums[i].val+f[j]-dis[nums[j].sub][nums[i].sub]);
        }
        ans=max(ans,f[i]);
    }
    cout<<ans<<endl;
    return 0;
}