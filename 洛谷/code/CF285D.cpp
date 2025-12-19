#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

long long a[17],b[17];

int main()
{
    b[1]=1;
    for(int i=2;i<=16;i++){
        b[i]=(b[i-1]*i)%MOD;
    }
    a[1]=1;
    a[3]=3;
    a[5]=15;
    a[7]=133;
    a[9]=2025;
    a[11]=37851;
    a[13]=1030367;
    a[15]=36362925;
    int num;
    cin>>num;
    cout<<(a[num]*b[num])%MOD<<endl;
    return 0;
}