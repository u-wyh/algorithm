#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int rread(){
	int x=0;
	char c=getchar(),o=' ';
	while(c<'0'||c>'9')o=c,c=getchar();
	while(c>='0'&&c<='9')x*=10,x+=(c^48),c=getchar();
	if(o=='-')x=-x;
	return x;
}
inline int lowbit(int x){
	return x&(-x);
}
struct node{
	int a,num;
}nd[100010];
bool operator <(const node& x,const node& y){
	return (x.a==y.a)?x.num<y.num:x.a<y.a;
}
int n,tree[100010];
inline void change(int x,int c){
	while(x<=n){
		tree[x]+=c;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int ans=0;
	while(x>0){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	n=rread();
	for(int i=1;i<=n;i++){
		nd[i].a=rread();
		nd[i].num=i;
		change(nd[i].num,1);
	}
	sort(nd+1,nd+1+n);
	int ans=0;
	int in=1;
	for(int i=0;i<n;i++){
		cout<<ans<<'\n';
		int t=in;
		while(i==nd[t].a){
			ans+=query(nd[t].num-1);
			change(nd[t].num,-1);
			t++;
		}
		in=t;
	}
	return 0;
}
