// https://www.luogu.com.cn/problem/P2797
// 题意：输入正整数 n，以及 n 个整数 x_1..x_n。
// 从这 n 个数中选出若干个数构成一个非空子集，使得这些数的平均数减去中位数的值最大。
// 计算这个差值的最大可能值。
// 输出一个精确到两位小数的实数，表示最大魔法差值。
// 数据范围：对于 100% 的数据，n <= 10^5（正整数），0 <= x_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：三分查找、前缀和、排序
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int sum[MAXN];
double ans=0;

double check(int pos,int len){
    double ans=1.0*(sum[n]-sum[n-len]+sum[pos]-sum[pos-len-1])/(2*len+1);
    return ans-nums[pos];
}

void compute(int pos,int len){
    int l=0,r=len;
    while(r-l>4){
        int midl=(r-l)/3+l;
        int midr=r-(r-l)/3;
        double k1=check(pos,midl);
        double k2=check(pos,midr);
        if(k1<k2){
            l=midl;
        }
        else{
            r=midr;
        }
    }
    for(int k=l;k<=r;k++){
        ans=max(ans,check(pos,k));
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++){
        sum[i]=nums[i]+sum[i-1];
    }
    for(int i=2;i<n;i++){
        compute(i,min(i-1,n-i));
    }
    printf("%.2lf\n",ans);
    return 0;
}