#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 22;
const int ALPHA = 26;

int n,q,p;
char s[MAXN];

int head[MAXN];
int nxt[MAXN*10];
int to[MAXN*10];
int cntg=1;

int headh[MAXN];
int nxth[MAXN];
int toh[MAXN];
int cnth=1;

int tree[MAXN][ALPHA];
int fail[MAXN];
int len[MAXN];
int firstpos[MAXN];
int cnt;
int last;

int st[MAXN][MAXH];
int dep[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addedgeh(int u,int v){
    nxth[cnth]=headh[u];
    toh[cnth]=v;
    headh[u]=cnth++;
}

void init(){
    cnt=1;
    last=0;
    len[0]=0,len[1]=-1;
    fail[0]=1,fail[1]=1;
    addedge(0,1);
    addedge(1,0);
    s[0]='#';
}

int getfail(int p,int i){
    while(s[i-len[p]-1]!=s[i]){
        p=fail[p];
    }
    return p;
}

void insert(int i){
    int c=s[i]-'a';
    int cur=getfail(last,i);

    if(!tree[cur][c]){
        int x=++cnt;
        len[x]=len[cur]+2;

        int p=getfail(fail[cur],i);
        fail[x]=tree[p][c];
        addedge(x,fail[x]);
        addedge(fail[x],x);

        tree[cur][c]=x;
        firstpos[x]=i-len[x]+1;
        addedgeh(len[x],x);
    }
    last=tree[cur][c];
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

int main()
{
    scanf("%d %d",&n,&q);
    p=log2(n)+1;
    scanf("%s",s+1);
    init();
    for(int i=1;i<=n;i++){
        insert(i);
    }
    dfs(1,1);
    // dfs(0,0);
    while(q--){
        int len1,len2;
        scanf("%d %d",&len1,&len2);
        int ans=n+1;
        for(int ei=headh[len2];ei;ei=nxth[ei]){
            int v=toh[ei];
            int pos=firstpos[v];
            int cur=v;
            for(int i=p;i>=0;i--){
                if(len[st[cur][i]]>=len1){
                    cur=st[cur][i];
                }
            }
            if(len[cur]==len1){
                ans=min(ans,pos);
            }
        }
        if(ans==n+1){
            ans=-1;
        }
        cout<<ans<<endl;
    }
    return 0;
}