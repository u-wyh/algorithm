#include <bits/stdc++.h>
using namespace std;

const int MAXK = 100000;
const long long INF = 3000000000; 

struct Item {
    int c, a, b;
};

struct Query {
    int m, k, s, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].c >> items[i].a >> items[i].b;
    }
    
    int p;
    cin >> p;
    vector<Query> queries(p);
    for (int i = 0; i < p; i++) {
        cin >> queries[i].m >> queries[i].k >> queries[i].s;
        queries[i].id = i;
    }
    
    sort(items.begin(), items.end(), [](const Item& x, const Item& y) {
        return x.a < y.a;
    });
    
    sort(queries.begin(), queries.end(), [](const Query& x, const Query& y) {
        return x.m < y.m;
    });
    
    vector<long long> dp(MAXK + 1, -1);
    dp[0] = INF;
    
    vector<string> ans(p);
    int idx = 0;
    for (const Query& q : queries) {
        while (idx < n && items[idx].a <= q.m) {
            int c = items[idx].c;
            int b = items[idx].b;
            for (int j = MAXK; j >= c; j--) {
                if (dp[j - c] != -1) {
                    long long new_val = min(dp[j - c], (long long)b);
                    if (new_val > dp[j]) {
                        dp[j] = new_val;
                    }
                }
            }
            idx++;
        }
        
        if (q.k <= MAXK && dp[q.k] != -1 && dp[q.k] > q.m + q.s) {
            ans[q.id] = "TAK";
        } else {
            ans[q.id] = "NIE";
        }
    }
    
    for (int i = 0; i < p; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}