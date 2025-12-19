#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 59;
const int MAXK = MAXN*70;

int n;
int p,q;
long long all;//表示全局最大值
long long val[MAXN];
long long ans[MAXN];
map<long long,int>mp;

int cnt=1;
int trie[MAXK][2];

int fa[MAXN];
int tag[MAXN][2];
int son[MAXN][2];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

long long find(long long val){
    int cur=1;
    long long ans=0;
    for(int i=MAXH;i>=0;i--){
        int best=1-((val>>i)&1);
        if(trie[cur][best]){
            ans+=(1ll<<i);
            cur=trie[cur][best];
        }
        else{
            cur=trie[cur][1-best];
        }
    }
    return ans;
}

void insert(long long val){
    int cur=1;
    for(int i=MAXH;i>=0;i--){
        int path=(val>>i)&1;
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
}

void clear(){
    for(int i=1;i<=cnt;i++){
        trie[i][0]=trie[i][1]=0;
    }
    all=0;
    cnt=1;
}

void dfs(int u){
    insert(val[u]);
    all=max(all,find(val[u]));
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d",&fa[i]);
        addedge(fa[i],i);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&val[i]);
    }

    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    else if(n==2){
        cout<<0<<endl<<0<<endl;
        return 0;
    }

    for(int i=n;i>=1;i--){
        mp[val[i]]=i;
    }

    for(int i=1;i<=n;i++){
        insert(val[i]);
        long long ans=find(val[i]);
        if(all<=ans){
            all=ans;
            p=i,q=mp[all^val[i]];
        }
    }

    // cout<<all<<' '<<p<<' '<<q<<endl;

    while(p!=0){
        tag[p][0]=true;
        son[fa[p]][0]=p;
        p=fa[p];
    }
    while(q!=0){
        tag[q][1]=true;
        son[fa[q]][1]=q;
        q=fa[q];
    }
    for(int i=1;i<=n;i++){
        if(!tag[i][0]&&!tag[i][1]){
            ans[i]=all;
        }
    }

    clear();
    int u=1;
    while(tag[u][0]){
        ans[u]=all;
        insert(val[u]);
        all=max(all,find(val[u]));
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=son[u][0]){
                dfs(v);
            }
        }
        u=son[u][0];
    }

    clear();
    u=1;
    while(tag[u][1]){
        ans[u]=all;
        insert(val[u]);
        all=max(all,find(val[u]));
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=son[u][1]){
                dfs(v);
            }
        }
        u=son[u][1];
    }

    for(int i=1;i<=n;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}