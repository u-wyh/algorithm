#include<bits/stdc++.h>

using namespace std;
long long n,t,last[100005];
struct cow
{
    long long x,y;
}a[100005];

int main()
{
    cin >> n >> t;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].y >> a[i].x;
        last[i]=a[i].y+a[i].x*t;
    }
    int res=1;
    for(int i=n-1;i>=1;i--){
        if(last[i]>=last[i+1]){
            last[i]=last[i+1];
        }else{
            res++;
        }
    }
    cout<< res;
    return 0;
}
