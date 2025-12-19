#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 2e5+5;

int n,m;
vector<int>nums[MAXM];
vector<int>edge[MAXM];
int st,en;
int dis[MAXN];
bool inroad[MAXN],can[MAXN];
queue<int>q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        nums[u].push_back(v);
        edge[v].push_back(u);
    }
    cin>>st>>en;
    can[en]=true;
    q.push(en);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<edge[cur].size();i++){
            int v=edge[cur][i];
            if(!can[v]){
                can[v]=true;
                q.push(v);
            }
        }
    }
    if(!can[st]){
        cout<<"-1"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(can[i]){
            inroad[i]=true;
            for(int j=0;j<nums[i].size();j++){
                int v=nums[i][j];
                if(!can[v]){
                    inroad[i]=false;
                    break;
                }
            }
        }
    }
    if(!inroad[st]){
        cout<<"-1"<<endl;
        return 0;
    }
    dis[st]=0;
    q.push(st);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        if(cur==en){
            cout<<dis[en];
            return 0;
        }
        for(int j=0;j<nums[cur].size();j++){
            int v=nums[cur][j];
            if(inroad[v]&&!dis[v]){
                dis[v]=dis[cur]+1;
                q.push(v);
            }
        }
    }
    cout<<"-1";
    return 0;
}
