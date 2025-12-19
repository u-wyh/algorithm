#include<bits/stdc++.h>
using namespace std;

vector<int>ans;

int main()
{
    int a,b,n;
    cin>>a>>b>>n;
    ans.push_back(a);
    ans.push_back(b);
    int u=0;
    while(ans.size()<n){
        a=ans[u];
        b=ans[++u];
        int k=a*b;
        if(k>=10){
            ans.push_back(k/10);
        }
        ans.push_back(k%10);
    }
    for(int i=0;i<n-1;i++){
        cout<<ans[i]<<' ';
    }
    cout<<ans[n-1];
    return 0;
}