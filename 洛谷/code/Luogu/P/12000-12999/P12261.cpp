#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const double eps = 1e-6;

int n;
int a[MAXN],b[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

double compute(double x){
    double ans=INT_MIN;
    for(int i=1;i<=n;i++){
        ans=max(ans,a[i]-(a[i]-b[i])*1.0/200000*(100000+x));
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read();
    }
    double l=-100000,r=100000,ans;
    while(r-l>=eps){
        double midl=l+(r-l)/3;
        double midr=l+(r-l)*2/3;
        double k1=compute(midl);
        double k2=compute(midr);
        if(k1<k2){
            r=midr;
            ans=midl;
        }
        else{
            l=midl;
            ans=midr;
        }
    }
    printf("%.2lf\n",compute(ans));
    return 0;
}