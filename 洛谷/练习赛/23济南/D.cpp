#include<bits/stdc++.h>
using namespace std;

int compute(int x){
    int ans=0;
    while(x){
        ans=max(ans,x%10);
        x/=10;
    }
    return ans;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        int l=l1+l2;
        int r=r1+r2;
        if(r-l>=10){
            cout<<9<<endl;
            continue;
        }
        else{
            int ans=0;
            for(int i=l;i<=r;i++){
                ans=max(ans,compute(i));
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}