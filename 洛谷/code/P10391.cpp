#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+10;

struct node{
	int to,nxt;
}edge[2*N];
int head[N];
int cnt;

void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}

int dep[N],st[N][30],rd_val[N][30],pv[N];

void dfs(int x,int last){
	dep[x]=dep[last]+1;
	st[x][0]=last;
	rd_val[x][0]=pv[x]|pv[last];
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to==last) continue;
		dfs(edge[i].to,x);
	}
}

int n,q;

void build_st(){
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			rd_val[i][j]=rd_val[i][j-1]|rd_val[st[i][j-1]][j-1];
			st[i][j]=st[st[i][j-1]][j-1];
		}
	}
}
int count(int x){
	int res=0;
	for(int i=0;i<=20;i++){
		if(x&(1<<i)) res++;
	}
	return res;
}
int ask(int x,int y){
	int res=0;
	if(x==y) return 1;
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=20;j>=0;j--){
		if(dep[st[x][j]]>=dep[y]){
			res|=rd_val[x][j];
			x=st[x][j];
		}
	}
	if(x==y) return count(res);
	for(int j=20;j>=0;j--){
		if(st[x][j]!=st[y][j]){
			res|=rd_val[x][j]|rd_val[y][j];
			x=st[x][j];y=st[y][j];
		}
	}
	return count(res|rd_val[x][0]|rd_val[y][0]);
}
int main(){
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>pv[i];
		pv[i]=1<<(pv[i]-1);
	}
	for(int i=1;i<n;i++){
		int uu,vv;
		cin>>uu>>vv;
		add(uu,vv);
		add(vv,uu);
	}
	dfs(1,0);
	build_st();
	while(q--){
		int ss,tt;
		cin>>ss>>tt;
		cout<<ask(ss,tt)<<'\n';
	}
	return 0;
}
