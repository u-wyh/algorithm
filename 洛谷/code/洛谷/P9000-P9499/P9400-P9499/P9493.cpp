// https://www.luogu.com.cn/problem/P9493
// 题意：多组数据（共 T 组）。
// 每组给定 n 和序列 L_0..L_{n-1}，
// 求有多少个 0~(n-1) 的排列 p，使得对每个 i ∈ [0, n-1]
// p 中都存在至少一个长度为 L_i 的连续子段 [l, r]，
// 其 mex 值恰好等于 i。
// 结果对 998244353 取模。
// 题意：第一行输入 T，每组输入 n 和 L_0..L_{n-1}；
// 输出 T 行整数。
// 数据范围：1 <= T <= 10，1 <= n <= 5 * 10^3，
// 1 <= L_i <= n。
// 算法标签：区间动态规划、滚动数组
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 5e3+5;

int n;
int nums[MAXN];
int f[MAXN];
int g[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        for(int i=1;i<=n;i++){
            f[i]=(i>nums[1]||n-i>=nums[1]);
        }
        for(int len=2;len<=n;len++){
            for(int i=1;i<=n;i++){
                g[i]=f[i];
            }
            for(int l=1,r=len;r<=n;l++,r++){
                f[l]=((n-l>=nums[len])&&(nums[len]>=len-1))*g[l+1]+((r>nums[len])&&(nums[len]>=len-1))*g[l];
                f[l]%=MOD;
            }
        }
        cout<<f[1]<<endl;
        // for(int i=1;i<=n;i++){
        //     f[i][i]=(i>nums[1]||n-i>=nums[1]);
        // }
        // for(int len=2;len<=n;len++){
        //     for(int l=1,r=len;r<=n;l++,r++){
        //         f[l][r]=((n-l>=nums[len])&&(nums[len]>=len-1))*f[l+1][r]+((r>nums[len])&&(nums[len]>=len-1))*f[l][r-1];
        //         f[l][r]%=MOD;
        //     }
        // }
        // cout<<f[1][n]<<endl;
    }
    return 0;
}