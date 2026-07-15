#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,mul,maxx;
int arr[45];

void dfs(int x,int ans,int last){
    if(x==m){
        mul=0;
        for(int j=last+1;j<n;j++){
            mul+=arr[j];
            mul*=10;
        }
        mul+=arr[n];
        maxx=max(maxx,ans*mul);
        return;
    }
    for(int i=last+1;i<=n-m+x;i++){
        mul=0;
        for(int j=last+1;j<i;j++){
            mul+=arr[j];
            mul*=10;
        }
        mul+=arr[i];
        dfs(x+1,ans*mul,i);
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        arr[i]=c-'0';
    }
    dfs(0,1,0);
    cout<<maxx<<endl;
    return 0;
}
