#include <bits/stdc++.h>
#define int long long
using namespace std;
const int p = 1e9 + 7;
int n, m;
bool f(vector<int> a, vector<int> b)
{
    int x = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[x])
            continue;
        else
        {
            cnt++;
            if (cnt >= 2)
            {
                x++;
                if (x == m)
                {
                    return true;
                }
            }
            else
            {
                continue;
            }
        }
    }
    if (x < m)
        return false;
    else{
        return true;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    if (f(a, b))
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}