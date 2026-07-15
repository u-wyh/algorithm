#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int fa[MAXN];
int ans[MAXN];
int n,m;
int order[MAXN],vis[MAXN];
vector<int>vec[MAXN];

int find(int i){
    return (fa[i]==i)?i:fa[i]=find(fa[i]);
}

void un(int x,int y){
     int fx=find(x);
     int fy=find(y);
     if(fx!=fy){
        fa[fx]=fy;
     }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cin>>order[i];
        vis[i]=1;
    }
    for(int i=n;i>=1;i--){
        vis[order[i]]=0;
        int u=order[i];
        for(int j=0;j<vec[u].size();j++){
            int v=vec[u][j];
            if(!vis[u]&&!vis[v]){
                un(u,v);
            }
        }
        int f=find(u);
        int flag=1;
        for(int j=n;j>=i;j--){
            if(find(order[j])!=f){
                flag=0;
                ans[i]=0;
                break;
            }
        }
        if(flag){
            ans[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
