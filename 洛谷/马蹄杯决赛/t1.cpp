#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,q;
int nums[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=q;i++){
        int op,u,v;
        cin>>op>>u>>v;
        if(op==1){
            nums[u]+=v;
        }
        else{
            nums[u]-=v;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<nums[i]<<' ';
    }
    cout<<endl;
    return 0;
}