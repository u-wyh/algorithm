#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 3e6+5;

int n;
char s[MAXN];

int cnt;
int tree[MAXM][26];
int en[MAXM];

int dp[MAXM];// dp[u] 表示以节点 u 为根的子树的最大值
//实际上 如果这个节点en[u]==0 那么dp实际上即使0
int ans;

//反向建立前缀树
void insert(char *s){
    int u=0;
    int len=strlen(s+1);
    for(int i=len;i>=1;i--){
        //反向插入
        int path=s[i]-'a';
        if(!tree[u][path]){
            tree[u][path]=++cnt;
        }
        u=tree[u][path];
    }
    en[u]++;
}

//dp[u]实际上表示的是u如果作为一个接口  最大可以是多少
//首先他应该是有最长的一个儿子maxx1  然后加上所有有效儿子节点个数-1（这里的减一是maxx1占据1个儿子）
//然后加上1 表示这个位置自己也要算
//为什么不加上maxx2  因为加上之后u就是中间位置 不能成为接口了
//但是加上所有有效儿子  不影响其继续作为接口
void dfs(int u){
    int sz=0;
    int maxx1=0,maxx2=0;
    for(int i=0;i<26;i++){
        int v=tree[u][i];
        if(v){
            dfs(v);
        }
        sz+=en[v];
        if(maxx1<dp[v]){
            maxx2=maxx1;
            maxx1=dp[v];
        }
        else if(maxx2<dp[v]){
            maxx2=dp[v];
        }
    }
    if(en[u]){
        dp[u]=maxx1+max(sz,1);//最好改成dp[u]=maxx1+1+max(sz-1,0);
    }
    ans=max(ans,maxx1+maxx2+en[u]+max(sz-2,0));
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        insert(s);
    }
    dfs(0);
    cout<<ans<<endl;
    return 0;
}
