#include<stdio.h>

int n,m,a,b,c,op;
int dp[2005];

int max(int A,int B)
{
    return A>B?A:B;
}

int main()
{
    scanf("%d %d",&n,&m);
    if(m==0)
    {
        printf("0\n");
        return 0;
    }
    while(n--)
    {
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d %d",&a,&b);
            for(int j = m; j >= 0; j--)
				for(int k = 1; k <= j; k++)
					dp[j] = max(dp[j], dp[j - k] + k * k * a - b * k);
        }
        if(op==2)
        {
            scanf("%d %d %d",&a,&b,&c);
            for(int j=m;j>=b;j--)
            {
                for(int k=1;k<=c&&k<=j/b;k++)
                {
                    dp[j]=max(dp[j],dp[j-k*b]+k*a);
                }
            }
        }
        if(op == 3)
		{
			scanf("%d %d", &a, &b);
			for(int j = b; j <= m; j++)
				dp[j] = max(dp[j], dp[j - b] + a);
		}
    }
    printf("%d\n",dp[m]);
    return 0;
}
