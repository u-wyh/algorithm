#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 2e6+5;

int n,m;
string s;

int cur;
int cnt;
int tree[MAXN][26];
int fail[MAXN];
int times[MAXN];
int en[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

void insert(string s,int i){
    int len=s.length();
    cur=0;
    for(int i=0;i<len;i++){
        int path=s[i]-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[i]=cur;
}

queue<int>q;
void setfail(){
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

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        times[u]+=times[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s,i);
    }
    setfail();
    cin>>s;
    cur=0;
    m=s.length();
    for(int i=0;i<m;i++){
        cur=tree[cur][s[i]-'a'];
        times[cur]++;
    }
    for(int i=1;i<=cnt;i++){
        addedge(fail[i],i);
    }
    dfs(0);
    for(int i=1;i<=n;i++){
        cout<<times[en[i]]<<endl;
    }
    return 0;
}