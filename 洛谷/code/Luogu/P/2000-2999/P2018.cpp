#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];
int deep[MAXN];
int sum[MAXN];
int t[MAXN];

void build(){
    fill(deep+1,deep+n+1,0);
    fill(sz+1,sz+n+1,0);
    fill(sum+1,sum+n+1,0);
}

void dfs1(int u,int f){
    deep[u]=deep[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]++;
            dfs1(v,u);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u;
        cin>>u;

        Next[cnt]=head[u];
        to[cnt]=i+1;
        head[u]=cnt++;

        Next[cnt]=head[i+1];
        to[cnt]=u;
        head[i+1]=cnt++;
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        build();
        dfs1(i,0);
        for(int i=1;i<=n;i++){
            cout<<sz[i]<<' '<<deep[i]<<endl;
            sum[i]=sz[i]+deep[i];
        }
        cout<<"--------------------------------------\n";
        sort(sum+1,sum+n+1,cmp);
        t[i]=sum[1];
        ans=min(ans,t[i]);
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(t[i]==ans){
            cout<<i<<' ';
        }
    }
    return 0;
}
