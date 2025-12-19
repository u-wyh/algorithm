#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int father[MAXN];
int n,m,k;

void build(){
    for(int i=0;i<=n*m;i++){
        father[i]=i;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x,int y){
    father[find(x)] = find(y);
}

int main()
{
    cin>>n>>m>>k;
    build();
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        un(u,v);
    }
    int ans=0;
    for(int i=1;i<=m*n;i++){
        if(find(i)==i){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
