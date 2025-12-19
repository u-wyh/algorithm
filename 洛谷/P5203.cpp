#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int LIMIT = 20;

int n,m,p;
long long ans=0;
int a[MAXN],b[MAXN],c[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][LIMIT];

map<pair<int,int>,int>mp;

int val[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
    }
}

int get(int u,int ancestor){
    if(u==ancestor){
        return -1;
    }
    for(int i=p;i>=0;i--){
        if(dep[st[u][i]]>dep[ancestor]){
            u=st[u][i];
        }
    }
    return u;
}

void dfs2(int u,int fa){
    val[u]+=val[fa];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
}

inline int lca(int a,int b){
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

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    for(int i=n;i<=m;i++){
        a[i]=read();
        b[i]=read();
        c[i]=lca(a[i],b[i]); 
        int t1=get(a[i],c[i]);
        int t2=get(b[i],c[i]);
        if(t1!=-1){
            val[t1]++;
            ans-=val[t1];
        }
        if(t2!=-1){
            val[t2]++;
            ans-=val[t2];
        }
        if(t1!=-1&&t2!=-1){
            if(t1>t2){
                swap(t1,t2);
            }
            ans-=mp[{t1,t2}];
            mp[{t1,t2}]++;
        }
    }
    dfs2(1,0);
    for(int i=n;i<=m;i++){
        ans+=(val[a[i]]+val[b[i]]-2*val[c[i]]);
    }
    cout<<ans<<endl;
    return 0;
}