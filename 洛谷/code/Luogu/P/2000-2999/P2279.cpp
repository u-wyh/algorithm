#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2020;
int n, b[N], f[N], d[N], o[N], ans, u, v, w;

bool cmp(int x, int y) {
    return d[x] > d[y];
}

int main() {
    cin >> n;
    b[1] = 1;
    o[1] = o[0] = N;
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        d[i] = d[f[i]] + 1;
        b[i] = i;
        o[i] = N;
    }
    sort(b + 1, b + n + 1, cmp);//根据深度排序

    for (int i = 1; i <= n; i++) {
        v = b[i];
        w = f[v];
        u = f[f[v]];
        o[v] = min(o[v], min(o[w] + 1, o[u] + 2));//看看自己与监控的最低距离是多少
        if (o[v] > 2) {
            //距离太远 无法覆盖  那么就在爷爷处安上一个监控
            //由于自己的节点会被监控  并且不会再被访问  所以不用管了
            o[u] = 0;
            ans++;
            o[f[u]] = min(o[f[u]], 1);
            o[f[f[u]]] = min(o[f[f[u]]], 2);
        }
    }
    cout << ans << endl;
    return 0;
}
