// https://www.luogu.com.cn/problem/P3874
// 题意：给出一棵 N 个节点的树，每个点 i 处有一个价值为 v_i、重量为 w_i 的水果。
// 选出原树中一个连通子图（包含至少 K 个节点），使得这些水果的平均价值（总价值除以总重量）最大，结果四舍五入保留两位小数。
// 数据范围：1 <= N <= 100，1 <= K <= N，1 <= v_i <= 10000，1 <= w_i <= 10000。
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool check(long long x,int *nums,int n){

}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    long long l=0,r=(n*n-n)/2,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
