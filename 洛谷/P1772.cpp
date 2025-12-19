#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 22;
const int MAXM = 505;
const int MAXT = 105;

int n,m,t,cost;
int k;

int dp[MAXT];

bool clos[MAXN][MAXT];
bool closed[MAXN];
bool vis[MAXN];

int money[MAXT][MAXT];

int dis[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];

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

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void spfa(){
	for(int i=1;i<=n;i++) {
        dis[i]=1e9,vis[i]=0;
	}
	queue<int> q;
	dis[1]=0;
	q.push(1);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int v=to[i];
			if(closed[v])
                continue;
			if(dis[v]>dis[x]+weight[i]){
				dis[v]=dis[x]+weight[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}

signed main()
{
    t=read(),n=read(),cost=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    k=read();
    for(int i=1;i<=k;i++){
        int p,l,r;
        p=read(),l=read(),r=read();
        for(int j=l;j<=r;j++){
            clos[p][j]=true;
        }
    }
    for(int i=1;i<=t;i++){
        for(int j=i;j<=t;j++){
            memset(closed,0,sizeof(closed));
            for(int k=i;k<=j;k++){
                for(int p=1;p<=n;p++){
                    if(clos[p][k]){
                        closed[p]=true;
                    }
                }
            }
            spfa();
            money[i][j]=dis[n];
        }
    }
    for(int i=1;i<=t;i++){
        dp[i]=INT_MAX;
    }
    for(int i=1;i<=t;i++){
        dp[i]=money[1][i]*i;
        for(int j=i-1;j>=0;j--){
            dp[i]=min(dp[i],dp[j]+money[j+1][i]*(i-j)+cost);
        }
    }
    cout<<dp[t]<<endl;
    return 0;
}
