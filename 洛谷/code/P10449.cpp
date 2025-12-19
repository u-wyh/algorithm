#include<bits/stdc++.h>
using namespace std;
const int N=7;
int ls[N][N];
int mapp[N][N];
int n;
bool flag;
int ans=INT_MAX;
int jsq;
void work(int i,int j)
{
	ls[i][j]^=1;
	ls[i+1][j]^=1;
	ls[i][j+1]^=1;
	if(i) ls[i-1][j]^=1;
	if(j) ls[i][j-1]^=1;
}
char c;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		for(int i=0;i<5;i++)
		    for(int j=0;j<5;j++)
		    {
		    	cin>>c;
		    	mapp[i][j]=c-'0';
		    }
		for(int i=0;i<32;i++)
		{
			for(int a=0;a<5;a++)
			    for(int b=0;b<5;b++)
			        ls[a][b]=mapp[a][b];
			jsq=0;
			for(int j=0;j<5;j++)
			    if((i>>j)&1) work(0,j),jsq++;
			for(int j=0;j<4;j++)
			    for(int k=0;k<5;k++)
			        if(ls[j][k]==0) work(j+1,k),jsq++;
			flag=1;
			for(int j=0;j<5;j++)
			    if(ls[4][j]==0)
			    {
			    	flag=0;
			    	break;
			    }
			if(flag) ans=min(ans,jsq);
		}
		if(ans<=6) printf("%d\n",ans);
		else printf("-1\n");
		ans=INT_MAX;
	}
	return 0;
}
