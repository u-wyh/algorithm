#include<iostream>
#include<cmath>
#define int long long//记得开long long
using namespace std;
const int szl=8e5+5;
int sgt[szl][2][2];//第一维是线段树节点编号，第二位表示左端点状态，第三位表示由端点状态，0表示不选，1表示选
int a[szl],d[szl],root=1;
void Updata(int p,int mid){
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			if(d[mid]*d[mid+1]>=0)sgt[p][i][j]=sgt[p<<1][i][1]+sgt[p<<1|1][1][j];//可以合并成一个区间
			else sgt[p][i][j]=max(sgt[p<<1][i][0]+sgt[p<<1|1][1][j],sgt[p<<1][i][1]+sgt[p<<1|1][0][j]); //不能合并成一个区间
	return;
}
void Add(int p,int l,int r,int pos){
	if(l==r){
		sgt[p][1][1]=abs(d[l]);
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid)Add(p<<1,l,mid,pos);
	else Add(p<<1|1,mid+1,r,pos);
	Updata(p,mid);
	return;
}

signed main(){
	int n,q;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		d[i]=a[i]-a[i-1];
		if(i==1)continue;
		Add(root,2,n,i);
		//也可以写在外面O(N)建树，但这样写慢却简单，少些一个函数，反正不会超时，减少错误率
		//注意：差分数组从2到n的区间才有效 。
	}
	cout<<tree[1][1][1]<<endl;
//	while(q--){
//		int l,r,x;cin>>l>>r>>x;
//		if(l>1){
//			d[l]+=x;
//			Add(root,2,n,l);
//		}
//		if(r<n){
//			d[r+1]-=x;
//			Add(root,2,n,r+1);
//		}
//		cout<<sgt[root][1][1]<<endl;//最后直接输出，不用比较左右端点不选的情况
//	}
	return 0;
}
