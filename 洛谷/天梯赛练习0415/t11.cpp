#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int kind,cnt;
vector<int>vec[MAXN];
int vis[MAXN];
int root;
int maxval=0;

void dfs(int u){
    sort(vec[u].begin(),vec[u].end());
    if(u!=root)
        cout<<' '<<u;
    for(int i=0;i<(int)vec[u].size();i++){
        dfs(vec[u][i]);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        if(u==0){
            root=i;
            continue;
        }
        if(vis[u]==0){
            cnt++;
        }
        vis[u]++;
        maxval=max(vis[u],maxval);
        vec[u].push_back(i);
    }
    if(n==1){
        cout<<1<<' '<<"yes"<<endl;
        cout<<1<<endl;
        return 0;
    }
    cout<<maxval<<' ';
    if((n-1)%maxval==0&&(n-1)/maxval==cnt){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"no"<<endl;
    }
    cout<<root;
    dfs(root);
    return 0;
}