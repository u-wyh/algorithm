// https://www.luogu.com.cn/problem/P10463
// 题意：给长为 N 的数组，执行 M 条指令。C l r d 给下标 l 到 r 全部加 d，Q l r 查询这些项的最大公约数。每条 Q 输出一个答案。
// 数据范围：N ≤ 5 × 10^5，M ≤ 10^5，1 ≤ a[i] ≤ 10^18，d 的绝对值不超过 10^18，计算过程在有符号 64 位整数范围内。

#include<bits/stdc++.h>
#define int long long
#define mid ((l + r) >> 1)
#define lchild (root << 1)
#define rchild ((root << 1) + 1)
using namespace std;
const int N = 5e5 + 9;
int n,m;
int a[N],b[N],c[N];
string op;
int l,r,d;
struct node{
	int val;
} t[N << 2];

int GCD(int a,int b){
	return b ? GCD(b,a % b) : abs(a);
}

bool in_range(int l,int r,int L,int R){
	return L <= l && r <= R;
}

bool out_range(int l,int r,int L,int R){
	return l > R || r < L;
}

void push_up(int root){
	t[root].val = GCD(t[lchild].val,t[rchild].val);
}

void build(int root,int l,int r){
	if(l == r){
		t[root].val = b[l];
		return;
	}
	build(lchild,l,mid);
	build(rchild,mid + 1,r);
	push_up(root);
}

void update(int root,int l,int r,int k,int v){
	if(r < k || l > k)
		return;
	if(l == r){
		t[root].val += v;
		return;
	}
	if(k <= mid)
		update(lchild,l,mid,k,v);
	else
		update(rchild,mid + 1,r,k,v);
	push_up(root);
}

int query(int root,int l,int r,int L,int R){
	if(out_range(l,r,L,R))
		return 0;
	if(in_range(l,r,L,R))
		return t[root].val;
	return GCD(query(lchild,l,mid,L,R),query(rchild,mid + 1,r,L,R));
}

int lowbit(int x){
	return x & (-x);
}

int sum(int x){
	int ret = 0;
	for(int i = x;i;i -= lowbit(i))
		ret += c[i];
	return ret;
}

void add(int x,int y){
	for(int i = x;i <= n;i += lowbit(i))
		c[i] += y;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = a[i] - a[i - 1];
		add(i,b[i]);
	}
	build(1,1,n);
	while(m--){
		cin >> op >> l >> r;
		if(op == "C"){
			cin >> d;
			update(1,1,n,l,d);
			update(1,1,n,r + 1,-d);
			add(l,d);
			add(r + 1,-d);
		}
		else
			cout << GCD(sum(l),query(1,1,n,l + 1,r)) << '\n';
	}
	return 0;
}
