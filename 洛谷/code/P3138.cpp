#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define LL long long
#define INF 1e9
#define MOD 1000000007

const int L=1005;
struct node{
	LL int s,num;
};
node zx[L],zy[L];
bool cmp(const node &b,const node &c){
	return b.s<c.s;
}
LL int n,x[L],y[L],ans=INF,sum[L][L];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>zx[i].s,cin>>zy[i].s;
		zx[i].num=i;
		zy[i].num=i;
	}
	sort(zx+1,zx+n+1,cmp);
	sort(zy+1,zy+n+1,cmp);
	for(int i=1;i<=n;i++){
		x[zx[i].num]=i;
		y[zy[i].num]=i;
	}//离散化
	for(int i=1;i<=n;i++)
		sum[x[i]][y[i]]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//预处理部分
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=min(ans,max(max(sum[i][j],sum[i][n]-sum[i][j]),max(sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j])));//四个象限
	printf("%lld",ans);
	return 0;
}
