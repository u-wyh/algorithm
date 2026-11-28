// https://www.luogu.com.cn/problem/P1285
// 题意：有 n 个人，给出每个人的单向“认识”列表（不具对称性与传递性）。
// 题意：将所有人分成两个非空小组，使同组内任意两人互相认识，
// 且两组人数差的绝对值最小（SPJ）。
// 输入：第一行输入 n，
// 第 2..n+1 行每行若干互不相同的正整数 a_{i,j} 并以 0 结尾。
// 输出：无解输出 No solution；
// 有解输出两行，每行先输出组人数，再升序输出成员编号。
// 数据范围：2 <= n <= 100。
// 数据范围：1 <= a_{i,j} <= n。
// 难度评分：2200（洛谷分级换算）
// 算法标签：二分图、动态规划、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 1e4+5;

int n;
bool edge[MAXN][MAXN];

bool flag;

int block;
int belong[MAXN];
int col[MAXN];
int cnta[MAXN];
int cntb[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    if(belong[u]){
        return ;
    }
    belong[u]=block;
    for(int i=1;i<=n;i++){
        if(i!=u&&!(edge[u][i]&&edge[i][u])){
            addedge(u,i);
            dfs(i);
        }
    }
}

void check(int u,int c){
    if(col[u]&&col[u]!=c){
        flag=false;
    }
    if(col[u]){
        return ;
    }
    else{
        col[u]=c;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        check(v,c^1);
    }
}

bool dp[MAXN][MAXN];
int from[MAXN][MAXN];
int diff[MAXN];

int in[4][MAXN];

void compute(){
    dp[0][0]=true;
    for(int i=1;i<=block;i++){
        int k=abs(cnta[i]-cntb[i]);
        for(int j=0;j<=n;j++){
            if(j+k<=n&&dp[i-1][j+k]){
                dp[i][j]=true;
                from[i][j]=j+k;
            }
            if(j>=k){
                if(dp[i-1][j-k]){
                    dp[i][j]=true;
                    from[i][j]=j-k;
                }
            }
            else{
                if(dp[i-1][k-j]){
                    dp[i][j]=true;
                    from[i][j]=k-j;
                }
            }
        }
    }

    for(int i=0;i<=n;i++){
        if(dp[block][i]){
            diff[block]=i;
            break;
        }
    }
    for(int i=block;i>=1;i--){
        diff[i-1]=from[i][diff[i]];
    }

    int big=2;
    for(int i=1;i<=block;i++){
        int k=abs(cnta[i]-cntb[i]);
        int maxx=(cnta[i]>cntb[i])?2:3;

        if(diff[i]==diff[i-1]+k){
            in[maxx][i]=big;
            in[maxx^1][i]=big^1;
            continue;
        }
        if(diff[i]>=k){
            in[maxx][i]=big^1;
            in[maxx^1][i]=big;
            continue;
        }
        else{
            in[maxx][i]=big^1;
            in[maxx^1][i]=big;
            big^=1;
            continue;
        }
    }

    vector<int>lt;
    vector<int>rt;
    for(int i=1;i<=n;i++){
        if(in[col[i]][belong[i]]==2){
            lt.push_back(i);
        }
        else{
            rt.push_back(i);
        }
    }
    cout<<lt.size()<<' ';
    for(int i=0;i<lt.size();i++){
        cout<<lt[i]<<' ';
    }
    cout<<endl;
    cout<<rt.size()<<' ';
    for(int i=0;i<rt.size();i++){
        cout<<rt[i]<<' ';
    }
    cout<<endl;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int j;
        cin>>j;
        while(j){
            edge[i][j]=true;
            cin>>j;
        }
    }
    flag=true;

    for(int i=1;i<=n;i++){
        if(!belong[i]){
            ++block;
            dfs(i);
            check(i,2);
            // cout<<i<<endl;
        }
        if(!flag){
            cout<<"No solution"<<endl;
            return 0;
        }
    }

    for(int i=1;i<=n;i++){
        if(col[i]==2){
            cnta[belong[i]]++;
        }
        else{
            cntb[belong[i]]++;
        }
    }

    compute();
    return 0;
}