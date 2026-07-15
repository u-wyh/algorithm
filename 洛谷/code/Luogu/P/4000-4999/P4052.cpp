#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e3+5;
const int MOD = 1e4+7;

int n,m;

int cnt;
int tree[MAXN][26];
int fail[MAXN];
bool en[MAXN];

int dp[105][MAXN];

void insert(string s){
    int cur=0;
    for(char ch:s){
        int path=ch-'A';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[cur]=true;
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
        en[u]=en[u]||en[fail[u]];
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s);
    }
    setfail();
    dp[0][0]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=cnt;j++){
            if(dp[i][j]){
                for(int c=0;c<26;c++){
                    int jj=tree[j][c];
                    if(en[jj]){
                        continue;
                    }
                    dp[i+1][jj]=(dp[i+1][jj]+dp[i][j])%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=cnt;i++){
        ans=(ans+dp[m][i])%MOD;
    }
    int all=power(26,m);
    ans=(all-ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}