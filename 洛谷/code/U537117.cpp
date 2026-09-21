// https://www.luogu.com.cn/problem/U537117
#include<bits/stdc++.h>
using namespace std;
#define int long long

int solve(int n){
    int ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;
        ans+=v*(rt-lt+1);
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<solve(n)<<endl;
    }
    return 0;
}