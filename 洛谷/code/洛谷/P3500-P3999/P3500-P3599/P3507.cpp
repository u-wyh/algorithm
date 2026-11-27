// https://www.luogu.com.cn/problem/P3507
// 题意：输入牌数 n，以及每张牌上的正整数 k_1..k_n。
// Alice 先手与 Bob 轮流取牌，每次至少取 1 张，
// 该轮得分等于本次所取牌中数字的最小值，直到取完；双方均最大化自己与对手的分差。
// 输出一个整数，表示双方最佳策略下 Alice 得分减去 Bob 得分的结果。
// 数据范围：1 <= n <= 10^6，1 <= k_i <= 10^9。
// 算法标签：动态规划、博弈论、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
//f[i]表示两人取完前i个数，先手减去后手的最大值，
//（这里先手后手是相对的，因为我们是倒序的，和实际取法是完全相反的，
//它实际上是处理出了1~i个数的情况下的最优解，A先从i开始往左边取，所以说考虑先手减后手最大值）
long long f[MAXN];

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
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;i++){
        f[i]=max(f[i-1],arr[i]-f[i-1]);
        //先手可以拿到i  或者多拿一个到i-1
    }
    cout<<f[n]<<endl;
    return 0;
}
