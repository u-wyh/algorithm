#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 20005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int dis[MAXN];
bool vis[MAXN];

int n,m,k;

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

inline void build(){
    for(int i=1;i<=n;i++){
        dis[i]=1005;
        vis[i]=false;
    }
}

bool check(int limit)
{
	//memset(dis,1005,sizeof(dis));
	//memset(vis,false,sizeof(vis));
	build();
	//cout<<dis[n]<<' ';
	queue<int> q;
	q.push(1);
	dis[1]=0;
	vis[1]=true;
	while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i]>limit?1:0;
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
	}
	//cout<<dis[n]<<endl;
	return dis[n]>k?false:true;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int l=0,r=1e6,mid,ans=-1;
    while(l<=r){
        mid=(l+r)/2;
        //cout<<mid<<' ' <<ans<<endl;
        //system("pause");
        if(check(mid)){
            //cout<<"yes"<<endl;
            ans=mid;
            r=mid-1;
        }
        else {
            //cout<<"no"<<endl;
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
