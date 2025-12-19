#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const double eps = 1e-4;

int n;
double x[MAXN],y[MAXN];
double k[MAXN],b[MAXN];

bool check(double y){
    double l=-1e9,r=1e9;
    for(int i=2;i<=n;i++){
        if(k[i]>0){
            r=min(r,(y-b[i])/k[i]);
        }
        else if(k[i]<0){
            l=max(l,(y-b[i])/k[i]);
        }
        else{
            if(b[i]>y){
                return 0;
            }
        }
    }
    return l<=r;
}

int main()
{
    cin>>n>>x[1]>>y[1];
    for(int i=2;i<=n;i++){
        cin>>x[i]>>y[i];
        k[i]=(y[i]-y[i-1])/(x[i]-x[i-1]);
        b[i]=y[i]-k[i]*x[i];
    }
    double l=0,r=1000000,ans=0;
    while(r-l>=eps){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid;
        }
        else{
            l=mid;
        }
    }
    printf("%.2lf\n",ans);
    return 0;
}