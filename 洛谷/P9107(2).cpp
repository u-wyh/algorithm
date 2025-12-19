#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;

int n,m,k;
int vis[2010][2010],dr[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
ll user[N];
char a[2010][2010];
struct node{
	int x,y,ul,dr;
	node(int tx,int ty,int tul,int tdr){
		x=tx,	y=ty;
		ul=tul,	dr=tdr;
	}
};

void bfs(ll &ul,ll &rd){
	queue<node> q;
	q.push(node(1,1,0,0));
	vis[1][1]=1;
	while(!q.empty()){
		node nd=q.front();
		q.pop();
		if(nd.x==n && nd.y==m){
			ul=nd.ul,	rd=nd.dr;
			return;
		}
		for(int i=0;i<4;i++){
			int tx=nd.x+dr[i][0],	ty=nd.y+dr[i][1],	tul=nd.ul,	tdr=nd.dr;
			if(tx<1 || tx>n || ty<1 || ty>m || a[tx][ty]=='X' || vis[tx][ty])
				continue;
			if(i==2 || i==3)
				tul+=1;
			else
				tdr+=1;
			q.push(node(tx,ty,tul,tdr));
			vis[tx][ty]=1;
		}
	}
}

int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i]+1;
	}
	ll ul=0,dr=0;
	bfs(ul,dr);
	ll mi=LLONG_MAX,cnt=0;
	for(int i=1;i<=k;i++){
		int ta,tb;
		cin>>ta>>tb;
		user[i]=ul*tb+dr*ta;
		mi=min(mi,user[i]);
	}

	for(int i=1;i<=k;i++){
		if(mi==user[i]){
			cnt+=1;
		}
	}
	cout<<mi<<" "<<cnt;
	return 0;
}
