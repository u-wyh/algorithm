#include<bits/stdc++.h>
using namespace std;
const int MAXM = 1e5+5;
const int MAXN = 2e6+5;
const int LIMIT = 23;

int n,q,p;
char s[MAXN];

int tree[MAXN];

int trie[MAXN][26];
int fail[MAXN];
int endpos[MAXM];
int cnt;

int dfncnt;
int dep[MAXN];
int dfn[MAXN];
int sz[MAXN];
int st[MAXN][LIMIT];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void insert(int id){
    int len=strlen(s+1);
    int cur=0;
    for(int i=1;i<=len;i++){
        char ch=s[i];
        int path=ch-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
    endpos[id]=cur;
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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    sz[u]=1;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=dfncnt){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        insert(i);
    }
    setfail();
    for(int i=1;i<=cnt;i++){
        addedge(fail[i],i);
    }
    p=log2(cnt)+1;
    dfs(0,0);
    scanf("%d",&q);
    while(q--){
        int op;
        scanf("%d",&op);
        if(op==1){
            scanf("%s",s+1);
            vector<int>vec;
            int cur=0;
            int len=strlen(s+1);
            for(int i=1;i<=len;i++){
                cur=trie[cur][s[i]-'a'];
                vec.push_back(cur);
            }
            sort(vec.begin(), vec.end());
            auto last = unique(vec.begin(), vec.end());
            vec.erase(last, vec.end());
            sort(vec.begin(), vec.end(), [&](int a, int b) {
                return dfn[a] < dfn[b];
            });
            for(int i=0;i<(int)vec.size();i++){
                add(dfn[vec[i]],1);
            }
            for(int i=1;i<(int)vec.size();i++){
                add(dfn[lca(vec[i],vec[i-1])],-1);
            }
        }
        else{
            int x;
            scanf("%d",&x);
            int node=endpos[x];
            cout<<(query(dfn[node]+sz[node]-1)-query(dfn[node]-1))<<endl;
        }
    }
    return 0;
}