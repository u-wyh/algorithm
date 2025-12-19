#include<bits/stdc++.h>
using namespace std;
#define int long long

int ans[200];
int cnt=0;

bool check(int n){
    int m=sqrt(n);
    return m*m==n;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cnt=0;
        while(!check(n)){
            ans[++cnt]=(n&-n);
            n+=ans[cnt];
        }
        cout<<cnt<<endl;
        if(cnt){
            cout<<ans[1];
        }
        for(int i=2;i<=cnt;i++){
            cout<<' '<<ans[i];
        }
        cout<<endl;
    }
    return 0;
}