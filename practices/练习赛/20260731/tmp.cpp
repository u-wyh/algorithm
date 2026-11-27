#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve(){
    int n;
    cin >> n;

    if(n & 1){
        cout << "-1\n";
        return;
    }

    if(n == 4){
        cout << "0 1 2 3\n";
        cout << "1 3 0 2\n";
        cout << "2 0 3 1\n";
        return;
    }

    vector<int> a;
    for(int i = n - 2; i >= 0; i -= 2) a.push_back(i);
    for(int i = n - 1; i >= 1; i -= 2) a.push_back(i);
    // swap(a[n / 2], a[n - 2]);

    vector<int> b;
    b.push_back(0);
    for(int i = n - 2; i >= 2; i -= 2) b.push_back(i);
    b.push_back(1);
    for(int i = n - 1; i >= 3; i -= 2) b.push_back(i);
    // swap(b[n / 2], b[n - 2]);

    int add = 0;
    vector<int> c(n);
    for(int i = n - 1; i >= 0; i--){
        c[i] = (a[i] + b[i] + add) % n;
        if(a[i] + b[i] + add >= n) add = 1;
        else add = 0;
    }

    int zero = 0, one = 0;
    for(int i = 0; i < n; i++){
        if(c[i] == 0) zero = i;
        if(c[i] == 1) one = i;
    }

    // cout << zero << " " << one << endl;

    // swap(a[zero], a[one]);
    // swap(b[zero], b[one]);

    if((n / 2) & 1){
        // cout << zero << " " << one << endl;
        int x = a[one];
        for(int i = one; i >= zero + 2; i--){
            a[i] = a[i - 1];
        }
        a[zero + 1] = x;

        x = b[one];
        for(int i = one; i >= zero + 2; i--){
            b[i] = b[i - 1];
        }
        b[zero + 1] = x;

        if(n > 6){
            add = 0;
            for(int i = n - 1; i >= 0; i--){
                c[i] = (a[i] + b[i] + add) % n;
                if(a[i] + b[i] + add >= n) add = 1;
                else add = 0;
            }

            int n_ = 0, n__ = 0;
            for(int i = 0; i < n; i++){
                if(c[i] == n - 3) n_ = i;
                if(c[i] == n - 4) n__ = i;
            }

            x = a[n_];
            for(int i = n_; i >= n__ + 2; i--){
                a[i] = a[i - 1];
            }
            a[n__ + 1] = x;

            x = b[n_];
            for(int i = n_; i >= n__ + 2; i--){
                b[i] = b[i - 1];
            }
            b[n__ + 1] = x;
        }

    }else{
        // cout << "XX: " << one << " " << zero << endl;
        int x = a[one];
        for(int i = one; i <= zero - 1; i++){
            a[i] = a[i + 1];
        }
        a[zero] = x;

        x = b[one];
        for(int i = one; i <= zero - 1; i++){
            b[i] = b[i + 1];
        }
        b[zero] = x;


        if(n > 4){

            add = 0;
            for(int i = n - 1; i >= 0; i--){
                c[i] = (a[i] + b[i] + add) % n;
                if(a[i] + b[i] + add >= n) add = 1;
                else add = 0;
            }

            int n_ = 0, n__ = 0;
            for(int i = 0; i < n; i++){
                if(c[i] == n - 3) n_ = i;
                if(c[i] == n - 4) n__ = i;
            }

            x = a[n_];
            for(int i = n_; i <= n__ - 1; i++){
                a[i] = a[i + 1];
            }
            a[n__] = x;

            x = b[n_];
            for(int i = n_; i <= n__ - 1; i++){
                b[i] = b[i + 1];
            }
            b[n__] = x;
        }

        
    }

    add = 0;
    for(int i = n - 1; i >= 0; i--){
        c[i] = (a[i] + b[i] + add) % n;
        if(a[i] + b[i] + add >= n) add = 1;
        else add = 0;
    }

    for(auto i : a) cout << i << " ";
    cout << "\n";
    for(auto i : b) cout << i << " ";
    cout << "\n";
    for(auto i : c) cout << i << " ";
    cout << "\n";
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while(T--){
        solve();
    }

    // solve(6);

    // for(int n = 4; n <= 20; n += 4){
    //     solve(n);
    // }
    return 0;
}