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