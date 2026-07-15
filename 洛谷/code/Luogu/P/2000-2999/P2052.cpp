#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 1e6+5;

int n;
int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int fa[MAXN];
int sz[MAXN<<1];
int nums[MAXN][3];

void dfs(int u,int f){
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>nums[i][0]>>nums[i][1]>>nums[i][2];

        Next[cnt]=head[nums[i][0]];
        to[cnt]=nums[i][1];
        head[nums[i][0]]=cnt++;

        Next[cnt]=head[nums[i][1]];
        to[cnt]=nums[i][0];
        head[nums[i][1]]=cnt++;
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<n;i++){
        if(fa[nums[i][0]]==nums[i][1]){
            ans+=nums[i][2]*abs(n-2*sz[nums[i][0]]);
        }
        else
            ans+=nums[i][2]*abs(n-2*sz[nums[i][1]]);
    }
    cout<<ans;
    return 0;
}
