// https://www.luogu.com.cn/problem/P1403
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;

    long long ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        ans+=1ll*v*(rt-lt+1);
    }
    cout<<ans<<endl;
    return 0;
}