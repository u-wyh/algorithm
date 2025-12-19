#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,m;
int a[MAXN];

signed main() 
{
    cin>>n>>m;

    if(m==1){
        for(int i=0;i<n;i++){
            a[i]=i*i;
        }
    }
    else{
        if(m%2==1){
            int x=(m+1)/2;
            for(int i=0;i<m;i++) {
                a[i]=x+i;
            }
        } else {
            int x=m/2;
            int sum=0;
            for(int i=0;i<m-1;i++) {
                a[i]=x+i;
                sum+=a[i];
            }
            a[m-1]=m*m-sum;
        }
        for (int i=m;i<n;i++) {
            a[i]=a[i-m]+2*i+1;
        }
    }

    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }
    return 0;
}