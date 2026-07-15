#include<bits/stdc++.h>
using namespace std;

int n;
double a[100005],b[100005];

int cmp(double a,double b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i]>>b[i];
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    int l=0,r=1;
    double suma=0,sumb=0,ans=0;
    for(r=1;r<=n;r++){
        sumb+=b[r];
        ans=max(ans,min(suma-l-r,sumb-l-r));
        while(suma<sumb&&l<n){
            suma+=a[++l];
            ans=max(ans,min(suma-l-r,sumb-l-r));
        }
    }
    printf("%.4lf\n",ans);
    return 0;
}
