#include<bits/stdc++.h>
using namespace std;
#define int long long
const double delta = 0.57721566490153286060651209;

signed main()
{
    int n;
    cin>>n;
    if(n<=1000000){
        if(n==1){
            printf("0.00000");
        }
        else{
            double ans=1;
            for(int i=1;i<n;i++){
                ans+=1.0/i;
            }
            printf("%.5lf",ans);
        }
    }
    else{
        double ans=delta+1+log(n);
        printf("%.5lf",ans);
    }
    return 0;
}