// https://www.luogu.com.cn/problem/P3847
// 题意：第一行输入队员数 n，
// 第二行输入 n 个整数表示从左到右每名队员衣服的颜色编号。
// 每次调整可进行以下任一操作：
// 在队伍最左/最右加一人、在任意两人中间插一人、踢掉一人、
// 或改变一人的衣服颜色（新颜色任意）。
// 求使队伍颜色序列变为左右对称（回文）的最少调整次数。
// 数据范围：1 <= n <= 3000，初始颜色为 1 到 3000 的整数。
// 算法标签：区间动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n;
int dp[MAXN][MAXN];
int arr[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        dp[i][i]=0;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            if(arr[i]==arr[j]){
                dp[i][j]=dp[i+1][j-1];
            }
            else{
                dp[i][j]=min(min(dp[i+1][j],dp[i][j-1]),dp[i+1][j-1])+1;
            }
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}
