// https://www.luogu.com.cn/problem/P5485
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const long double eps = 1e-18L;

long double s;
int n;

long double a[MAXN];
long double b[MAXN];
long double A[MAXN];
long double B[MAXN];

long double best=-1e100L;
long double bestk;

void calc(long double k){
    if(k<0||k>s){
        return ;
    }

    long double t=1e100L;
    for(int i=1;i<n;i++){
        t=min(t,A[i]*k+B[i]-A[n]*k-B[n]);
    }

    if(t>best){
        best=t;
        bestk=k;
    }
}

int main()
{
    cin>>s>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        A[i]=1/a[i]-1/b[i];
        B[i]=s/b[i];
    }
    for(int i=1;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(fabs(A[i]-A[j])<eps){
                continue;
            }
            long double k=(B[j]-B[i])/(A[i]-A[j]);
            calc(k);
        }
    }
    calc(0);
    calc(s);
    if(best<-1e-12L){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<fixed<<setprecision(2);
    cout<<bestk<<" "<<s-bestk<<" "<<llroundl(max(0.0L,best)*3600)<<'\n';   
    return 0;
}
/*
2147483648.00 0.00 22738062155
*/