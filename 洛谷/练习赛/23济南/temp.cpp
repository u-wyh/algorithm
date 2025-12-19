#include<bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int a = 0;
    int n = s.size();
    for(int i = 0; i < n; i ++){
        if(s[i] == ')') s[i] = '(';
        if(s[i] == ']') s[i] = '[';
    }
    for(int i = 0; i < n; i ++){
        if(s[i + 1] == s[i]){
            int res = 1;
            while(s[i + 1] == s[i]){
                i ++;
                res ++;
            }
            if(res >= 3){
                cout << "No\n";
                return;
            }
            else a ++;
        }
    }
    if(a >= 3) cout << "No\n";
    else cout << "Yes\n";
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}