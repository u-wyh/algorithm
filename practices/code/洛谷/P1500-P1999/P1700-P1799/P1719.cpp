// https://www.luogu.com.cn/problem/P1719
// 题意：给定 n 行 n 列的整数矩阵，选一个非空的连续子矩形，
// 求其中所有元素的和最大是多少。
// 数据范围：1 ≤ n ≤ 120，矩阵元素在 [−127,127]。
// 算法标签：前缀和、枚举

#include<bits/stdc++.h>
using namespace std;
const int MAXN=130;

int n;
int nums[MAXN][MAXN],sum[MAXN][MAXN];

int fun(int X1,int Y1,int X2,int Y2){
    return sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2];
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+nums[i][j];
        }
    }
    int ans=-1e9;
    for(int X1=1;X1<=n;X1++){
        for(int Y1=1;Y1<=n;Y1++){
            for(int X2=X1;X2<=n;X2++){
                for(int Y2=Y1;Y2<=n;Y2++){
                    ans=max(ans,fun(X1,Y1,X2,Y2));
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
