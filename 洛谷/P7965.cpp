#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int fa[MAXN];
int n,m,q;

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

int main()
{
    cin>>n>>m>>q;
    build();
    int nums[n+1];
    for(int i=1;i<=m;i++){
        for(int i=1;i<=n;i++){
            cin>>nums[i];
            un(i,nums[i]);
        }
    }
    for(int i=1,u,v;i<=q;i++){
        cin>>u>>v;
        if(find(u)==find(v)){
            cout<<"DA\n";
        }else{
            cout<<"NE\n";
        }
    }
    return 0;
}
