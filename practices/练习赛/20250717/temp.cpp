#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n, t;
    cin >> n >> t;
    string s;
    cin >> s;
    deque<int> mx;
    string tmp=s;
    tmp+=s;
    int len=s.length();
    int l=0,r=0;
    for(;l<len;r++){
        if(tmp[r]=='1'){
            if(r>l) mx.push_back(r-l);
            l=r+1;
        }
    }
    if(l<r) mx.push_back(r-l);
    if(s[0]==s[len-1]&&mx.size()) mx.pop_front();
    // for(int num:mx) cout<<num<<' ';
    // cout<<'\n';
    int ans = 0;
    sort(mx.begin(), mx.end());
    int m = mx.size();
    if(m<1) cout<<0<<'\n';
    else{
        for (int i = 0; i < m - 1; i++) {
            ans += max((int)0, mx[i] - 2 * t);
        }
        ans += max((int)0, mx[m - 1] - t - 1);
        cout << ans<<'\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
