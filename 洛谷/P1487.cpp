#include<bits/stdc++.h>
using namespace std;
const int MAXN = 65;

int n,m;
long long f[MAXN];
double d,a1,an;
double k;

int main()
{
    cin>>n>>m>>d>>a1>>an;
    if(n)
    f[0]=0;
    f[1]=1;
    for(int i=2;i<n;i++){
        f[i]=2*f[i-1]+f[i-2];
    }
    if(m==0){
        printf("0.000");
        return 0;
    }
    if(a1==d){
        printf("%.3lf",d);
        return 0;
    }
    an=(an-d)/(a1-d);
    long long a=f[n-2];
    long long b=f[n-1];
    if(n%2==0){
        k=1.0*(an+a)/b;
    }
    else{
        k=1.0*(a-an)/b;
    }
    a=f[m-2];
    b=f[m-1];
    double kk;
    if(m%2==0){
        kk=1.0*k*b-a;
    }
    else{
        kk=1.0*a-1.0*b*k;
    }
    double ans=(a1-d)*kk;
    ans+=d;
    printf("%.3lf",ans);
    return 0;
}