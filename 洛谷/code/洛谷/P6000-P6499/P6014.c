// https://www.luogu.com.cn/problem/P6014
// 题意：给定 n 张牌（点数 1~10），
// 若能挑出 n - 2 张牌使它们的和为 10 的倍数
// 则得分为另两张牌之和的个位数（若该和为 10 的倍数则得 10 分），
// 否则得 0 分；
// 求最终点数。
// 数据范围：5 <= n <= 10^6，牌面大小为 1~10。
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    int cnt[11];
    for(int i=0;i<11;i++){
        cnt[i]=0;
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
        sum+=a[i];
    }
    int ans=sum%10;
    if(ans==0){
        if(cnt[0]>=2||(cnt[1]&&cnt[9])||(cnt[2]&&cnt[8])||(cnt[3]&&cnt[7])||(cnt[4]&&cnt[6])||cnt[5]>=2){
            printf("%d\n",ans);
        }else{
            printf("0\n");
        }
    }else if(ans==1){
        if(cnt[0]>=2||(cnt[2]&&cnt[9])||(cnt[3]&&cnt[8])||(cnt[4]&&cnt[7])||(cnt[5]&&cnt[6])||cnt[5]>=2){
            printf("%d\n",ans);
        }else{
            printf("0\n");
        }
    }
    return 0;
}
