#include<stdio.h>
#define Max 10

int nums[Max][Max];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            nums[i][j]=0;
        }
    }
    int i,j,k;
    while(scanf("%d %d %d",&i,&j,&k)==3)
    {
        nums[i][j]=k;
    }
    return 0;
}
