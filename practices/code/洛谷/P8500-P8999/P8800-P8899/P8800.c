// https://www.luogu.com.cn/problem/P8800
// 题意：输入正整数 n, m，第 i 种卡牌现有数量 a_1..a_n，
// 以及第 i 种卡牌最多手写补充的上限 b_1..b_n；
// 共有 m 张空白牌可任意写成各牌种（每张最多写 b_i 张），
// 每套牌需要 1..n 各 1 张，输出最多能凑出多少套牌。
// 数据范围：
// 1 <= n <= 2*10^5，a_i,
// b_i <= n，m <= n^2（a_i, b_i 为正整数）。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

bool judge(int limit,int *a,int *b,int n,long long m){
    for(int i=1;i<=n;i++){
        if((limit-a[i]>b[i])||(limit-a[i]>m)||m<0)
            return false;
        else if(a[i]>=limit){
            continue;
        } else {
            m-=(limit-a[i]);
        }
    }
    return true;
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    int a[n+1],b[n+1],l=1e9,r=-1,mid,ans;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        l=min(l,a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        r=max(r,a[i]+b[i]);
    }
    while(l<=r){
        mid=l+((r-l)>>1);
        if(judge(mid,a,b,n,m)){
            ans=mid;
            l=mid+1;
        } else {
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
