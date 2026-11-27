// https://www.luogu.com.cn/problem/P3406
// 题意：输入城市数 N、行程城市数 M，依次经过的 M 个城市编号 P_1..P_M
// 以及 N-1 段铁路各自的纸质票价 A_i、IC 卡单次扣费 B_i 和 IC 卡工本费 C_i。
// 第 i 段铁路连接城市 i 与 i+1；
// 若未买第 i 段 IC 卡，每次经过需买 A_i 元纸质票，若花 C_i 元买卡后每次只需 B_i 元（B_i < A_i），工本费不退且不能跨段使用。
// 按 P_1 -> P_2 -> ... -> P_M 顺序往返各相邻段，求买票、买卡与充值的总最少花费。
// 输出一个整数，表示最少总花费。
// 数据范围：1 <= N, M <= 10^5，1 <= P_i <= N（相邻 P_i 不同），B_i < A_i
// A_i, B_i, C_i <= 10^5。
#include<bits/stdc++.h>
// 算法标签：差分、前缀和、贪心
using namespace std;

long long ans=0;
int n,m;
long long  nums[100005],a[100005],b[100005],c[100005],d[100005],cnt[100005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        cin>>a[i]>>b[i]>>c[i];
        d[i]=(c[i]+(a[i]-b[i]-1))/(a[i]-b[i]);
    }
    for(int i=1;i<m;i++){
        long  L=min(nums[i],nums[i+1]);
        long  R=max(nums[i],nums[i+1]);
        cnt[L]+=1;
        cnt[R]-=1;
    }
    for(int i=1;i<n;i++){
        cnt[i]+=cnt[i-1];
        if(cnt[i]>=d[i]){
            ans+=c[i]+cnt[i]*b[i];
        }else{
            ans+=a[i]*cnt[i];
        }
        //printf("%3d",cnt[i]);
    }
    //printf("\n");
    cout<<ans;
    return 0;
}
