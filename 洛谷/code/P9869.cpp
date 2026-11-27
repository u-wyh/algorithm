// https://www.luogu.com.cn/problem/P9869
// 题意：多组数据（首行测试点编号 c 及数据组数 t）。
// 每组有 n 个三值逻辑变量 x_1..x_n（取值 T/F/U
// ¬T=F, ¬F=T
// ¬U=U）及顺序执行的 m 条赋值语句：x_i <- v (v ∈ {T, F, U})、x_i <- x_j 或 x_i <- ¬x_j。
// 保证存在使执行后所有变量终值与初值相等的赋初值方案，求初值中 U 个数的最小值。
// 题意：首行输入 c, t，每组输入 n, m 及 m 条语句（v i 或 + i j 或 - i j）；每组输出一行一个整数。
// 数据范围：1 <= t <= 6，1 <= n, m <= 10^5，1 <= i, j <= n。
// 算法标签：并查集、深度优先搜索
#include<bits/stdc++.h>
#define afor(x,y,z) for(int x=y;x<=z;x++)
#define bfor(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
typedef const int cint;
cint N=100010;
int t,c,n,m,fa[N],siz[N],mp[N];
int find(int x) {//查找
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void Union(int x,int y) {//合并
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fy]=fx,siz[fx]+=siz[fy];
}
bool dfs(int x,int root,int flag) {//找这棵树中是否有根节点的反
	if(mp[x]/2==root) return flag^(mp[x]&1);
	return dfs(mp[x]/2,root,flag^(mp[x]&1));
}
#define True -1
#define False -2
#define Unknown -3
int opp(int x) {//数值的反
	if(x==True) return False;
	if(x==False) return True;
	if(x==Unknown) return Unknown;
	return x^1;
}
int main() {
	scanf("%d%d",&c,&t);
	while(t--) {
		int ans=0;
		scanf("%d%d",&n,&m);
		afor(i,1,n) mp[i]=i*2,fa[i]=i,siz[i]=1;
		afor(i,1,m) {
			char opt;
			int x,y;
			scanf(" %c",&opt);
			if(opt=='+') {
				scanf("%d%d",&x,&y);
				mp[x]=mp[y];//路径压缩
			}
			else if(opt=='-') {
				scanf("%d%d",&x,&y);
				mp[x]=opp(mp[y]);
			}
			else if(opt=='T') scanf("%d",&x),mp[x]=True;
			else if(opt=='F') scanf("%d",&x),mp[x]=False;
			else scanf("%d",&x),mp[x]=Unknown;
		}
		afor(i,1,n) if(mp[i]>0) Union(mp[i]/2,i);//连边，以赋值的元素为父亲
		afor(i,1,n) if(i==find(i)&&(mp[i]==Unknown||(mp[i]>0&&dfs(i,i,0))))
			ans+=siz[i];//满足是 Unknown 的条件就累加答案
		printf("%d\n",ans);
	}
	return 0;
}
