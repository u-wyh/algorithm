#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;

int n;
double l,r;
double arr[14];

int main()
{
    cin>>n>>l>>r;
    double ans=0;
    for(int i=n;i>=0;i--){
        cin>>arr[i];
    }
    while(r-l>=eps){
        double midl=(r-l)/3+l;
        double midr=(r-l)/3*2+l;
        double k1=0;
        for(int i=0;i<=n;i++){
            k1+=arr[i]*pow(midl,i);
        }
        double k2=0;
        for(int i=0;i<=n;i++){
            k2+=arr[i]*pow(midr,i);
        }
        if(k1<=k2){
            l=midl;
            ans=midr;
        }
        else{
            r=midr;
            ans=midl;
        }
    }
    printf("%.8lf",ans);
    return 0;
}