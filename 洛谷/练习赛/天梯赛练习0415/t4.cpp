#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    int sum=0;
    for(int i=1;i<=m;i++){
        int val;
        cin>>val;
        sum+=val;
    }
    int ans=max(0,sum-n*m+n);
    cout<<ans<<endl;
    return 0;
}