#include<bits/stdc++.h>
using namespace std;

long long l,r;

long long sum(long long val){
    if(val<10){
        return val;
    }
    long long a=val%10;
    long long ans=val/10+9;
    long long b=val;
    while(b>10){
        b/=10;
    }
    if(b>a){
        ans--;
    }
    return ans;
}

int main()
{
    cin>>l>>r;
    cout<<sum(r)-sum(l-1)<<endl;
    return 0;
}
