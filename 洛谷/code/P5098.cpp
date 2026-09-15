#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;

int x[MAXN];
int y[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        x[i]=a+b;
        y[i]=a-b;
    }
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    cout<<max(y[n]-y[1],x[n]-x[1])<<endl;
    return 0;
}