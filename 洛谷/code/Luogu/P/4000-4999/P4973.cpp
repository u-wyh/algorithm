#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        int x;
        string str;
        cin>>x>>str;
        int n=str.length();
        long double ans=1;
        ans+=1.0*(n-1)*n/2*log10(x);
        for(int i=0;i<n;i++){
            ans+=log10(str[i]-'0');
        }
        cout<<(long long)ans<<endl;
    }
    return 0;
}