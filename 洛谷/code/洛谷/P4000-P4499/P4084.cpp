// https://www.luogu.com.cn/problem/P4084
// 题意：第一行输入谷仓数 N 和已涂色数 K；
// 接下来 N-1 行输入树的无向边 (x, y)；
// 最后 K 行每行输入谷仓 b 及其已涂颜色 c（共 3 种颜色）。
// 要求给其余未涂色谷仓涂上颜色 1~3 中的一种，
// 使得任意直接相连的两个谷仓颜色不同。
// 输出合法涂色方案数对 10^9 + 7 取模的结果。
// 数据范围：1 <= N <= 10^5，0 <= K <= N，
// 1 <= x, y <= N（x != y），1 <= b <= N
// 1 <= c <= 3。
// 算法标签：树形动态规划、深度优先搜索
#include<bits/stdc++.h>
#define maxn 200005
#define ll long long
using namespace std;
const int TT=1e9+7;
int n,x,y,lnk[maxn],nxt[maxn],son[maxn],tot,m;
ll f[maxn][3];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Dfs(int x,int fa){
	for (int i=0;i<3;i++){
		if (f[x][i]){for (int j=0;j<i;j++) f[x][j]=0;break;}
		f[x][i]=1;
	}
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa){
	  	Dfs(son[i],x);
	  	f[x][0]=f[x][0]*((f[son[i]][1]+f[son[i]][2])%TT)%TT;
                f[x][1]=f[x][1]*((f[son[i]][0]+f[son[i]][2])%TT)%TT;
                f[x][2]=f[x][2]*((f[son[i]][1]+f[son[i]][0])%TT)%TT;
	  }
}
int main(){
	n=read(),m=read();
	for (int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	for (int i=1;i<=m;i++) x=read(),y=read()-1,f[x][y]=1;
	Dfs(1,0);
	printf("%lld",(f[1][0]+f[1][1]+f[1][2])%TT);
	return 0;
}
