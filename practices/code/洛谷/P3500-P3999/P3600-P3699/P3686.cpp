// https://www.luogu.com.cn/problem/P3686
// 题意：输入城市数 n、演出场数 d，
// 巡演城市序列 a_1..a_d（相邻不同且 a_1 = a_d）
// 以及 m 种机票 (s_i, d_i, t_i, p_i)。
// t_i='O' 为单程票（s_i -> d_i 一次，票价 p_i）；
// t_i='R' 为双程票
// （需先 s_i -> d_i 再 d_i -> s_i，
// 也可只飞去不返回，票价 p_i），
// 每种票不限量。
// 输出按顺序飞完 a_1 -> a_2 -> ... -> a_d
// 的最小总机票花费（保证有解）。
// 数据范围：2 <= n, d <= 3*10^5，
// 3 <= m <= 3*10^5，
// 1 <= p_i <= 10^9，s_i != d_i。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、哈希表
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 3e5+5;
const int INF = 1e15;

int n,d,m,n1,n2;
unordered_map<int,int>cost;
int nums[MAXN];
int dp[MAXN];//表示到达第i个城市的最小代价

inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

signed main()
{
    n=read(),d=read();
    n1=n+1,n2=(n+1)*(n+1);
    for(int i=1;i<=d;i++){
        nums[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        char op;
        u=read(),v=read();
        cin>>op;
        w=read();
        int k=(op=='R')?1:0;
        k=k*n2+u*n1+v;
        int tmp=cost[k];
        if(tmp==0){
            cost[k]=w;
        }
        else{
            cost[k]=min(w,tmp);
        }

        if(op=='R'){
            k=v*n1+u;
            tmp=cost[k];
            if(tmp==0){
                cost[k]=w;
            }
            else{
                cost[k]=min(w,tmp);
            }
        }
        // cout<<' '<<k<<' '<<cost[k]<<endl;
    }

    dp[1]=0;
    for(int i=2;i<=d;i++){
        dp[i]=INF;

        int u=nums[i-1],v=nums[i];
        int c1=cost[u*n1+v];
        int c2=cost[n2+u*n1+v];
        if(c1||c2){
            if(c1==0){
                dp[i]=min(dp[i],dp[i-1]+c2);
            }
            else if(c2==0){
                dp[i]=min(dp[i],dp[i-1]+c1);
            }
            else{
                dp[i]=min(dp[i],dp[i-1]+min(c1,c2));
            }
        }

        if(nums[i-2]!=v){
            continue;
        }
        c2=cost[n2+v*n1+u];
        if(c2==0){
            continue;
        }
        dp[i]=min(dp[i],dp[i-2]+c2);
    }
    cout<<dp[d]<<endl;
    return 0;
}