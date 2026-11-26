// https://www.luogu.com.cn/problem/P6549
// 题意：给定 1~n 的一个排列，每次只能将一本书抽出并放到序列最顶部，求将序列排成 (1, 2, ..., n) 所需的最少移动次数。
// 数据范围：1 <= n <= 3*10^5。
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int ans=n;
    for(int i=n;i>=1;i--){
        if(a[i]==ans){
            ans--;
        }
    }
    printf("%d\n",ans);
    return 0;
}
