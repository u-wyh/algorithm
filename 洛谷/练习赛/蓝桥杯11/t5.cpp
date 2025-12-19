#include<bits/stdc++.h>
using namespace std;

int n,maxans=INT_MIN,minans=INT_MAX,sum;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        maxans=max(maxans,u);
        minans=min(minans,u);
        sum+=u;
    }
    printf("%d\n%d\n%.2lf",maxans,minans,sum*1.0/n);
    return 0;
}