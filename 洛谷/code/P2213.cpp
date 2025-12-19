#include<cstdio>
#include<algorithm>
#define maxn 2005
using namespace std;
int N,K,ans,mp[maxn][maxn],F[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-')f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	N=read(),K=read();
	for (int i=1;i<=N;i++)
	for (int j=1;j<=N;j++) mp[i+j-1][N-i+j]=read();
	for (int i=1;i<2*N;i++)
	for (int j=1;j<2*N;j++) F[i][j]=F[i-1][j]+F[i][j-1]-F[i-1][j-1]+mp[i][j];
	for (int i=1;i<=N;i++)
	for (int j=1;j<=N;j++){
		int now_x=i+j-1,now_y=N-i+j;
		int x_l=max(0,now_x-K-1),y_l=max(0,now_y-K-1),x_r=min(2*N-1,now_x+K),y_r=min(2*N-1,now_y+K);
		ans=max(ans,F[x_r][y_r]-F[x_l][y_r]-F[x_r][y_l]+F[x_l][y_l]);
	}
	printf("%d\n",ans);
	return 0;
}
