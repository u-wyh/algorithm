#include<stdio.h>
#include<string.h>
#define Max 105

int dp[Max][Max];
int d[6][6]=
{
	{0,0,0,0,0,0},
	{0,5,-1,-2,-1,-3},
	{0,-1,5,-3,-2,-4},
	{0,-2,-3,5,-2,-2},
	{0,-1,-2,-2,5,-1},
	{0,-3,-4,-2,-1,0}
};

int max(int a,int b)
{
    return a>b?a:b;
}

int  main()
{
    int m;
    scanf("%d",&m);
    getchar();
    char s;
    int a[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%c",&s);
        switch(s)
		{
            case'A':
                a[i]=1;break;
            case'C':
                a[i]=2;break;
            case'G':
                a[i]=3;break;
            case'T':
                a[i]=4;break;
		}
		//printf("%5d",a[i]);
    }
    //printf("\n");
    int n;
    scanf("%d",&n);
    getchar();
    char s2;
    int b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%c",&s2);
        switch(s2)
		{
            case'A':
                b[i]=1;break;
            case'C':
                b[i]=2;break;
            case'G':
                b[i]=3;break;
            case'T':
                b[i]=4;break;
		}
		//printf("%5d",b[i]);
    }
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
		dp[i][0]=dp[i-1][0]+d[a[i]][5];
	for(int i=1;i<=n;i++)
		dp[0][i]=dp[0][i-1]+d[5][b[i]];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=max(max(dp[i-1][j-1]+d[a[i]][b[j]],dp[i][j-1]+d[5][b[j]]),dp[i-1][j]+d[a[i]][5]);
        }
    }
    printf("%d\n",dp[m][n]);
    return 0;
}
