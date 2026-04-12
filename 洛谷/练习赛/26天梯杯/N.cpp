#include<bits/stdc++.h>
using namespace std;

int n,m;
int val[1005];
int fa[1005];

int dfncnt;
int ord[1005];

void dfs(int u){
    if(u<=n){
        dfs(u<<1);
        dfs(u<<1|1);
        ord[++dfncnt]=u;
    }
}

int main()
{
    cin>>m>>n;
    for(int i=2;i<=n;i++){
        fa[i]=i/2;
    }
    dfs(1);
    while(m--){
        int ans=0;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        for(int i=2;i<=n;i++){
            if(val[i]>val[fa[i]]){
                ans|=1;
            }
            else{
                ans|=2;
            }
        }
        if(ans==1){
            cout<<"Min Heap"<<endl;
        }
        else if(ans==2){
            cout<<"Max Heap"<<endl;
        }
        else{
            cout<<"Not Heap"<<endl;
        }

        for(int i=1;i<n;i++){
            cout<<val[ord[i]]<<' ';
        }
        cout<<val[1];
        if(m){
            cout<<endl;
        }
    }
    return 0;
}