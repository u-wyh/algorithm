#include<bits/stdc++.h>
using namespace std;
int n;
long long m;
long long f[100005],s[100005];

bool check(long long mid){
    long long sum=0;
    for(int i=1;i<=n;i++){
        if(s[i]>mid){
            sum=0;
        }else{
            sum+=f[i];
            if(sum>=m){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m;
    long long l=0,r=0;
    for(int i=1;i<=n;i++){
        cin>>f[i]>>s[i];
        r=max(r,s[i]);
    }
    long long ans=r;
    while(l<=r){
        long long mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
