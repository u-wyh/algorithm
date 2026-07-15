#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int sz[MAXN];
char str[MAXN];

void dfs(int u){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        sz[v]+=sz[u];
        dfs(v);
    }
}

int main()
{
    cin>>n;
    for(int i=1,u;i<n;i++){
        cin>>u;

        Next[cnt]=head[u];
        to[cnt]=i+1;
        head[u]=cnt++;
    }
    for(int i=1;i<=n;i++){
        cin>>str[i];
    }
    int m;
    cin>>m;
    for(int i=1,u;i<=m;i++){
        cin>>u;
        sz[u]++;
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        if(sz[i]%2==0){
            cout<<str[i];
        }else{
            if(str[i]=='1')
                cout<<'0';
            else
                cout<<'1';
        }
    }
    return 0;
}
