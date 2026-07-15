#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXM = 30005;

int n,m;
int u,v;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
    }
    for(int i=1;i<=n;i++){
        int ans=0;
        vis[i]=true;
        for(int j=head[i];j>0;j=Next[j]){
            vis[to[j]]=true;
        }
        for(int j=1;j<=n;j++){
            printf("%3d",vis[j]);
            if(vis[j]){
                ans++;
                vis[j]=false;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

