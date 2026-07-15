#include<bits/stdc++.h>
using namespace std;
const double sml = 1e-6;
const int MAXN = 1005;
const int MAXM = 5005;

int head[MAXN];
int to[MAXM];
int Next[MAXM];
double weight[MAXM];
int cnt=1;
int n,m;
int arr[MAXN];
// dfs判断负环，每个点的累积边权
double d[MAXN];
// dfs判断负环，每个点是否是递归路径上的点
bool vis[MAXN];
int num[MAXN];

void addedge(int u,int v,double w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int check(double x)
{
    queue<int> q;
    for(int i=1;i<=n;++i)//因为图不一定连通，所以初始所有结点入队
    {
    	q.push(i);
    	d[i]=0;
    	vis[i]=num[i]=1;
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=Next[i])
        {
            int v=to[i];
            double dis=weight[i];
            if(d[v]>d[u]+x*dis-arr[u])//边权为mid*Tim[e_i]-Fun[u_i]
            {
                d[v]=d[u]+x*dis-arr[u];
                if(!vis[v])
                {
                    q.push(v); vis[v]=1;
                    if(++num[v]>=n) return 1;
                }
            }
        }
    }
    return 0;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    double l = 0, r = 2000, x, ans = 0;
    while (l < r && r - l >= sml) {
        x = (l + r) / 2;
        if (!check(x)) {
            r = x - sml;
        } else {
            ans = x;
            l = x + sml;
        }
    }
    printf("%.2lf\n", ans);
    return 0;
}
