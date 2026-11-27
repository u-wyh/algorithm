// https://www.luogu.com.cn/problem/P3957
// 题意：直线上起点右侧有 n 个格子，第 i 个格子在位置 x_i（递增给出），
// 分数为 s_i。
// 机器人初始每次只能向右跳固定距离 d，
// 花费 g 金币可使
// 每次向右跳跃距离范围为 [max(1, d - g), d + g]。
// 随时可结束游戏，求获得总分至少为 k 所需花费的最少金币数 g，
// 不可能则输出 -1。
// 数据范围：1 <= n <= 5 * 10^5，
// 1 <= d <= 2 * 10^3，1 <= x_i, k <= 10^9，
// |s_i| < 10^5。
// 算法标签：二分答案、单调队列、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int INF = 1e15;

int n,d,k;
int pos[MAXN];
int val[MAXN];
int dp[MAXN];
int q[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool check(int limit){
    int l=max(1ll,d-limit);
    int r=d+limit;
    int h=0,t=0;
    for(int i=1;i<=n;i++){
        dp[i]=-INF;
    }
    dp[0]=0;
    int now=0;
    for(int i=1;i<=n;i++){
        while(now<i&&pos[i]-pos[now]>=l){
            while(h<t&&dp[now]>=dp[q[t]]){
                t--;
            }
            q[++t]=now;
            now++;
        }
        while(h<t&&pos[i]-pos[q[h+1]]>r){
            h++;
        }
        if(h<t)
            dp[i]=dp[q[h+1]]+val[i];
        if(dp[i]>=k){
            return true;
        }
    }
    return false;
}

signed main()
{
    n=read(),d=read(),k=read();
    int all=0;
    for(int i=1;i<=n;i++){
        pos[i]=read(),val[i]=read();
        if(val[i]>0){
            all+=val[i];
        }
    }
    if(all<k){
        cout<<-1<<endl;
        return 0;
    }
    pos[0]=0,val[0]=0;
    int l=0,r=1e9,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}