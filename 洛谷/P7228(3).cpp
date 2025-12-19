#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int deep[MAXN<<1];
bool vis[MAXN];
int n;

void dfs(int u,int f){
    deep[u]=deep[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1,j=n;i<n;i++,j++){
        int u,v;
        cin>>u>>v;

        Next[i]=head[u];
        to[i]=v;
        head[u]=i;

        Next[j]=head[v];
        to[j]=u;
        head[v]=j++;
    }
    //deep[1]=1;
    dfs(1,0);
    for(int i=1;i<n;i++){
        if(deep[to[i]]%2==0)
            cout<<1<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}
