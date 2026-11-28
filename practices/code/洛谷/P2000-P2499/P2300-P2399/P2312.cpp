// https://www.luogu.com.cn/problem/P2312
// 题意：给定 n 次多项式系数 a_0..a_n，
// 求方程 a_0 + a_1*x + ... + a_n*x^n = 0 在
// [1,m] 内的整数解。
// 第一行输出解的个数，之后按从小到大每行输出一个解。
// 数据范围：0 < n <= 100，
// |a_i| <= 10^10000，a_n != 0，m < 10^6。
// 难度评分：1300（洛谷分级换算）
// 算法标签：秦九韶算法、数论取模、枚举
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n,m;
queue<int>q;
int arr[105];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',x%=MOD,ch=getchar();
    return x*f;
}

inline bool check(int x){
    int sum=0;
    for(int i=n;i>=1;i--){
        sum=((arr[i]+sum)*x)%MOD;
    }
    sum=(sum+arr[0])%MOD;
    return sum==0;
}

signed main()
{
    n=read(),m=read();
    for(int i=0;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=m;i++){
        if(check(i)){
            q.push(i);
        }
    }
    printf("%lld\n",(int)q.size());
    while(!q.empty()){
        printf("%lld\n",q.front());
        q.pop();
    }
    return 0;
}