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
