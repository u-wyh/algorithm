// https://www.luogu.com.cn/problem/P2292
// 题意：给定包含 n 个单词的字典，随后有 m 段文章。
// 对每段文章，求能被字典中单词拼接理解的最长前缀长度。
// 每段文章输出一行最长前缀长度。
// 数据范围：1 <= n <= 20，1 <= m <= 50，单词长 <= 20，文章长 <= 2*10^6，均只含小写字母。
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