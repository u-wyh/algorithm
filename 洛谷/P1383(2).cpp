#include<bits/stdc++.h>
#define ri register int
#define int long long
#define lc tree[p].l
#define rc tree[p].r
//懒人砖用表示法
using namespace std;
int m,cnt=1,node;
//cnt表示节点个数，node表示根节点个数
int root[10000001];
struct node{
	int l;
	int r;
	char data;
	int size;
}tree[10000001*4];
//如上
void change(int &p,int pre,int l,int r,char x){
	p=++cnt;
	lc=tree[pre].l;
	rc=tree[pre].r;
	tree[p].size=tree[pre].size;
	tree[p].data=tree[pre].data;
  //先开点，继承上一个根节点
	if(l>r) return;
	if(l==r){
		tree[p].data=x;
		tree[p].size=1;
		return;
	}
	if(tree[lc].size==((l+r)>>1)-l+1) change(rc,tree[pre].r,(l+r)>>1+1,r,x);
	else change(lc,tree[pre].l,l,(l+r)>>1,x);
  //同上
	tree[p].size=tree[lc].size+tree[rc].size;//当前子树的节点总数为左子树加上右子树
}
char ask(int p,int l,int r,int x){
	if(l>=r){
		return tree[p].data;
	}
	if(x<=tree[lc].size){//如果要访问的叶子节点编号小于左子树的节点总数，那么ta肯定在左子树，反之在右子树
		return ask(lc,l,(l+r)>>1,x);
	}else{
		return ask(rc,(l+r)>>1+1,r,x-tree[lc].size);
	}
}
signed main(){
	cin>>m;
	for(ri i=1;i<=m;i++){
		char o,c;
		int x;
		cin>>o;
		if(o=='T'){
			cin>>c;
			++node;
			change(root[node],root[node-1],1,m,c);
		}
		if(o=='U'){
			cin>>x;
			++node;
			root[node]=root[node-x-1];
            //撤销直接新建根节点就行了
		}
		if(o=='Q'){
			cin>>x;
			cout<<ask(root[node],1,m,x)<<endl;
		}
	}
	return 0;
}
/*
9
T a
T b
T c
U 2
Q 1
T d
T e
U 3
Q 3
*/
