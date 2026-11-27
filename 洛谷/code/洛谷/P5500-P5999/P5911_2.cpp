// https://www.luogu.com.cn/problem/P5911
// 题意：桥最大承重为 W，有 n 个队员各有过桥时间 t_i 和重量 w_i；
// 队伍需分批过桥
// （每批总重 <= W，耗时取该批最大 t_i，整批通过后下一批再上），
// 求最短总时间。
// 输入 W, n 及每人的 (t, w)；输出最少总过桥时间。
// 数据范围：100 <= W <= 400，1 <= n <= 16，
// 1 <= t <= 50，10 <= w <= 100。
// 算法标签：状态压缩动态规划、记忆化搜索
#include<bits/stdc++.h>
using namespace std;

int n,limit;
struct node{
    int t,w;
    int i;
}nums[16];
int dp[1<<16][16];

int dfs(int *w,int *t,int status,int index){
    if(index==n){
        return 0;
    }
    if(status==0){
        return 0;
    }
    if(dp[status][index]){
        return dp[status][index];
    }
    if((status&(1<<index))==0){
        return dfs(w,t,status,index+1);
    }
    int ans=INT_MAX;
    for(int j=status;j>0;j=(j-1)&status){
        if((j&(1<<index))==0&&w[j]<=limit){
            ans=min(ans,t[j]+dfs(w,t,status^j,index+1));
        }
    }
    dp[status][index]=ans;
    return ans;
}

int main()
{
    cin>>limit>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].t>>nums[i].w;
        nums[i].i=i;
    }
    int w[1<<n],t[1<<n];
    for(int i=0;i<(1<<n);i++){
        w[i]=0;
        t[i]=0;
    }
    for (int i = 0, W, T, h; i < n; i++) {
        W = nums[i].w;
        T = nums[i].t;
        h = 1 << i;
        for (int j = 0; j < h; j++) {
            w[h | j] = w[j] + W;
            t[h | j] = max(t[j] , T);
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=0;
        }
        cout<<w[i]<<' '<<t[i]<<endl;
    }
    cout<<dfs(w,t,(1<<n)-1,0);
    return 0;
}

