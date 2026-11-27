// https://www.luogu.com.cn/problem/P10460
// 题意：每组给 N 个等差序列，参数 (S,E,D) 表示从 S 起每次加 D，保留不超过 E 的项。
// 保证最多只有一个位置出现奇数次。
// 若有就输出该位置和出现次数，否则输出 There's no weakness.。
// 数据范围：1 ≤ T ≤ 5，N ≤ 2 × 10^5，S ≤ E，三个参数均在 [0,2^31-1]，序列总项数不超过 10^8。
// 算法标签：二分查找、前缀和

#include<stdio.h>
#include<stdbool.h>

int max(int a,int b){
    return a>b?a:b;
}

bool check(int l,int r,int *sum){
    if((sum[r]-sum[l-1])%2==1)
        return true;
    return false;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int s[n+1],e[n+1],d[n+1],sum[n+1],l=1,r=0,mid;
        sum[0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&s[i],&e[i],&d[i]);
            r=max(r,e[i]);
            sum[i]=sum[i-1]+(e[i]-s[i]+1)/d[i];
        }
        if(sum[n]%2==0){
            printf("There's no weakness. \n");
            continue;
        }
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(l,mid,sum)){
                r=mid;
            }else{
                l=mid;
            }
        }
        printf("%d %d\n",l,mid);
    }
    return 0;
}
