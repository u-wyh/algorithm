#include<bits/stdc++.h>
using namespace std;
const int MAXN=2001;
int n,q;
int h[MAXN];
double cal(int i,int j){
	return 1.0*(h[j]-h[i])/(j-i);
}
set<int> st[MAXN];
int lower(int i,int x){
	auto p=st[i].lower_bound(x);
	p--;
	return *p;
}
int upper(int i,int x){
	auto p=st[i].upper_bound(x);
	return *p;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		st[i].insert(0);
		st[i].insert(n+1);
		double now=-1e9;
		for(int j=i+1;j<=n;j++)
			if(now<=cal(i,j))now=cal(i,j),st[i].insert(j),ans++;
	}
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		h[x]+=y;
		for(int i=1;i<x;i++){
			int y=lower(i,x);
			if(y&&cal(i,y)>cal(i,x))continue;
			if(st[i].find(x)==st[i].end())st[i].insert(x),ans++;
			y=upper(i,x);
			while(y<=n){
				if(cal(i,x)<=cal(i,y))break;
				st[i].erase(y),ans--;
				y=upper(i,y);
			}
		}
		ans-=st[x].size()-2;
		st[x].clear();
		st[x].insert(0);
		st[x].insert(n+1);
		double now=-1e9;
		for(int j=x+1;j<=n;j++)
			if(now<=cal(x,j))now=cal(x,j),st[x].insert(j),ans++;
		cout<<ans<<'\n';
	}
	return 0;
}
