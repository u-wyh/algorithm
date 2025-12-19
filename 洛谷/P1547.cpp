#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int fa[200004];
int n,m,l,r,tot,ans,k;//tot是合并次数  最多n-1

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

struct node{
	int fir;//第一个点
	int sec;//第二个点
	int data;//边权
}edge[400005];

inline int find(int x){
	if(x==fa[x])return x;
	else return fa[x]=find(fa[x]);
}

inline bool cmp(node a,node b){
	return a.data<b.data;
}

inline void kruskal(){
	for(register int i=1;i<=m;i++){
		l=find(edge[i].fir);
		r=find(edge[i].sec);
		if(l==r)continue ;//如果联通就跳过
		fa[l]=r;//否则就合并
		k=edge[i].data;
		tot++;
		if(tot==n-1)break;
	}
}

int main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;i++)
        fa[i]=i;//初始化并查集
	for(register int i=1;i<=m;i++){
		edge[i].fir=read();
		edge[i].sec=read();
		edge[i].data=read();
	}
	sort(edge+1,edge+m+1,cmp);//将边权排序，每次加小的
	kruskal();
	cout<<k;//我喜欢cout...

	return 0;
}
