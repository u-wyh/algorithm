#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 3000
int n;//行数
int m;//列数
int s;//无人机数
int l;//任务数
int a[max_n+2][max_n+2];//矩阵
bool ans;//答案
int main(){
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	scanf("%d",&s);
	for(register int i=1,x1,y1,x2,y2;i<=s;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		++a[x1][y1];//左上
		++a[x2+1][y2+1];//右下
		--a[x2+1][y1];//左下
		--a[x1][y2+1];//右上
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			if(a[x][y])a[x][y]=1;
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	scanf("%d",&l);
	for(register int i=1,x1,y1,x2,y2;i<=l;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1]>=(x2-x1+1)*(y2-y1+1))puts("Yes");
		else puts("No");
	}
	return 0;
}
