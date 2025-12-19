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
