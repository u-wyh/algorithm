#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int earlist[MAXN];
int lastest[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int n;
int sz[MAXN];

void build(){
    cnt=1;
    fill(earlist+1,earlist+n+1,0);
    fill(lastest+1,lastest+n+1,0);
    fill(head+1,head+n*2+1,0);
    fill(Next+1,Next+2*n+1,0);
    fill(to+1,to+2*n+1,0);
    fill(sz+1,sz+n+1,0);
}

void dfs1(int u,int f){
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            earlist[v]=earlist[u]+1;
            lastest[v]=lastest[u]+sz[u]-sz[v];
            dfs2(v,u);
        }
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        build();
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;

            Next[cnt]=head[u];
            to[cnt]=v;
            head[u]=cnt++;

            Next[cnt]=head[v];
            to[cnt]=u;
            head[v]=cnt++;
        }
        dfs1(1,0);
        earlist[1]=1;
        lastest[1]=1;
        dfs2(1,0);
        for(int i=1;i<=n;i++){
            cout<<earlist[i]<<' '<<lastest[i]<<endl;
        }
    }
    return 0;
}
