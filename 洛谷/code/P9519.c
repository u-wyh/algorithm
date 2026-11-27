// https://www.luogu.com.cn/problem/P9519
// 题意：n 名员工排成一排 1..n，第 i 人期望快乐值为 a_i。
// 现给其中 m 名指定员工 b_1..b_m 发 k 元工资。
// 所有员工中，每当距离为 d 的员工获得工资，该员工快乐值增加 max(0, k - d)（自身获工资则加 k）。
// 求使所有员工快乐值不低于各自期望的最小非负整数 k。
// 题意：第一行输入 n, m，第二行输入 a_1..a_n，第三行输入 b_1..b_m；输出一个整数。
// 数据范围：1 <= m <= n <= 10^6，0 <= a_i <= 10^9，1 <= b_i <= n 且 b_i 互不相同。
// 算法标签：二分答案、暴力枚举
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

#define MAX 1000000+5

int a[MAX],b[MAX],n,m,c[MAX];

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

bool check(int x){
    for(int i=1;i<=n;i++){
        c[i]=0;
    }
    for(int i=1;i<=m;i++){
        for(int j=max(b[i]-x+1,1);j<=min(b[i]+x-1,n);j++){
            c[j]+=(x-abs(j-b[i]));
        }
    }
    for(int i=1;i<=n;i++){
        if(c[i]<a[i])
            return false;
    }
    return true;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    int l=0,r=1e9,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
