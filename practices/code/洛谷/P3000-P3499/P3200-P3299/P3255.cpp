// https://www.luogu.com.cn/problem/P3255
// 题意：输入山的数量 N，以及按编号 1..N 顺序给出的每座山的高度和关键数字。
// 将这 N 座山排成一排，要求对每座山，
// 排在它前面且比它高的山的数量严格小于它的关键数字（高度和编号均各不相同）。
// 输出两个用空格分隔的整数，
// 分别为不同的合法标号序列数与不同的合法等高线（高度）序列数对 2011
// 取模的结果。
// 数据范围：1 <= N <= 1000，
// 高度和关键数均为不超过 10^9 的正整数。
// 难度评分：2300（洛谷分级换算）
// 算法标签：动态规划、前缀和、排序
#include<bits/stdc++.h>
using namespace std;
const int MOD = 2011;
const int MAXN = 1005;

int n;
struct node{
    int val,key;
};
node nums[MAXN];

int dp[MAXN][MAXN];
int sum[MAXN];

bool cmp(node a,node b){
    if(a.val!=b.val){
        return a.val>b.val;
    }
    return a.key<b.key;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].val,&nums[i].key);
        nums[i].key--;
    }
    sort(nums+1,nums+n+1,cmp);

    int ans1=1;
    int p=0;
    for(int i=1;i<=n;i++){
        while(p+1<=n&&nums[p+1].val>nums[i].val){
            p++;
        }
        ans1=(ans1*(min(nums[i].key,p)+i-p))%MOD;
    }

    int ans2=1;
    p=0;

    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        while(p+1<=n&&nums[p+1].val>nums[i].val){
            p++;
        }

        for(int j=1;j<=n+1;j++){
            sum[j]=(sum[j-1]+dp[i-1][j])%MOD;
        }
        if(p==i-1){
            ans2=(ans2*sum[n+1])%MOD;
            for(int j=1;j<=n+1;j++){
                dp[i-1][j]=(j==1)?1:0;
                sum[j]=1;
            }
        }

        int pos=min(p,nums[i].key)+1;
        for(int j=1;j<=pos;j++){
            dp[i][j]=sum[j];
        }
        for(int j=pos+1;j<=n+1;j++){
            dp[i][j]=0;
        }
    }
    int res=0;
    for(int j=1;j<=n+1;j++){
        res=(res+dp[n][j])%MOD;
    }
    ans2=(ans2*res)%MOD;
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}