#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 35;

int n,m1,m2;
int f[MAXN];
int g[MAXN];

struct node{
    int t,v;
};

struct compare{
    bool operator()(node a,node b){
        return a.t>b.t;
    }
};
priority_queue<node,vector<node>,compare>heap;

int main()
{
    cin>>n>>m1>>m2;

    for(int i=1;i<=m1;i++){
        node tmp;
        cin>>tmp.v;
        heap.push({tmp.v,tmp.v});
    }
    for(int i=1;i<=n;i++){
        node u=heap.top();
        heap.pop();
        f[i]=u.t;
        heap.push({u.t+u.v,u.v});
    }

    while(!heap.empty()){
        heap.pop();
    }

    for(int i=1;i<=m2;i++){
        node tmp;
        cin>>tmp.v;
        heap.push({tmp.v,tmp.v});
    }
    for(int i=n;i>=1;i--){
        node u=heap.top();
        heap.pop();
        g[i]=u.t;
        heap.push({u.t+u.v,u.v});
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,f[i]+g[i]);
    }
    cout<<f[n]<<' '<<ans<<endl;
    return 0;
}