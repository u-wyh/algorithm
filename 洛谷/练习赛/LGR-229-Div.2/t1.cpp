#include<bits/stdc++.h>
using namespace std;

int n;
int a[15];
int b[15];

int compute(int a,int b,int c,int d){
    if(a>=c&&b<=d){
        return 1;
    }
    if(c>=a&&d<=b){
        return 1;
    }
    return 0;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int ans=0;
    for(int i=1;i<n;i++){
        ans+=compute(a[i],a[i+1],b[i],b[i+1]);
    }
    cout<<ans<<endl;
    return 0;
}