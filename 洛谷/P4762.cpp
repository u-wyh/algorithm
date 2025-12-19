#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9;

int n;

int dp[MAXN];
char s[MAXN];

int tree[MAXN][4];
int len[MAXN];
int fail[MAXN];
int fa[MAXN];
int half[MAXN];
int cnt;
int last;

void init(){
    cnt=1;
    last=0;
    len[0]=0,len[1]=-1;
    fail[0]=1;//偶根节点的fail指针指向奇根
    fail[1]=1;
    s[0]='#';// 特殊字符，防止越界
    half[0]=0,half[1]=1;
}

// 在fail链上查找满足条件的节点  即回文串前面一个字母是t[i]的位置  最大的位置
int getfail(int p,int i){
    while(s[i-len[p]-1]!=s[i]){
        p=fail[p];
    }
    return p;
}

// 添加字符t[i]到回文自动机
void insert(int i){
    int c;
    if(s[i]=='A'){
        c=0;
    }
    else if(s[i]=='T'){
        c=1;
    }
    else if(s[i]=='G'){
        c=2;
    }
    else{
        c=3;
    }
    // 查找合适的节点  其实这里找的是一个类似于父亲节点
    int cur=getfail(last,i);

    // 如果该节点不存在，创建新节点
    if(!tree[cur][c]){
        int x=++cnt;
        len[x]=len[cur]+2;

        int p=getfail(fail[cur],i);
        fail[x]=tree[p][c];

        if(len[x]<=1){
            half[x]=0;
        }
        else{
            int v=half[cur];
            while(len[v]+2>len[x]/2||s[i-len[v]-2]!=s[i]){
                v=fail[v];
            }
            half[x]=tree[x][c];
        }

        tree[cur][c]=x;
        fa[x]=cur;
    }
    last=tree[cur][c];
}

void compute(){
    for(int i=1;i<=cnt;i++){
        dp[i]=INF;
    }
    dp[0]=0;
    for(int i=0;i<3;i++){
        dp[tree[0][i]]=2;
    }
    for(int i=2;i<=cnt;i++){
        if(len[i]%2==1||len[i]<=2){
            continue;
        }
        if(len[fa[i]]%2==0){
            dp[i]=min(dp[i],dp[fa[i]]+1);
        }
        if(len[half[i]]%2==0){
            dp[i]=min(dp[i],dp[half[i]]+len[i]/2-len[half[i]]+1);
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        init();
        n=strlen(s+1);
        for(int i=1;i<=n;i++){
            insert(i);
        }
        compute();
        int ans=INF;
        for(int i=1;i<=cnt;i++){
            if(len[i]%2==0){
                ans=min(ans,n-len[i]+dp[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}