// https://www.luogu.com.cn/problem/P3041
// 题意：输入组合技数量 n、输入串长度 k，以及 n 个仅由大写字母 A、B、C 构成的模式串 s_i。
// 构造一个长度为 k 的字符串 t（字符集为 A、B、C），s_i 每在 t 中作为连续子串出现一次便得 1 分（不同起始位置分别计分）。
// 求长度为 k 的字符串 t 最多能获得多少分。
// 输出一行一个整数，表示最大总得分。
// 数据范围：对于 100% 的数据，1 <= n <= 20，1 <= k <= 10^3，1 <= |s_i| <= 15。
#include<bits/stdc++.h>
// 算法标签：AC自动机、动态规划
using namespace std;
const int MAXN = 305;
const int MAXM = 1e3+5;
const int INF = 1e9;

int n,k;

int tree[MAXN][3];
int fail[MAXN];
int score[MAXN];
int cnt;

int dp[MAXM][MAXN];

void insert(string s){
    int cur=0;
    for(char ch:s){
        int path=ch-'A';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    score[cur]=1;
}

void setfail(){
    queue<int>q;
    for(int i=0;i<3;i++){
        if(tree[0][i]){
            q.push(tree[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<3;i++){
            if(tree[u][i]==0){
                tree[u][i]=tree[fail[u]][i];
            }
            else{
                fail[tree[u][i]]=tree[fail[u]][i];
                q.push(tree[u][i]);
            }
        }
        score[u]+=score[fail[u]];
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s);
    }
    setfail();
    for(int i=0;i<=k;i++){
        for(int j=0;j<=cnt;j++){
            dp[i][j]=-INF;
        }
    }
    dp[0][0]=0;
    for(int i=0;i<=k;i++){
        for(int j=0;j<=cnt;j++){
            if(dp[i][j]<0){
                continue;
            }
            for(int c=0;c<3;c++){
                int jj=tree[j][c];
                if(dp[i+1][jj]<dp[i][j]+score[jj]){
                    dp[i+1][jj]=dp[i][j]+score[jj];
                }
            }
        }
    }
    int ans=0;
    for(int j=0;j<=cnt;j++){
        ans=max(ans,dp[k][j]);
    }
    cout<<ans<<endl;
    return 0;
}