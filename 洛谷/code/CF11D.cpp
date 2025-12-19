#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define inf 0x7fffffff
#define rg register int

using namespace std;

int n,m,t,u,v;
bool a[19][19]; //存边
ll ans,f[600001][19]; //状压

inline int qr(){ //快读
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	int res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		res=res*10+(ch^48);
	return res;
}

int main()
{
	n=qr(),m=qr();t=1<<n;
	for(rg i=1;i<=m;++i){
		u=qr()-1;v=qr()-1;
		a[u][v]=a[v][u]=1;//加边
	}
	for(rg i=0;i<n;++i)
		f[1<<i][i]=1; //初始化（创建以i为起点的路径）
	for(rg i=1;i<=t;++i){
		for(rg j=0;j<n;++j){
			if(!f[i][j])continue; //加速
			for(rg k=0;k<n;++k){
				if(!a[j][k])continue; //加速
				if((i&-i)>1<<k)continue; //起点不能改！！！（去重）
				if(1<<k&i){ //这个点走过
					if(1<<k==(i&-i)) //起点与终点相同
						ans+=f[i][j];
				}else f[i|1<<k][k]+=f[i][j]; //没走过就走！
			}
		}
	}printf("%lld",(ans-m)/2); //处理之后再输出！
	return 0;
}
