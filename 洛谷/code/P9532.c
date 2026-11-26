// https://www.luogu.com.cn/problem/P9532
// 题意：多组数据（共 T 组）。
// 长度为 n 的正整数数组 a 满足除 a_1 外每个元素都等于前面所有元素之和（即 a_2=a_1, a_3=2a_1, ..., a_k = 2^{k-2} a_1）。
// 已知整数 x 在数组 a 中出现过，求末尾元素 a_n 的最小可能值。
// 题意：第一行输入 T，接下来 T 行每行输入 n, x；输出 T 行答案。
// 数据范围：1 <= T <= 10^4，2 <= n <= 20，1 <= x <= 10^9。
#include<stdio.h>
#include<math.h>

int main()
{
    int a[21];
    a[0]=1;
    for(int i=1;i<=20;i++){
        a[i]=pow(2,i-1);
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        long long m,ans1;
        scanf("%d %lld",&n,&m);
        int l=0,r=n,mid=0,ans=0;
        while(l<=r){
            mid=(l+r)/2;
            if(m%a[mid]==0){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        //printf("%d\n",ans);
        ans1=a[n-ans]*m;
        printf("%lld\n",ans1);
    }
    return 0;
}
