#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve(){
    LL n;
    cin >> n;

    if(n & 1) cout << "-1\n";
    else cout << "-1 1 " << n / 2 << "\n";
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while(T--){
        solve();
    }
    return 0;
}