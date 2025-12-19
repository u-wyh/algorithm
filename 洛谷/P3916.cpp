#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int > p[100005];
int a[100005];

void dfs(int x,int y){
    a[x]=y;
    for(int i=0;i<p[x].size();i++){
        if(a[p[x][i]]==0){
            dfs(p[x][i],y);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        p[v].push_back(u);
    }
    for(int i=n;i>0;i--){
        if(a[i]==0){
            dfs(i,i);
        }
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}
