#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int ans;
int n;
int edges[MAXN][2];
vector<vector<int>>graph;

int f(int x,int p){
    bool k1=false,k2=false,k3=false;
    for(int i=0;i<graph[x].size();i++){
        int v=graph[x][i];
        if(v!=p){
            int k=f(v,x);
            if(k==0){
                k1=true;
            }else if(k==1){
                k2=true;
            }else if(k==2){
                k3=true;
            }
        }
    }
    if(k1){
        ans++;
        return 2;
    }else if(k3){
        return 1;
    }else{
        return 0;
    }
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<n;i++){
        cin>>edges[i][0]>>edges[i][1];
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    if(f(1,0)==0){
        ans++;
    }
    cout<<ans;
    return 0;
}
