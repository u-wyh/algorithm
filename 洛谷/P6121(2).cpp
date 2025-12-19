#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int head[MAXN],Next[MAXN<<1],to[MAXN<<1];
int cnt=1;
int n,m;
int arr[MAXN],ans[MAXN];
int fa[MAXN];
bool vis[MAXN];
int t=0;

int find(int x){
    if(x!=fa[x]){
        fa[x]=find(fa[x]);
    }
    return fa[x];
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    vis[arr[n]]=1;
    ans[n]=1;
    for(int i=n-1;i>=1;i--){
        vis[arr[i]]=1;
        for(int j=head[arr[i]];j>0;j=Next[j]){
            int v=to[j];
            if(vis[v]){
                int tmp=find(v);
                int tmp2=find(arr[i]);
                if(tmp!=tmp2){
                    t++;
                    fa[tmp2]=tmp;
                }
            }
        }
        if(t==n-i){
            ans[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            cout<<"YES"<<endl;
        }
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
