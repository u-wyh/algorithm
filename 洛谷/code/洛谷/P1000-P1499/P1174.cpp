// https://www.luogu.com.cn/problem/P1174
// 题意：有 n 行 m 列砖和 k 发初始子弹。
// 每次耗一发打掉任意一列当前最下面的砖，获得砖上的分数，
// 标 Y 的砖还会返还一发子弹。
// 砖全打掉或子弹用完就结束，求最高总得分。
// 数据范围：1 ≤ n,m,k ≤ 200，砖的分数在 [1,10000]，
// 奖励标记为 Y 或 N。
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n,m,k;

int arr[MAXN][MAXN];
int op[MAXN][MAXN];
int sum[MAXN][MAXN];
int f[MAXN][MAXN];

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            char c;
            cin>>c;
            if(c=='N'){
                op[i][j]=0;
            }
            else{
                op[i][j]=1;
            }
        }
    }
    for(int j=1;j<=m;j++){
        int u=n;
        while(op[u][j]&&u){
            sum[j][0]+=arr[u][j];
            u--;
        }
        for(int p=1;p<=k;p++){
            sum[j][p]=sum[j][p-1];
            if(u<=0){
                continue;
            }
            sum[j][p]+=arr[u][j];
            u--;
            while(op[u][j]&&u){
                sum[j][p]+=arr[u][j];
                u--;
            }
        }
    }
//    for(int j=1;j<=m;j++){
//        for(int p=0;p<=k;p++){
//            cout<<sum[j][p]<<' ';
//        }
//        cout<<endl;
//    }
    for(int j=1;j<=m;j++){
        f[j][0]=f[j-1][0]+sum[j][0];
        for(int p=1;p<=k;p++){
            f[j][p]=f[j-1][p]+sum[j][0];
            for(int q=1;q<=p;q++){
                f[j][p]=max(f[j][p],f[j-1][p-q]+sum[j][q]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=k;i++){
        ans=max(ans,f[m][i]);
    }
    cout<<ans<<endl;
    return 0;
}

