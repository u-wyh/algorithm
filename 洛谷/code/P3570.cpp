#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;
const int INF = 1e9;

int n,k,s,t;
int col[MAXN];
int a[MAXN];
int b[MAXN];
int f[MAXN];
int g[MAXN];
int nxt[MAXN];
int pre[MAXN];
int lt[MAXN];
int rt[MAXN];
int pos[MAXN];
int vis[MAXN];

bool ok[MAXN];

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

int getnxt(int x){
    stack<int>st;
    while(x!=f[x]){
        st.push(x);
        x=f[x];
    }
    while(!st.empty()){
        int u=st.top();
        f[u]=x;
        st.pop();
    }
    return x;
}

int getpre(int x){
    stack<int>st;
    while(x!=g[x]){
        st.push(x);
        x=g[x];
    }
    while(!st.empty()){
        int u=st.top();
        g[u]=x;
        st.pop();
    }
    return x;
}

// int getnxt(int x){
//     return x==f[x]?x:f[x]=getnxt(f[x]);
// }

// int getpre(int x){
//     return x==g[x]?x:g[x]=getpre(g[x]);
// }

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        col[i]=read();
    }
    s=read(),t=read();
    for(int i=1;i<=s;i++){
        a[i]=read();
    }
    for(int i=1;i<=t;i++){
        b[i]=read();
    }

    for(int i=1;i<=s;i++){
        vis[a[i]]=i;
        ok[a[i]]=true;
    }
    for(int i=1;i<=k;i++){
        pos[i]=0;
    }
    for(int i=n;i>=1;i--){
        nxt[i]=pos[a[1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=k;i++){
        pos[i]=0;
    }
    for(int i=n;i>=1;i--){
        if(!vis[col[i]]){
            continue;
        }
        if(col[i]==a[s]){
            f[i]=i;
        }
        else{
            f[i]=pos[a[vis[col[i]]+1]];
        }
        pos[col[i]]=i;
    }

    for(int i=1;i<=k;i++){
        vis[i]=0;
    }

    for(int i=1;i<=t;i++){
        vis[b[i]]=i;
        ok[b[i]]=true;
    }
    for(int i=1;i<=k;i++){
        pos[i]=0;
    }
    for(int i=1;i<=n;i++){
        pre[i]=pos[b[1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=k;i++){
        pos[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(!vis[col[i]]){
            continue;
        }
        if(col[i]==b[t]){
            g[i]=i;
        }
        else{
            g[i]=pos[b[vis[col[i]]+1]];
        }
        pos[col[i]]=i;
    }

    for(int i=1;i<=n;i++){
        rt[col[i]]=i;
    }
    for(int i=n;i>=1;i--){
        lt[col[i]]=i;
    }

    int minpos=INF,maxpos=0;
    for(int i=1;i<=k;i++){
        if(!lt[i]){
            continue;
        }
        int l=getnxt(nxt[lt[i]]);
        int r=getpre(pre[rt[i]]);

        if(l==0||r==0||l>r){
            continue;
        }
        minpos=min(minpos,l);
        maxpos=max(maxpos,r);
    }

    vector<int>ans;
    for(int i=minpos;i<=maxpos;i++){
        if(col[i]==a[s]){
            ans.push_back(i);
        }
    }
    cout<<ans.size()<<endl;
    for(int v:ans){
        cout<<v<<' ';
    }
    return 0;
}