#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

vector<pair<int,int>>nums[MAXN];
int n,m;
int sum[MAXN],limit[MAXN];
bool vis[MAXN];
queue<int>q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        sum[i]=a;
        limit[i]=b;
        if(a!=0){
            vis[i]=true;
            sum[i]+=b;
            q.push(i);
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        nums[u].push_back({v,w});
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        sum[u]-=limit[u];
        sum[u]=max(sum[u],0);
        //cout<<u<<' '<<nums[u].size()<<endl;
        for(int i=0;i<nums[u].size();i++){
            int v=nums[u][i].first;
            //cout<<v<<' ';
            int w=nums[u][i].second;
            sum[v]+=w*sum[u];
            if(!vis[v])
                q.push(v);
            vis[v]=true;
        }
        //cout<<endl;
    }
//    for(int i=1;i<=n;i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<endl;
    int f=0;
    for(int i=1;i<=n;i++){
        if(nums[i].size()==0&&sum[i]!=0){
            f=1;
            cout<<i<<' '<<sum[i]<<endl;
        }
    }
    if(!f){
        cout<<"NULL"<<endl;
    }
    return 0;
}
