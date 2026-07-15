#include<bits/stdc++.h>
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