// https://www.luogu.com.cn/problem/P13467
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T,n,m,a;

signed main(){
    cin>>T;
    for(int tc=1;tc<=T;tc++){
        cin>>n>>m>>a;

        cout<<"Case #"<<tc<<": ";

        if(a>n*m){
            cout<<"IMPOSSIBLE\n";
            continue;
        }

        int y=(a+n-1)/n;
        int x=n*y-a;

        cout<<0<<" "<<0<<" ";
        cout<<n<<" "<<1<<" ";
        cout<<x<<" "<<y<<"\n";
    }
    return 0;
}