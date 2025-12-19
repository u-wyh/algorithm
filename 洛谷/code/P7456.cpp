#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int LIMIT = 20;
const int INF = 1e9;

int n;
char t[MAXN];
char s[MAXN];

int trie[MAXN][26];
int fail[MAXN];
int len[MAXN];
int cnt;

int st[MAXN][LIMIT];

void insert(){
    int cur=0;
    int m=strlen(t+1);
    for(int i=1;i<=m;i++){
        char ch=t[i];
        int path=ch-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
    len[cur]=max(len[cur],m);
}

void setfail(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        len[u]=max(len[u],len[fail[u]]);
        for(int i=0;i<26;i++){
            if(trie[u][i]==0){
                trie[u][i]=trie[fail[u]][i];
            }
            else{
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
        }
    }
}

int query(int l,int r){
    int p=log2(r-l+1);
    return min(st[l+(1<<p)-1][p],st[r][p]);
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        scanf("%s",t+1);
        insert();
    }
    setfail();
    int m=strlen(s+1);
    for(int i=0;i<=m;i++){
        for(int j=0;j<20;j++){
            st[i][j]=INF;
        }
    }
    st[0][0]=0;
    int cur=0;
    for(int i=1;i<=m;i++){
        cur=trie[cur][s[i]-'a'];
        if(len[cur]!=0){
            st[i][0]=query(i-len[cur],i-1)+1;
        }
        for(int j=1;j<20;j++){
            if(i-(1<<j)+1<0){
                break;
            }
            st[i][j]=min(st[i][j-1],st[i-(1<<(j-1))][j-1]);
        }
    }
    int ans=st[m][0];
    if(st[m][0]>=INF){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}