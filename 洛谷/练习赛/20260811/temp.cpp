#include <bits/stdc++.h>
using namespace std;

using LL = long long;

map<int, int> mp;
void solve(){
    int n;
    cin >> n;
    n++;

    if(mp.count(n)){
        cout << mp[n] << "\n";
        return;
    }

    vector<int> d;
    for(int i = 1; i * i <= n; i++){
        if(n % i == 0){
            d.push_back(i);
            if(i * i != n) d.push_back(n / i);
        }
    }
    if(d.size() == 2){
        cout << n - 1 << "\n";
        return;
    }

    sort(d.begin(), d.end());

    vector<int> f(d.size(), n);
    f[0] = 0;
    for(int i = 1; i < (int)d.size(); i++){
        for(int j = i-1; j>=0; j--){
            f[i] = min(f[i], f[j] + (d[i] - 1) / d[j]);
            if(d[i]%d[j]==0){
                break;
            }
            // cout << d[i] << " " << d[j] << " " << (d[i] - 1) / d[j] << endl;
        }
    }

    mp[n] = f[d.size() - 1];
    cout << f[d.size() - 1] << "\n";
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}