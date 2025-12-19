#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;
const int MAXM = 2e6+5;

int n,m;
int len;

char s[MAXM];
bool dp[MAXM];

int tree[MAXN][26];
int fail[MAXN];
int en[MAXN];
int cnt;

void insert(){
    int cur=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        char ch=s[i];
        int path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[cur]=len;
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
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insert();
        len=max(len,(int)strlen(s));
    }
    setfail();
    while(m--){
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=0;i<=n;i++){
            dp[i]=false;
        }
        dp[0]=true;
        int cur=0;
        int ans=0;
        for(int i=1;i<=n;i++){
            if(ans+len<i){
                break;
            }
            cur=tree[cur][s[i]-'a'];
            for(int j=cur;j;j=fail[j]){
                dp[i]|=dp[i-en[j]];
                if(dp[i]){
                    break;
                }
            }
            if(dp[i]){
                ans=i;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}