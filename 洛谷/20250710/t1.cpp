#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;

int k[MAXN];
int b[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==fa){
            continue;
        }
        k[v]=-k[u];
        b[v]=w-b[u];
        dfs(v,u);
    }
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    k[1]=1;
    dfs(1,0);
    int minn=1,maxx=INT_MAX;
    for(int i=1;i<=n;i++){
        if(k[i]==1){
            minn=max(minn,1-b[i]);
        }
        else{
            maxx=min(maxx,b[i]-1);
        }
    }
    if(minn>maxx){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        cout<<(k[i]*minn+b[i])<<' ';
    }
    return 0;
}
/*
5
1 2 5
1 3 4
2 5 7
3 4 2

4
1 2 5
2 3 9
3 4 4
*/