// https://codeforces.com/problemset/problem/626/E
// 题意：长为 n 的非负整数序列 x，选一个非空子序列使其均值与中位数之差最大。
// 偶数项时，中位数取中间两项的平均值。
// 输出：第一行输出所选子序列长度，第二行输出其中元素。
// 数据范围：1 <= n <= 2*10^5，0 <= x_i <= 10^6。
// 难度评分：2400（CF 官方）
// 算法标签：三分搜索、前缀和、排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int nums[MAXN];
int sum[MAXN];
struct Score{
    int numerator, denominator;
};

Score ans={0,1};
int p,le;

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

Score check(int pos,int len){
    int count=2*len+1;
    int total=sum[n]-sum[n-len]+sum[pos]-sum[pos-len-1];
    return {total-count*nums[pos],count};
}

bool lessScore(Score a,Score b){
    return a.numerator*b.denominator<b.numerator*a.denominator;
}

void compute(int pos,int len){
    int l=0,r=len;
    while(r-l>4){
        int midl=(r-l)/3+l;
        int midr=r-(r-l)/3;
        Score k1=check(pos,midl);
        Score k2=check(pos,midr);
        if(lessScore(k1,k2)){
            l=midl;
        }
        else{
            r=midr;
        }
    }
    for(int k=l;k<=r;k++){
        Score res=check(pos,k);
        if(lessScore(ans,res)){
            ans=res;
            p=pos;
            le=k;
        }
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++){
        sum[i]=nums[i]+sum[i-1];
    }
    p=1,le=0;
    for(int i=1;i<=n;i++){
        compute(i,min(i-1,n-i));
    }
    printf("%lld\n",2*le+1);
    for(int i=p-le;i<=p;i++){
        cout<<nums[i]<<' ';
    }
    for(int i=n-le+1;i<=n;i++){
        cout<<nums[i]<<' ';
    }
    return 0;
}