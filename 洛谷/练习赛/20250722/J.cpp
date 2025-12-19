#include<bits/stdc++.h>
using namespace std;
#define int long long

int gcd(int a,int b){
    return (b==0)?a:gcd(b,a%b);
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        int val=gcd(a,b);
        a/=val,b/=val;
        int t=0;
        int d=(a+b);
        while(d%2==0){
            t++;
            d/=2;
        }
        if(d>1){
            cout<<-1<<endl;
        }
        else{
            cout<<t<<endl;
        }
    }
    return 0;
}