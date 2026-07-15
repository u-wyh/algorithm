#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    int cnt=0;
    long long ans=1;
    cin>>n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
                cnt++;
                //cout<<i<<' ';
                if(cnt<=2){
                    ans*=i;
                }
            }
        }
    }
    if (n > 1) {
        //cout<<n<<endl;
        cnt++;
    }
    //cout<<cnt<<endl;
    if(cnt==2){
        cout<<2<<endl;
        return 0;
    }
    if(cnt==1){
        cout<<1<<endl<<0<<endl;
        return 0;
    }
    cout<<1<<endl;
    cout<<ans<<endl;
    return 0;
}
