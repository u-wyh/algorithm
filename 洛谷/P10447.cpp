#include<bits/stdc++.h>
using namespace std;
const int MAXN=25,MAXM=(1<<20),inf=0x3f;//定义变量，inf为无限

int n,a[MAXN][MAXN],f[MAXM][MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	memset(f,inf,sizeof(f));
	f[1][0]=0;//还没开始旅程，为0
	for(int i=1;i<(1<<n);i++)//枚举状态
	{
		for(int j=0;j<n;j++)//枚举每个点
		{
			if(!((i>>j)&1)) continue;//经过了
			for(int k=0;k<n;k++)//上一次经过了哪些点？
				if(((i^(1<<j))>>k)&1)//枚举从上一个经过的节点走到j节点
					f[i][j]=min(f[i][j],f[i^(1<<j)][k]+a[k][j]);//状态转移
		}
	}
	printf("%d\n",f[(1<<n)-1][n-1]);//out
	return 0;
    //完结撒花
}
