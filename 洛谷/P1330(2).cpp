#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int fa[MAXN],sz[MAXN],n,m;
bool vis[MAXN];

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=n+1;i<=2*n;i++){
        fa[i]=i;
        sz[i]=0;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    sz[fx]+=sz[fy];
    fa[fy]=fx;
}

int main()
{
    cin>>n>>m;
    build();
    int f=0;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        if(find(u)!=find(v)){
            un(u,v+n);
            un(v,u+n);
        }
        else{
            f=1;
            continue;
        }
    }
    if(f==1){
        cout<<"Impossible";
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int f=find(i);
        if(!vis[f]){
            ans+=min(sz[f],sz[find(i+n)]);
            vis[f]=true;
            vis[find(i+n)]=true;
        }
    }
    cout<<ans;
    return 0;
}
