#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve(){
    int m, r, c;
    cin >> m >> r >> c;

    double ans1 = min(1.0*m / c, 1.0), ans2 = 0, ans3 = 1.0*m / (m + r);
    
    int t=c%(m+r);
    if(t>m){
        int all=c/(m+r);
        ans2=max(1.0*(all+1)*m/c,1.0*(all+2)*m/(c-t+m+m+r));
    }
    else{
        int all=c/(m+r);
        ans2=1.0*(all+1)*m/(c-t+m);
    }


    cout << max({ans1, ans2, ans3}) << "\n";
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(12);

    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}
/*
2
4 3 5
4 3 10

*/