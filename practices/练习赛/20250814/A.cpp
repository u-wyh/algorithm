#include <bits/stdc++.h>
using namespace std;
void solve(){
    string s;
    cin >> s;
    // s[0]: digit, s[1]: op, s[2]: digit, s[3]: '='
    int a = s[0] - '0';
    int b = s[2] - '0';
    char op = s[1];
    if (s[3] != '=') {
        cout << "No\n";
        return;
    }
    int left = 0;
    if (op == '+') left = a + b;
    else if (op == '-') left = a - b;
    else if (op == '*') left = a * b;
    else {
        cout << "No\n";
        return;
    }
    string t = s.substr(0, 3); // "aob"
    string rev_t = t;
    reverse(rev_t.begin(), rev_t.end());
    // Try "aob=boa"
    int a2 = rev_t[0] - '0';
    int b2 = rev_t[2] - '0';
    char op2 = rev_t[1];
    int right = 0;
    bool valid = false;
    if (op2 == '+' || op2 == '-' || op2 == '*') {
        if (op2 == '+') right = a2 + b2;
        else if (op2 == '-') right = a2 - b2;
        else if (op2 == '*') right = a2 * b2;
        if (left == right) valid = true;
    }
    if (valid) cout << "Yes\n";
    else cout << "No\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
