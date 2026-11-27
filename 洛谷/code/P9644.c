// https://www.luogu.com.cn/problem/P9644
// 题意：多组数据（共 T 组）。
// 有 n 盏灯排成一排，给定长度为 n 的 01 串表示初始亮灭（1 亮，0 灭，至少有一个 1）。
// 每次操作可将连续 L 盏灯全部关闭（长度为固定的正整数 L，覆盖 [i, i+L-1]）。
// 求能在 k 次操作内关掉所有灯的最小正整数 L。
// 题意：第一行输入 T，每组输入 n, k 及 01 串 s；每组输出一行一个整数。
// 数据范围：1 <= k <= n <= 2 * 10^5，sum(n) <= 2 * 10^6（未显式给出 T 上界，受 sum(n) 限制）。
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool check(int x,char *s,int n){
    int ans=0;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            ans++;
            for(int j=i;j<=i+x-1&&j<n;j++){
                s[j]='0';
            }
        }
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n,k;
        scanf("%d %d",&n,&k);
        char s[n+1];
        scanf("%s",s);
        //printf("%c %c\n",s[0],s[n-1]);
        int l=0,r=n,mid,ans;
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(mid,s,n)<=k){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
