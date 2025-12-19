#include<bits/stdc++.h>
using namespace std;

typedef long long ll;  // 使用 ll 作为 long long 的别名
const ll MN = 3e5 + 5;

ll a[MN];
ll Lmax[MN], Rmax[MN], Lmin[MN], Rmin[MN];
stack<ll> s;
ll n;

int main() {
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];

    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]<=a[i])
            s.pop();
        if(s.empty())
            Lmax[i]=0;
        else
            Lmax[i]=s.top();
        s.push(i);
    }

    while(!s.empty())
        s.pop();
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]>=a[i])
            s.pop();
        if(s.empty())
            Lmin[i]=0;
        else
            Lmin[i]=s.top();
        s.push(i);
    }

    while(!s.empty())
        s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]<a[i])
            s.pop();
        if(s.empty())
            Rmax[i]=n+1;
        else
            Rmax[i]=s.top();
        s.push(i);
    }

    while(!s.empty())
        s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]>a[i])
            s.pop();
        if(s.empty())
            Rmin[i]=n+1;
        else
            Rmin[i]=s.top();
        s.push(i);
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += a[i] * (i - Lmax[i]) * (Rmax[i] - i);
        ans -= a[i] * (i - Lmin[i]) * (Rmin[i] - i);
    }
    cout << ans << endl;
    return 0;
}
