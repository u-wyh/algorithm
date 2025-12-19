#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        long long n;
        int cnt=0;
        long long ans=1;
        cin>>n;
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                cnt=0;
                while (n % i == 0) {
                    n /= i;
                    cnt++;
                }
                ans*=pow(i,cnt/3);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
