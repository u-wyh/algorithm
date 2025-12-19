#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,d;
int ans1,ans2;

signed main()
{
    cin>>a>>d;
    a--;
    int flag=-1;
    for(int i=1;i<=a;i++){
        int b=(a-i+1)/i;
        int c=(a-i+1)%i;
        ans1+=flag*(i*(b+1)*b/2+c*(b+1));
        flag*=-1;
    }
    flag=-1;
    for(int i=1;i<=d;i++){
        int b=(d-i+1)/i;
        int c=(d-i+1)%i;
        // cout<<i<<": "<<flag*(i*(b+1)*b/2+c*(b+1))<<endl;
        ans2+=flag*(i*(b+1)*b/2+c*(b+1));
        flag*=-1;
    }
    // cout<<ans1<<' '<<ans2<<endl;
    cout<<(ans2-ans1)<<endl;
    return 0;
}