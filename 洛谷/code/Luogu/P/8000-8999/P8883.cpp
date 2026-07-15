#include<bits/stdc++.h>
using namespace std;
#define int long long
const long double pi = 3.141592653589793238462643383279;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<(long long)(n*(1.0-6.0/(pi*pi)))<<endl;
    }
    return 0;
}