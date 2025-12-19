#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,root;
vector<vector<pair<int,int>>>graph;
long long val[MAXN];
int edges[MAXN][3];

void f(int x,int p){
    long long sum=0;
    int h=-1;
    for(int i=0;i<graph[x].size();i++){
        int v=graph[x][i].first;
        if(v!=p){
            f(v,x);
            sum+=val[v];
        }else{
            h=graph[x][i].second;
        }
    }
    if(h!=-1){
        if(sum==0)
            val[x]=edges[h][2];
        else
            val[x]=min(sum,(long long)edges[h][2]);
    }else{
        val[root]=sum;
    }
}

int main()
{
    cin>>n>>root;
    graph.resize(n+1);
    for(int i=1;i<n;i++){
        cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
        graph[edges[i][0]].push_back({edges[i][1],i});
        graph[edges[i][1]].push_back({edges[i][0],i});
    }
//    for(int i=0;i<=n;i++){
//        val[i]=LLONG_MAX;
//    }
    f(root,0);
    cout<<val[root];
    return 0;
}

