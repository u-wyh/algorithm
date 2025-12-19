#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 4e5+5;

int n,m;
int fa[MAXN];
int ls[MAXN],rs[MAXN];
struct node{
    int u,op;
}nums[MAXM];
int ans[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>ls[i]>>rs[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].u>>nums[i].op;
    }
    return 0;
}
