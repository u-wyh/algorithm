#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000];
int f[1000][1000];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+m+1); //排序，有序的才能转移状态
    a[0]=0;a[m+1]=n+1; //假设0和n+1号牢房有人，方便后面的状态转移
    for(int l=1;l<=m;l++)  //枚举区间长度
        for(int i=1;i+l-1<=m;i++) //区间左端点位置
        {
            int j=i+l-1;  //区间右端点位置
            f[i][j]=999999999;
            for(int k=i;k<=j;k++)  //枚举分界点
                f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+a[j+1]-a[i-1]-1-1); //状态转移
        }
    printf("%d",f[1][m]);
}
