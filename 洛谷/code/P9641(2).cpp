#include<bits/stdc++.h>
using namespace std;
int n,m;
string str[100005];
int fa[100005],d[100005];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y,int x_,int y_){
	int s1=(x-1)*m+y,s2=(x_-1)*m+y_;
	int u=find(s1),v=find(s2);
	if(u!=v) fa[v]=u;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++){
		fa[i]=i;
		d[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>str[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			scanf("%d",&x);
			int ch=(int)str[i][j-1],p,q;
			if(ch==117) p=i-x,q=j;
			else if(ch==100) p=i+x,q=j;
			else if(ch==108) p=i,q=j-x;
			else p=i,q=j+x;
			if(p<1||q<1||p>n||q>m) continue;
			merge(i,j,p,q);
			d[(p-1)*m+q]++;
		}
	}
	int x=find(1),cnt=n*m;
	for(int i=2;i<=cnt;i++){
		if(find(i)!=x){
			puts("No");
			return;
		}
	}
	int res=0;
	for(int i=1;i<=cnt;i++){
		if(!d[i]) res++;
		if(res>1){
			puts("No");
			return;
		}
	}
	puts("Yes");
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
