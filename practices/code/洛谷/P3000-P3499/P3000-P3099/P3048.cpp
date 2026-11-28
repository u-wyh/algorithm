// https://www.luogu.com.cn/problem/P3048
// 题意：输入正整数 N 和 K。
// 考虑所有首位为 '1' 且二进制表示中恰好包含 K 个 '1' 的正整数，
// 将它们按数值严格递增排序。
// 求出排在第 N 位的那个二进制数。
// 输出一行一个二进制数（不含前导零），表示第 N 个编号。
// 数据范围：对于 100% 的数据，1 <= N <= 10^7，
// 1 <= K <= 10。
// 难度评分：1300（洛谷分级换算）
// 算法标签：组合数学、递推
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,k;
int comb[1005][15];
int pos[15];

int ans[MAXN];
signed main()
{
    cin>>k>>n;
    if(n==1){
        cout<<1;
        for(int i=1;i<k;i++){
            cout<<0;
        }
        return 0;
    }
    comb[0][0]=1;
    comb[1][0]=1;
    comb[1][1]=1;
    for(int i=2;i<=1000;i++){
        comb[i][0]=1;
        if(i<=n) comb[i][i]=1;
        for(int j=1;j<=min(i-1,n);j++){
            comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
        }
    }
    for(int i=n;i>=1;i--){
        bool flag=false;
        for(int j=i;j;j++){
            if(comb[j-1][i-1]>k){
                pos[i]=j;
                // cout<<i<<' '<<pos[i]<<' '<<k<<' '<<comb[j-1][i-1]<<endl;
                break;
            }
            k-=comb[j-1][i-1];
            if(k==0){
                flag=true;
                for(int k=i;k>=1;k--){
                    pos[k]=j--;
                    // cout<<k<<' '<<pos[k]<<endl;
                }
                break;
            }
        }
        if(flag){
            break;
        }
    }
    for(int i=1;i<=n;i++){
        ans[pos[i]]=1;
    }
    for(int i=pos[n];i>=1;i--){
        cout<<ans[i];
    }
    return 0;
}