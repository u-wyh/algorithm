#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int nums[MAXN];
int edge[MAXN][2];
vector<vector<int >>graph;
long long ans[MAXN],headans[MAXN];

void f(int x,int p){
    for(int i=0;i<graph[x].size();i++){
        int v=graph[x][i];
        if(v!=p){
            f(v,x);
            ans[x]=max(ans[x],ans[v]);
            headans[x]=max(headans[x],headans[x]+headans[v]);
        }
    }
    ans[x]=max(ans[x],headans[x]);
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        headans[i]=nums[i];
        //ans[i]=max(0,nums[i]);
    }
    for(int i=1;i<n;i++){
        cin>>edge[i][0]>>edge[i][1];
        graph[edge[i][0]].push_back(edge[i][1]);
        graph[edge[i][1]].push_back(edge[i][0]);
    }
    f(1,0);
    cout<<ans[1];
    return 0;
}
