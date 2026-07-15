#include<bits/stdc++.h>
using namespace std;

long long n,m;

int main()
{
    cin>>n>>m;
    int k;
    for(int i=1;i<=n;i++){
        if(i*i-i>=2*m){
            k=i;
            break;
        }
    }
    for(int i=1;i<=n-k;i++){
        cout<<i<<' ';
    }
    if(m==(k*k-k)/2){
        for(int i=n;i>n-k;i--){
            cout<<i<<' ';
        }
    }else{
        int h=m-((k-1)*(k-1)-(k-1))/2;
        cout<<n-k+1+h<<' ';
        for(int i=n;i>n-k;i--){
            if(i==n-k+1+h)
                continue;
            else
                cout<<i<<' ';
        }
    }
    return 0;
}
