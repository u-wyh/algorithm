#include <bits/stdc++.h>
using namespace std;
#define rnt register int
const int N=5e5+10;
int n,q;
string cyj;
struct hextree{  //线段树
	int col[N<<2],mark[N<<2];
	hextree(){memset(mark,-1,sizeof mark);}
	void pushup(rnt k){
		if(col[k<<1]==col[k<<1|1]){
			col[k]=col[k<<1];
		} else col[k]=-1;
	} void pushdown(rnt k){
		if(mark[k]!=-1){
			col[k<<1]=col[k<<1|1]=mark[k];
			mark[k<<1]=mark[k<<1|1]=mark[k];
			mark[k]=-1;
		}
	} void build(rnt l,rnt r,rnt k){
		if(l==r){
			col[k]=cyj[l-1]-'A'+1; //取1、2、3
			return;
		} rnt mid=(l+r)>>1;
		build(l,mid,k<<1);
		build(mid+1,r,k<<1|1);
		pushup(k);
	} void fix(rnt x,rnt y,rnt z,rnt l,rnt r,rnt k){
		if(x>r||y<l) return;
		if(x<=l&&r<=y){
			col[k]=mark[k]=z; //别忘加pushdown
			return;
		} pushdown(k);
		rnt mid=(l+r)>>1;
		fix(x,y,z,l,mid,k<<1);
		fix(x,y,z,mid+1,r,k<<1|1);
		pushup(k);
	} int draw(rnt x,rnt y,rnt l,rnt r,rnt k){
		/*
		0表示此区间并不询问。
		如果一个子区间不询问，返回另一个子区间的返回值
		如果有一个区间混色，返回混色
		如果两个子区间同色，返回此色
		否则，返回混色
		*/
		if(x>r||y<l) return 0;
		if(x<=l&&r<=y) return col[k];
		pushdown(k);
		rnt mid=(l+r)>>1,L,R;
		L=draw(x,y,l,mid,k<<1);
		R=draw(x,y,mid+1,r,k<<1|1);
		if(L==0) return R;
		if(R==0) return L;
		if(L==-1||R==-1) return -1;
		if(L==R) return L;
		return -1;
	}
}tree;
int main(){
	scanf("%d",&n);
	cin>>cyj;
	scanf("%d",&q);
	tree.build(1,n,1);
	while(q--){
		int x,y;
		char sign,op;
		scanf(" %c ",&sign);
		if(sign=='A'){
			scanf("%d%d %c",&x,&y,&op);
//			printf("x=%d y=%d op=%c\n",x,y,op);
			tree.fix(x,y,op-'A'+1,1,n,1);
		} else {
			scanf("%d%d",&x,&y);
			int L=tree.draw(x-1,x-1,1,n,1),
			R=tree.draw(y+1,y+1,1,n,1);
//			printf("L=%d R=%d\n",L,R);
			//如果区间左边没矿，右边没矿或左右边不同矿
			//并且中间是同一种矿，就符合要求
			if(tree.draw(x,y,1,n,1)!=-1
			&&(L!=R||!L||!R)) puts("Yes");
			else puts("No"); //看清大小写
		}
	}
	return 0;
}
