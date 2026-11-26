// https://www.luogu.com.cn/problem/P10463
// 题意：给长为 N 的数组，执行 M 条指令。C l r d 给下标 l 到 r 全部加 d，Q l r 查询这些项的最大公约数。每条 Q 输出一个答案。
// 数据范围：N ≤ 5 × 10^5，M ≤ 10^5，1 ≤ a[i] ≤ 10^18，d 的绝对值不超过 10^18，计算过程在有符号 64 位整数范围内。

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pl (p<<1)
#define pr (p<<1|1)
const int N=5e5+10;
struct Tree{ll sum,gcd;}tr[N<<2];
int n,q,l,r;ll v,a[N];char op;
void push_up(int p){tr[p]={tr[pl].sum+tr[pr].sum,__gcd(tr[pl].gcd,tr[pr].gcd)};}//上放标记
void build(int l,int r,int p){//建树
	if(l==r)return tr[p]={a[l]-a[l-1],a[l]-a[l-1]},void();//将差分存进去
	int mid=l+r>>1;
	build(l,mid,pl),build(mid+1,r,pr),push_up(p);
}void update(int l,int r,int k,ll v,int p){//单点加
	if(l==r)return tr[p].sum+=v,tr[p].gcd+=v,void();
	int mid=l+r>>1;
	if(k<=mid)update(l,mid,k,v,pl);
	else update(mid+1,r,k,v,pr);
	push_up(p);
}ll query_sum(int l,int r,int le,int ri,int p){//区间和
	if(l>=le&r<=ri)return tr[p].sum;
	int mid=l+r>>1;ll ret=0;
	if(le<=mid)ret+=query_sum(l,mid,le,ri,pl);
	if(ri>mid)ret+=query_sum(mid+1,r,le,ri,pr);
	return ret;
}ll query_gcd(int l,int r,int le,int ri,int p){//区间最大公约数
	if(l>=le&r<=ri)return tr[p].gcd;
	int mid=l+r>>1;ll ret=0;
	if(le<=mid)ret=__gcd(ret,query_gcd(l,mid,le,ri,pl));
	if(ri>mid)ret=__gcd(ret,query_gcd(mid+1,r,le,ri,pr));
	return ret;
}int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,n,1);
	while(q--){
		cin>>op>>l>>r;
		if(op=='C')cin>>v,update(1,n,l,v,1),r!=n&&(update(1,n,r+1,-v,1),1);
		else cout<<abs(__gcd(query_gcd(1,n,l+1,r,1),query_sum(1,n,1,l,1)))<<'\n';//记得取绝对值
	}return 0;
}
