// https://www.luogu.com.cn/problem/P4045
// 题意：第一行输入密码长度 L 和观察到的子串个数 N，接下来 N 行每行输入一个仅含小写字母的字符串。
// 统计长度为 L、仅由 a-z 小写字母组成且同时包含全部 N 个给定字符串作为子串的密码总数。
// 第一行输出总数；若总数 <= 42，则按字典序再输出全部可能密码，每行一个。
// 数据范围：对于 100% 的数据，1 <= L <= 25，1 <= N <= 10，每个给定字符串长度不超过 10，答案小于 2^{63}。
#include<bits/stdc++.h>
// 算法标签：AC自动机、状态压缩动态规划、深度优先搜索
using namespace std;
const int MAXS = 1<<10;
const int MAXN = 105;
const int MAXL = 26;

int len,n;

int cnt;
int tree[MAXN][26];
int fail[MAXN];
int st[MAXN];
vector<string>ans;
long long dp[MAXL][MAXN][MAXS];

void insert(int i,string s){
    int cur=0;
    for(char ch:s){
        int path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    st[cur]|=(1<<i);
}

void setfail(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(tree[0][i]){
            q.push(tree[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tree[u][i]==0){
                tree[u][i]=tree[fail[u]][i];
            }
            else{
                fail[tree[u][i]]=tree[fail[u]][i];
                q.push(tree[u][i]);
            }
        }
        st[u]|=st[fail[u]];
    }
}

void dfs(int i,int j,int k,string str,int sta){
    if(i==len){
        if(k==sta){
            ans.push_back(str);
        }
        return ;
    }
    for(int c=0;c<26;c++){
        int jj=tree[j][c];
        int kk=k|st[jj];
        if(dp[i+1][jj][kk]){
            dfs(i+1,jj,kk,str+char('a'+c),sta);
        }
    }

}

int main()
{
    cin>>len>>n;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        insert(i,s);
    }
    setfail();
    int status=(1<<n)-1;
    for(int j=0;j<=cnt;j++){
        dp[len][j][status]=1;
    }
    for(int i=len-1;i>=0;i--){
        for(int j=0;j<=cnt;j++){
            for(int k=0;k<=status;k++){
                for(int c=0;c<26;c++){
                    int jj=tree[j][c];
                    int kk=k|st[jj];
                    dp[i][j][k]+=dp[i+1][jj][kk];
                }
            }
        }
    }

    long long total=dp[0][0][0];
    cout<<total<<endl;
    if(total<=42&&total){
        dfs(0,0,0,"",status);
        for(string s:ans){
            cout<<s<<endl;
        }
    }
    return 0;
}