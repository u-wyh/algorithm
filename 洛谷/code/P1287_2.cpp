// https://www.luogu.com.cn/problem/P1287
#include<bits/stdc++.h>
using namespace std;

int comb(int a,int b){
    int ans=1;
    for(int i=1;i<=b;i++){
        ans*=(a-i+1);
        ans/=i;
    }
    return ans;
}

int main()
{
    int n,r;
    cin>>n>>r;
    int ans=0;
    for(int k=0;k<=r;k++){
        int tmp=1;
        if((r-k)&1){
            tmp=-1;
        }
        tmp*=comb(r,k);
        for(int i=1;i<=n;i++){
            tmp*=k;
        }
        // cout<<k<<":  "<<tmp<<endl;
        ans+=tmp;
    }
    cout<<ans<<endl;
    return 0;
}