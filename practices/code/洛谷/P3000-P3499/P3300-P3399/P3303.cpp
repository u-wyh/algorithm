// https://www.luogu.com.cn/problem/P3303
// 题意：输入正整数 N 和采集次数 K，
// 初始在 [1..N]×[1..N] 每个整点各有一块金子。
// 位于 (i, j) 的金子会移动到 (f(i), f(j))，
// 其中 f(x) 为 x 各位数字之积；落到 [1..N] 范围外的金子被移除。
// 选择最多 K 个坐标采集，每次取走该坐标全部金子，
// 求最多能采集到的金子总数对 10^9+7 取模。
// 输出一个整数表示答案。
// 数据范围：N <= 10^12，K <= min(N^2, 10^5)。
// 难度评分：2200（洛谷分级换算）
// 算法标签：数位动态规划、优先队列、贪心
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e4+5;
const int MOD = 1e9+7;

int n,k;
int len;
int nums[15];
int nxt[MAXN];

int f[15][MAXN][2];

unordered_map<int,int>mp;
bool vis[15][MAXN];
int cnt;
int val[MAXN];
int t[MAXN];

struct cmp{
    bool operator()(const pair<int,int>a,const pair<int,int>b){
        return (1.0*t[a.first]/t[b.second])<(1.0*t[b.first]/t[a.second]);
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

bool compare(int a,int b){
    return a>b;
}

void init(int x,int now,bool free){
    if(x==0){
        if(!mp.count(now)){
            ++cnt;
            mp[now]=cnt;
            val[cnt]=now;
        }
        return ;
    }
    if(!mp.count(now)){
        ++cnt;
        mp[now]=cnt;
        val[cnt]=now;
    }
    if(vis[x][mp[now]]){
        return ;
    }
    vis[x][mp[now]]=true;
    int up=free?9:nums[x];
    for(int i=1;i<=up;i++){
        init(x-1,now*i,free||i<nums[x]);
    }
}

int dfs(int x,int now,bool free){
    if(x==0){
        return val[now]==1;
    }
    if(f[x][now][free]!=-1){
        return f[x][now][free];
    }
    int up=free?9:nums[x];
    int ans=0;
    for(int i=1;i<=up;i++){
        if(val[now]%i==0){
            int t=val[now]/i;
            if(mp.count(t)){
                ans+=dfs(x-1,mp[t],free||i<nums[x]);
            }
        }
    }
    f[x][now][free]=ans;
    return ans;
}

signed main()
{
    cin>>n>>k;
    len=0;
    while(n){
        nums[++len]=n%10;
        n/=10;
    }
    for(int i=2;i<=len+1;i++){
        init(i-1,1,i<len+1);
    }

    // cout<<cnt<<endl;
    // for(int i=1;i<=cnt;i++){
    //     cout<<val[i]<<' ';
    // }
    // cout<<endl;

    memset(f,-1,sizeof(f));
    for(int i=1;i<=cnt;i++){
        for(int j=2;j<=len+1;j++){
            t[i]+=dfs(j-1,i,j<len+1);
        }
        // cout<<i<<":  "<<t[i]<<endl;
    }
    sort(t+1,t+cnt+1,compare);
    for(int i=1;i<=cnt;i++){
        nxt[i]=1;
    }
    for(int i=1;i<=cnt;i++){
        heap.push({i,1});
    }
    int ans=0;
    while(k--&&!heap.empty()){
        pair<int,int>u=heap.top();
        // cout<<u.first<<' '<<u.second<<endl;
        heap.pop();
        ans=(ans+(t[u.first]%MOD)*(t[u.second]%MOD)%MOD)%MOD;
        if(nxt[u.first]<cnt){
            u.second=++nxt[u.first];
            heap.push(u);
        }
    }
    cout<<ans<<endl;
    return 0;
}