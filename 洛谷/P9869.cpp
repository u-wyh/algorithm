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
