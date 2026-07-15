#include<bits/stdc++.h>
using namespace std;

struct hzy{
	int x,y,z;
}a[200001];
int f[200001],n,m,b[200001],l;

int find(int k){//并查集函数，注意路径压缩
	return f[k]==k?k:f[k]=find(f[k]);
}
void un(int x,int y){//合并函数
	int x1=find(x);
	int x2=find(y);
	if(x1!=x2){
		f[x1]=x2;
	}
}
int main() {
	cin>>n>>m;
	string ch;
	for(int i=1; i<=m; i++) {
		cin>>a[i].x>>a[i].y>>ch;
		a[i].x--;//方便后面运算，这里直接减1
		if(ch[0]=='o') {//相同和不同要搞清楚
			a[i].z=1;
		} else {
			a[i].z=0;
		}
		b[++l]=a[i].x;
		b[++l]=a[i].y;
	}
	sort(b+1,b+l+1);
	l=unique(b+1,b+l+1)-b-1;
	for(int i=1;i<=l*2;i++){
		f[i]=i;
	}
	for(int i=1; i<=m; i++) {
		a[i].x=lower_bound(b+1,b+l+1,a[i].x)-b;//离散化
		a[i].y=lower_bound(b+1,b+l+1,a[i].y)-b;
		if(a[i].z==0){//种类并查集，分相同和不同操作
			if(find(a[i].x)==find(a[i].y+l)){//如果两个数奇偶性不同，矛盾，输出
				cout<<i-1;
				return 0;
			}
			else{//不然就合并集合
				un(a[i].x,a[i].y);
				un(a[i].x+l,a[i].y+l);
			}
		}
		else{
			if(find(a[i].x)==find(a[i].y)){//同理
				cout<<i-1;
				return 0;
			}
			else{
				un(a[i].x,a[i].y+l);
				un(a[i].x+l,a[i].y);
			}
		}
	}
	cout<<m;
	return 0;
}
