#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
long long dis[MAXN];
int n,m,home,st,t;
struct node{
    int pos;
    long long t;
}nums[MAXN];
bool vis[MAXN];
queue<int>q;

bool cmp(node a,node b){
    return a.t<b.t;
}

inline void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main()
{
    cin>>n>>m>>home>>st;
    nums[0].t=1;
    nums[0].pos=st;
    for(int i=1;i<=n;i++){
        dis[i]=LLONG_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>nums[i].t>>nums[i].pos;
    }
    sort(nums,nums+t+1,cmp);
    q.push(home);
    dis[home]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[v]>w+dis[u]){
                dis[v]=w+dis[u];
                q.push(v);
            }
        }
    }
//    for(int i=1;i<=n;i++){
//        cout<<dis[i]<<' ';
//    }
//    cout<<endl;
    if(dis[st]<nums[1].t||t==0) {  //不用管瞬移的两种情况
		cout<<dis[st];
		return 0;
	}
	for(int i=1;i<=t;i++) {  //枚举瞬移找答案
		if(dis[nums[i].pos]<=nums[i].t) {  //守株待兔或正好抓住的情况
			cout<<nums[i].t;
			return 0;
		}
		else {
			if(dis[nums[i].pos]<nums[i+1].t) {  //在下一次瞬移前抓住的情况
				cout<<dis[nums[i].pos];
				return 0;
			}
		}
	}
    return 0;
}
