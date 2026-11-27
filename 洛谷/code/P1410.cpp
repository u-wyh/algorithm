// https://www.luogu.com.cn/problem/P1410
// 题意：给一个长度为偶数的序列，判断能否把所有元素分到两个等长子序列。两边都保持原下标顺序，并且各自严格递增。有解输出 Yes!，否则输出 No!。
// 数据范围：每个测试点至多 50 行，N 为偶数且不超过 2000，输入数值在 [0,10^9]。
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int arr[MAXN];
int dp[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    while(scanf("%d",&n)==1){
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dp[i][j]=1e9;
            }
        }
        dp[1][1]=-1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                if(dp[i][j]!=1e9){
                    if(arr[i]<arr[i+1]){
                        dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
                    }
                    if(dp[i][j]<arr[i+1]){
                        dp[i+1][i+1-j]=min(arr[i],dp[i+1][i-j+1]);
                    }
                }
            }
        }
        if(dp[n][n/2]!=1e9){
            cout<<"Yes!"<<endl;
        }
        else{
            cout<<"No!"<<endl;
        }
    }
    return 0;
}
