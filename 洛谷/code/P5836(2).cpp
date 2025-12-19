#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int fa[MAXN];
char str[MAXN];
int ans[MAXN];
int cnt=0;

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}


int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        cin>>str[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        if(str[u]==str[v])
            un(u,v);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        char c;
        cin>>u>>v>>c;
        if(find(u)==find(v)&&c!=str[u])
            ans[cnt++]=0;
        else
            ans[cnt++]=1;
    }
    for(int i=0;i<m;i++){
        cout<<ans[i];
    }
    return 0;
}
