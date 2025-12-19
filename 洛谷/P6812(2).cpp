#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int l;
	int r;
	int lw;
	int rw;
	bool flag;
}e[10000010];

int n,m;
int a[10000010];
int lazy[10000010];

void merge(int i){
	e[i].lw = e[i * 2].lw;
	e[i].rw = e[i * 2 + 1].rw;
	if(e[i * 2].rw <= e[i * 2 + 1].lw && e[i * 2].flag && e[i * 2 + 1].flag)e[i].flag = true;
	else e[i].flag = false;
}

void renewans(node &x,node &y,node &z){
	x.lw = y.lw;
	x.rw = z.rw;
	if(y.flag && z.flag && y.rw <= z.lw)x.flag = true;
	else x.flag = false;
}

void pushup(int i,int w){
	e[i].lw += w;
	e[i].rw += w;
	lazy[i] += w;
}

void pushdown(int i){
	if(e[i].l == e[i].r)return ;
	pushup(i * 2,lazy[i]);
	pushup(i * 2 + 1,lazy[i]);
	lazy[i] = 0;
}

void build(int i,int l,int r){
	e[i].l = l;
	e[i].r = r;
	if(l == r){
		e[i].lw = e[i].rw = a[l];
		e[i].flag = true;
		return ;
	}
	int mid = (l + r) / 2;
	build(i * 2,l,mid);
	build(i * 2 + 1,mid + 1,r);
	merge(i);
}

void update(int i,int l,int r,int w){
	if(e[i].l >= l && e[i].r <= r){
		pushup(i,w);
		return ;
	}
	pushdown(i);
	int mid = (e[i].l + e[i].r) / 2;
	if(mid >= l)update(i * 2,l,r,w);
	if(mid < r)update(i * 2 + 1,l,r,w);
	merge(i);
}

node query(int i,int l,int r){
	if(e[i].l >= l && e[i].r <= r)return e[i];
	pushdown(i);
	int mid = (e[i].l + e[i].r) / 2;
	node ans;
	node ans1;
	node ans2;
	if(mid >= r)return query(i * 2,l,r);
	else if(mid < l)return query(i * 2 + 1,l,r);
	else {
		ans1 = query(i * 2,l,mid);
		ans2 = query(i * 2 + 1,mid + 1,r);
		renewans(ans,ans1,ans2);
	}
	return ans;
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++)a[i] = read();
	build(1,1,n);
	while(m --){
		int op;
		int l,r,w;
		op = read();
		if(op == 1){
			l = read(),r = read(),w = read();
			update(1,l,r,w);
		}
		else {
			l = read(),r = read();
			node ans = query(1,l,r);
			if(ans.flag == true)puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
