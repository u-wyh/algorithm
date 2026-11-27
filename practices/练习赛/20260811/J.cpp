#include <bits/stdc++.h>
using namespace std;
#define int long long
using LL = long long;

int calc(int x0, int y0, int x, int y){
    int mu = x0 - x;
    int y0_y = (x0 * (y0 - y)  ) / mu; 
    return y0 - y0_y; 
}

long double slope(int x, int y, int x0, int y0){
    return (long double)1.0 * (y - y0) / (x - x0);  
}

void solve(){
    int n; cin >> n;
    int q; cin >> q;
    vector<int> res(n + 1);
    vector<pair<int, int>> a(n + 1);
    stack<pair<int, int>> st; 
    for(int i = 1; i <= n; i++){
        cin >> a[i].first >> a[i].second; 
    }
    sort(a.begin() + 1, a.end());
    for(int i = 1; i <= n; i++){
        if(i == 1){
            res[i] = 1; 
            st.push({a[i].first, a[i].second});
        }else if(i == 2){
            int x0 = a[i].first, y0  = a[i].second;
            res[i] = calc(x0, y0, st.top().first, st.top().second);  
            st.push({a[i].first, a[i].second});
        }else{
            int x0 = a[i].first, y0  = a[i].second;
            int x1 = st.top().first, y1 = st.top().second;
            st.pop(); 
            int x2 =  st.top().first, y2 = st.top().second;
            st.push({x1, y1}); 
            while(slope(x0, y0, x1, y1) >= slope(x0, y0, x2, y2) && st.size() >= 2){ // slope xiao
                st.pop(); 
                x1 = x2; y1 = y2; 
                if(st.size() == 1) break; 
                st.pop(); 
                x2 = st.top().first; y2 = st.top().second; 
                st.push({x1, y1}); 
            }         
            res[i] = calc(x0, y0, st.top().first, st.top().second);  
            st.push(a[i]); 
        }
    }
    for(int i = 1; i <= n; i++){
        cout << res[i] << "\n"; 
    }
    sort(res.begin() + 1, res.end()); 
    
    
    for(int i = 1; i <= q; i++){
        int y; cin >> y; 
        int l = 1,  r = n; 
        while(l <= r){
            int mid = (l + r) / 2; 
            if(y >= res[mid]) l = mid + 1; 
            else r = mid - 1; 
        }
        cout << l - 1 << "\n"; 
    }
    return;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; 
    while(T--){
        solve();
    }
    return 0;
}

/*
7 0
1 1
2 3
3 1
4 3
5 1
6 3
7 1

*/