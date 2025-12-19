#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned uint;
typedef pair<int, int> pii;
const int N = 1e5 + 5;

int n, t[140], zyq;
char s[N];
int p[N];
vector<int> qu[140];
int cnt;
vector<int> ans[N];

void mian() {
    cin >> n;
    zyq = -1;
    cnt = 0;
    for (int i = 'a'; i <= 'z'; ++i) {
        t[i] = 0;
        qu[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        ++t[s[i]];
    }
    for (int i = 'a'; i <= 'z'; ++i) {
        if (t[i] >= (n + 1) / 2) {
            zyq = i;
        }
    }
    if (zyq < 0) {
        for (int i = 1; i <= n; ++i) {
            qu[s[i]].push_back(i);
        }
        cnt = n >> 1;
        int tot = 0;
        for (int i = 'a'; i <= 'z'; ++i) {
            for (auto it : qu[i]) {
                p[++tot] = it;
            }
        }
        for (int i = 1; i <= (n >> 1); ++i) {
            ans[i].push_back(p[i]);
            ans[i].push_back(p[i + (n >> 1)]);
        }
        if (n & 1) {
            ans[1].push_back(p[n]);
        }
    } else {
        if (t[zyq] == n) {
            cout << "Shuiniao\n";
            return;
        }
        if (t[zyq] == n - 1) {
            if ((n & 1) && s[(n + 1) >> 1] != zyq) {
                cout << "Shuiniao\n";
                return;
            }
            cout << "Huoyu\n1\n" << n << " ";
            for (int i = 1; i <= n; ++i) {
                cout << i << " ";
            }
            cout << "\n";
            return;
        }
        int l, r;
        cnt = 2;
        for (int i = 1; i <= n; ++i) {
            if (s[i] != zyq) {
                l = i;
                break;
            }
        }
        for (int i = n; i >= 1; --i) {
            if (s[i] != zyq) {
                r = i;
                break;
            }
        }
        ans[1].push_back(l);
        ans[2].push_back(r);
        for (int i = l + 1; i <= n; ++i) {
            if (s[i] == zyq) {
                ans[1].push_back(i);
            }
        }
        for (int i = 1; i <= l - 1; ++i) {
            if (s[i] == zyq) {
                ans[2].push_back(i);
            }
        }
        for (int i = l + 1; i <= r - 1; ++i) {
            if (s[i] != zyq) {
                ans[++cnt].push_back(i);
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            if (ans[i].size() < 2) {
                if (ans[1].size() > 2) {
                    ans[i].push_back(ans[1].back());
                    ans[1].pop_back();
                } else {
                    ans[i].push_back(ans[2].back());
                    ans[2].pop_back();
                }
            }
        }
    }
    cout << "Huoyu\n" << cnt << "\n";
    for (int i = 1; i <= cnt; ++i) {
        cout << ans[i].size() << " ";
        sort(ans[i].begin(), ans[i].end());
        for (auto it : ans[i]) {
            cout << it << " ";
        }
        cout << "\n";
        ans[i].clear();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int c, _;
    cin >> c >> _;
    while (_--) {
        mian();
    }
    return 0;
}