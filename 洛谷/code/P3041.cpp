#include<bits/stdc++.h>
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