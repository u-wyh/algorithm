#include<bits/stdc++.h>
using namespace std;

int ask(int x){
    cout<<"? "<<x<<endl;
    int v;
    cin>>v;
    return v;
}

int main()
{
    int l=0,r=1000000000,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ask(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<"! "<<ans<<endl;
    return 0;
}