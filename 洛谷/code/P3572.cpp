// https://www.luogu.com.cn/problem/P3572
// 题意：输入树的数量 n、各树高度 d_1..d_n，询问数 q，以及每只鸟的最大单步跨度 k_i。
// 每只鸟从第 1 棵树走到第 n 棵树，每次从 j 飞到 j+1..j+k_i 中的某棵树；若目标树高度不低于当前树则劳累值加 1，否则不加。
// 输出 q 行，每行输出第 i 只鸟的最小劳累值。
// 数据范围：1 <= n <= 10^6，1 <= d_i <= 10^9，1 <= q <= 25，1 <= k_i <= n - 1。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int q[MAXN];
int dp[MAXN];
int n;
int arr[MAXN];
int m;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int k;
        cin>>k;
        int head=1,tail=2;
        q[head]=1;
        dp[1]=0;
        for(int i=2;i<=n;i++){
            while(head<tail&&q[head]+k<i){
                head++;
            }
            if(arr[i]<arr[q[head]]){
                dp[i]=dp[q[head]];
            }
            else{
                dp[i]=dp[q[head]]+1;
            }
            while(head<tail&&(dp[q[tail-1]]>dp[i]||(dp[q[tail-1]]==dp[i]&&arr[q[tail-1]]<=arr[i]))){
                tail--;
            }
            q[tail]=i;
            tail++;
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
