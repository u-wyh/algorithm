#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

double f[MAXN];
double g[MAXN];

int main()
{
    int n;
    cin>>n;
    for(int i=n-1;i>=0;i--){
        f[i]=f[i+1]+1.0*n/(n-i);
        g[i]=1.0*i/(n-i)*f[i]+g[i+1]+f[i+1]+1.0*n/(n-i);
    }
    printf("%.2lf",g[0]);
    return 0;
}