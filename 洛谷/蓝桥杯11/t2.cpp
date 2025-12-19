#include<bits/stdc++.h>
using namespace std;

int ans=0;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main()
{
    for(int i=1;i<=2020;i++){
        for(int j=1;j<=2020;j++){
            if(gcd(i,j)==1){
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}