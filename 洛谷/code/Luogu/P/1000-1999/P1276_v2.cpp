#include<iostream>
#include<cstring>
#include<cstdio>
#define lson o<<1
#define rson o<<1|1
#define mid ((l+r)>>1)
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=10005;

//tree[0]维护的是树，tree[1]维护的是树和树苗。
//tree[0].Ans,tree[1].Ans分别表示总共被砍掉的树/树与树苗的总数。
struct Segtree{
	int sum[maxn*4],ly[maxn*4],Ans;
	Segtree(){
		Ans=0;
		memset(ly,0,sizeof(ly));
		memset(sum,0,sizeof(sum));
	}
	void build(int o,int l,int r){
		if(l==r){
			sum[o]=1;
			return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		sum[o]=sum[lson]+sum[rson];
	}
	void down(int o,int l,int r){
		if(ly[o]==1){
			ly[lson]=1;
			ly[rson]=1;
			sum[lson]=mid-l+1;
			sum[rson]=r-mid;
		}
		if(ly[o]==-1){
			ly[lson]=-1;
			ly[rson]=-1;
			sum[lson]=0;
			sum[rson]=0;
		}
		ly[o]=0;
	}
	void zhong(int o,int l,int r,int L,int R){
		if(L<=l&&r<=R){
			ly[o]=1;
			sum[o]=r-l+1;
			return;
		}
		down(o,l,r);
		if(L<=mid)zhong(lson,l,mid,L,R);
		if(mid+1<=R)zhong(rson,mid+1,r,L,R);
		sum[o]=sum[lson]+sum[rson];
	}
	void cut(int o,int l,int r,int L,int R){
		if(L<=l&&r<=R){
			Ans+=sum[o];
			ly[o]=-1;
			sum[o]=0;
			return;
		}
		down(o,l,r);
		if(L<=mid)cut(lson,l,mid,L,R);
		if(mid+1<=R)cut(rson,mid+1,r,L,R);
		sum[o]=sum[lson]+sum[rson];
	}
}tree[2];

int n,m;
int main(){
	scanf("%d%d",&n,&m);
	n++;
	tree[0].build(1,1,n);
	tree[1].build(1,1,n);
	rep(i,1,m){
		int ops,l,r;
		scanf("%d%d%d",&ops,&l,&r);
		l++,r++;
		if(ops==0)tree[0].cut(1,1,n,l,r),tree[1].cut(1,1,n,l,r);
		if(ops==1)tree[0].zhong(1,1,n,l,r);
	}
	cout<<tree[0].sum[1]-tree[1].sum[1]<<endl;
	cout<<tree[0].Ans-tree[1].Ans;
	return 0;
}
