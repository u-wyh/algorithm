#include<bits/stdc++.h>
using namespace std;

int n;
double d1,c,d2,p;
struct station{
    double dis,val;
}oil[10];

bool cmp(station a,station b){
    return a.dis<b.dis;
}

int main()
{
    cin>>d1>>c>>d2>>p>>n;
    for(int i=1;i<=n;i++){
        cin>>oil[i].dis>>oil[i].val;
    }
    oil[0].dis=0,oil[0].val=p;
    sort(oil,oil+n+1,cmp);
    double ans=1e9;
    double x=c*d2;
    for(int i=1;i<=n;i++){
        if(x<d[i]-d[i-1]){
            printf("No Solution\n");
            return 0;
        }
    }
    return 0;
}
