// https://www.luogu.com.cn/problem/P11293
// 题意：在 n 行 m 列的棋盘上选同一行的一段和同一列的一段，让两段共用一个端点作为拐角。
// 计算两段覆盖的格子和，拐角只算一次。
// 求最大值，任意一段都可以只有拐角一个格。
// 数据范围：1 ≤ n,m ≤ 1000，-10^9 ≤ A[i][j] ≤ 10^9。
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[1005][1005];
long long up[1005][1005],dn[1005][1005],le[1005][1005],ri[1005][1005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            le[i][j]=ri[i][j]=up[i][j]=dn[i][j]=nums[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(le[i][j-1]>=0)
                le[i][j]+=le[i][j-1];
        }
        for(int j=m;j>=1;j--){
            if(ri[i][j+1]>=0)
                ri[i][j]+=ri[i][j+1];
        }
    }
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            if(dn[i-1][j]>=0){
                dn[i][j]+=dn[i-1][j];
            }
        }
        for(int i=n;i>=1;i--){
            if(up[i+1][j]>=0){
                up[i][j]+=up[i+1][j];
            }
        }
    }
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<i<<" "<<j<<"  :"<<le[i][j]<<' '<<ri[i][j]<<' '<<up[i][j]<<' '<<dn[i][j]<<endl;
//        }
//    }
    long long ans=LLONG_MIN;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans=max(ans,max(up[i][j],dn[i][j])+max(le[i][j],ri[i][j])-nums[i][j]);
        }
    }
    cout<<ans;
    return 0;
}
