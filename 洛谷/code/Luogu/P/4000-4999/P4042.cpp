#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e16;
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;

int n;

int degree[MAXN];
int val1[MAXN];
int val2[MAXN];

int dp[MAXN];

int dis[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val1[i]=read(),val2[i]=read();
        heap.push({i,val2[i]});
        degree[i]=read();
        for(int j=1;j<=degree[i];j++){
            int u=read();
            addedge(u,i);
        }
    }
    while(!heap.empty()){
        int u=heap.top().first;
        if(!dp[u])
            dp[u]=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(vis[v]){
                continue;
            }
            dis[v]+=dp[u];
            degree[v]--;
            if(degree[v]==0){
                heap.push({v,dis[v]+val1[v]});
            }
        }
    }
    cout<<dp[1]<<endl;
    return 0;
}